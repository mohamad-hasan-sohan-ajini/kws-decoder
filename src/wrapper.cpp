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
        .def("search", &KWSDecoder::search);
}
