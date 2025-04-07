#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "trie.h"
#include "kws_decoder.h"

namespace py = pybind11;

PYBIND11_MODULE(wrapper, m)
{
    py::class_<Trie>(m, "Trie")
        .def(py::init<>())
        .def("add_word", &Trie::add_word)
        .def("has_word", &Trie::has_word)
        .def("is_promising", &Trie::is_promising);

    py::class_<KWSDecoder>(m, "KWSDecoder")
        .def(py::init<vector<char32_t>, int>())
        .def("add_words", &KWSDecoder::add_words)
        .def("search", &KWSDecoder::search)
        // getters
        .def("get_blank_index", &KWSDecoder::get_blank_index)
        .def("get_alphabet_size", &KWSDecoder::get_alphabet_size)
        .def("get_beam_width", &KWSDecoder::get_beam_width)
        .def("get_beta", &KWSDecoder::get_beta)
        .def("get_min_keyword_score", &KWSDecoder::get_min_keyword_score)
        .def("get_max_gap", &KWSDecoder::get_max_gap)
        .def("get_min_clip", &KWSDecoder::get_min_clip)
        .def("get_top_n", &KWSDecoder::get_top_n)
        // setters
        .def("set_blank_index", &KWSDecoder::set_blank_index)
        .def("set_alphabet_size", &KWSDecoder::set_alphabet_size)
        .def("set_beam_width", &KWSDecoder::set_beam_width)
        .def("set_beta", &KWSDecoder::set_beta)
        .def("set_min_keyword_score", &KWSDecoder::set_min_keyword_score)
        .def("set_max_gap", &KWSDecoder::set_max_gap)
        .def("set_min_clip", &KWSDecoder::set_min_clip)
        .def("set_top_n", &KWSDecoder::set_top_n);
}
