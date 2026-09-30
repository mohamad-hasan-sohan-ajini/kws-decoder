cmake_minimum_required(VERSION 3.15...4.2)
project(kws_decoder LANGUAGES CXX)

# Use CMake's modern FindPython support through pybind11.
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(kws_decoder MODULE
    cpp/node.cpp
    cpp/trie.cpp
    cpp/counter.cpp
    cpp/kws_decoder_core.cpp
    cpp/kws_decoder.cpp
)

target_compile_features(kws_decoder PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(kws_decoder PRIVATE /W4)
else()
    target_compile_options(kws_decoder PRIVATE -Wall -Wextra -Wpedantic)
endif()

# scikit-build-core packages the CMake install tree. Installing the extension
# here avoids writing generated, Python-version-specific files into src/.
install(TARGETS kws_decoder DESTINATION kws_decoder)
