#ifndef KWS_DECODER_H
#define KWS_DECODER_H

#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <tuple>

#include "trie.h"

using namespace std;
namespace py = pybind11;

class KWSDecoder
{
    Trie trie;
    vector<char32_t> alphabet;
    int blank_index;
    int alphabet_size;
    long unsigned int beam_width = 16;
    float beta = 1.2;
    float min_keyword_score = 0.01;
    int max_gap = 3;
    float min_clip = .01;
    int top_n = 10;

    public:
        KWSDecoder(vector<char32_t>, int);

        void add_words(vector<u32string>);
        map<u32string, vector<map<u32string, float>>> search(py::array_t<float>);

    private:
        tuple<vector<int>, vector<vector<float>>> collapse(py::array_t<float>);
};

#endif
