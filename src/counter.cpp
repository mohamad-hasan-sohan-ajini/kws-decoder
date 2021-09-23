#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <locale>
#include <codecvt>
#include <iostream>

#include "counter.h"

using namespace std;

map<string, float> Counter::get_counter()
{
    return counter;
}

void Counter::set_item(string prefix, float prob)
{
    counter[prefix] = prob;
}

float Counter::get_value(string prefix)
{
    return counter[prefix];
}

void Counter::accumulate_prob(string prefix, float prob)
{
    counter[prefix] += prob;
}

vector<string> Counter::get_keys()
{
    vector<string> result;
    for(map<string, float>::iterator i = counter.begin(); i != counter.end(); i++)
    {
        result.push_back(i->first);
    }
    return result;
}

float Counter::get_normalized_prob(float beta, string key)
{
    return counter[key] * pow(beta, wstring_convert<codecvt_utf8<char32_t>, char32_t>{}.from_bytes(key).size());
}

vector<float> Counter::get_normalized_probs(float beta)
{
    vector<float> result;
    for(map<string, float>::iterator i = counter.begin(); i != counter.end(); i++)
    {
        result.push_back(i->second * pow(beta, wstring_convert<codecvt_utf8<char32_t>, char32_t>{}.from_bytes(i->first.length()).size()));
    }
    return result;
}

Counter Counter::operator+(Counter operand)
{
    set<string> keys;
    for (string key : get_keys())
    {
        keys.insert(key);
    }
    for (string key : operand.get_keys())
    {
        keys.insert(key);
    }

    Counter result;
    for (string key : keys)
    {
        result.set_item(key, counter[key] + operand[key]);
    }
    return result;
}

float Counter::operator[](string prefix)
{
    return counter[prefix];
}

void Counter::clear()
{
    counter.clear();
}
