#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

#include "trie.h"
#include "counter.h"
#include "kws_decoder.h"

using namespace std;
namespace py = pybind11;

KWSDecoder::KWSDecoder(vector<char> alphabet_, int blank_index_)
{
    alphabet = alphabet_;
    blank_index = blank_index_;
    alphabet_size = alphabet.size();
}

void KWSDecoder::add_words(vector<string> keywords)
{
    for (string keyword : keywords)
    {
        trie.add_word(keyword);
    }
}

tuple<vector<int>, vector<vector<float>>> KWSDecoder::collapse(py::array_t<float> np_array)
{
    // make a direct access to np_array
    auto array = np_array.unchecked<2>();

    // find run length vector
    float prob, max_prob;
    int arg_max_prob, prev_arg_max_prob, current_length;
    vector<int> cumsum_run_length;
    cumsum_run_length.push_back(0);
    max_prob = 0;
    for (py::ssize_t char_index = 0; char_index < array.shape(1); char_index++)
    {
        prob = array(0, char_index);
        if (prob > max_prob)
        {
            max_prob = prob;
            prev_arg_max_prob = char_index;
        }
    }
    current_length = 0;
    for (py::ssize_t t = 0; t < array.shape(0); t++)
    {
        max_prob = 0;
        for (py::ssize_t char_index = 0; char_index < array.shape(1); char_index++)
        {
            prob = array(t, char_index);
            if (prob > max_prob)
            {
                max_prob = prob;
                arg_max_prob = char_index;
            }
        }
        if (arg_max_prob == prev_arg_max_prob)
        {
            current_length += 1;
        }
        else
        {
            cumsum_run_length.push_back(cumsum_run_length.back() + current_length);
            current_length = 1;
            prev_arg_max_prob = arg_max_prob;
        }
    }

    // collapse vectors with the same argmax
    vector<vector<float>> result;
    vector<float> current_max;
    for (int char_index = 0; char_index < array.shape(1); char_index++)
    {
        current_max.push_back(0);
    }
    for (long unsigned int i = 1; i < cumsum_run_length.size(); i++)
    {
        for (int char_index = 0; char_index < array.shape(1); char_index++)
        {
            current_max[char_index] = 0;
        }
        for (int t = cumsum_run_length[i - 1]; t < cumsum_run_length[i]; t++)
        {
            for (int char_index = 0; char_index < array.shape(1); char_index++)
            {
                current_max[char_index] = max(array(t, char_index), current_max[char_index]);
            }
        }
        result.push_back(current_max);
    }

    return make_tuple(cumsum_run_length, result);
}

map<string, vector<map<string, float>>> KWSDecoder::search(py::array_t<float> np_array)
{
    vector<int> cumsum_run_length;
    vector<vector<float>> collapsed_array;
    tie(cumsum_run_length, collapsed_array) = collapse(np_array);

    // create temporary variables
    char ch;
    float tmp_prob, threshold_score, score, prob, char_prob_threshold;
    string prefix_plus;
    Counter A_next;
    vector<string> A_next_keys;
    vector<float> A_next_scores, char_probs;
    bool has_empty_string;
    map<string, vector<map<string, float>>> results;
    map<string, float> tmp_result;

    // create variables
    string empty_string = "";
    map<int, Counter> Pb, Pnb;
    vector<string> A_prev;

    // initiate defaults
    Pb[-1].set_item(empty_string, 1.0);
    Pnb[-1].set_item(empty_string, 0.0);
    A_prev.push_back(empty_string);

    for (size_t t = 0; t < collapsed_array.size(); t++)
    {
        // prune alphabet
        char_probs.clear();
        for (int char_index = 0; char_index < alphabet_size; char_index++)
        {
            char_probs.push_back(collapsed_array[t][char_index]);
        }
        sort(char_probs.begin(), char_probs.end(), greater<float>());
        char_prob_threshold = char_probs[top_n];
        for (string prefix : A_prev)
        {
            for (int char_index = 0; char_index < alphabet_size; char_index++)
            {
                ch = alphabet[char_index];
                prob = collapsed_array[t][char_index];
                if (prob < char_prob_threshold)
                {
                    continue;
                }
                prob = max(prob, min_clip);

                if (char_index == blank_index)
                {
                    // step 3
                    tmp_prob = Pb[t][prefix] + prob * (Pb[t-1][prefix] + Pnb[t-1][prefix]);
                    Pb[t].set_item(prefix, tmp_prob);
                }
                else
                {
                    prefix_plus = prefix + ch;
                    if (ch == prefix.back())
                    {
                        // step 4
                        tmp_prob = Pnb[t][prefix_plus] + prob * Pb[t-1][prefix];
                        Pnb[t].set_item(prefix_plus, tmp_prob);
                        tmp_prob = Pnb[t][prefix] + prob * Pnb[t-1][prefix];
                        Pnb[t].set_item(prefix, tmp_prob);
                    }
                    else
                    {
                        // step 5
                        tmp_prob = Pnb[t][prefix_plus] + prob * (Pb[t-1][prefix] + Pnb[t-1][prefix]);
                        Pnb[t].set_item(prefix_plus, tmp_prob);
                    }
                    // TODO: implement "step 6" to make the results more accurate
                }
            }
        }
        // filter promising and results
        A_next.clear();
        A_next = Pb[t] + Pnb[t];
        A_next_keys.clear();
        for (string key : A_next.get_keys())
        {
            // compute sc ore
            score = A_next.get_normalized_prob(beta, key);
            // breaking conditions
            if (score < min_keyword_score)
            {
                continue;
            }
            if (trie.is_promising(key))
            {
                A_next_keys.push_back(key);
            }
            if (trie.has_word(key))
            {
                tmp_result["timestep"] = t;
                tmp_result["score"] = score;
                tmp_result["end"] = cumsum_run_length[t + 1];
                if (results[key].size() > 0)
                {
                    if (t - results[key].back()["timestep"] < max_gap)
                    {
                        if (results[key].back()["score"] < score)
                        {
                            results[key].pop_back();
                            results[key].push_back(tmp_result);
                        }
                    }
                    else
                    {
                        results[key].push_back(tmp_result);
                    }
                }
                else
                {
                    results[key].push_back(tmp_result);
                }
            }
        }
        // sort scores of promising prefixes
        A_next_scores.clear();
        for (string key : A_next_keys)
        {
            A_next_scores.push_back(A_next.get_normalized_prob(beta, key));
        }
        sort(A_next_scores.begin(), A_next_scores.end(), greater<float>());
        A_next_scores.resize(beam_width);
        threshold_score = A_next_scores.back();
        // add top k to A_prev
        A_prev.clear();
        has_empty_string = false;
        for (string key : A_next_keys)
        {
            if (A_next.get_normalized_prob(beta, key) >= threshold_score)
            {
                A_prev.push_back(key);
                if (key == empty_string)
                {
                    has_empty_string = true;
                }
            }
        }
        if (!has_empty_string)
        {
            A_prev.push_back(empty_string);
        }
        Pb[t].set_item(empty_string, 1.0);
        Pnb[t].set_item(empty_string, 0.0);
    }
    // return
    return results;
}
