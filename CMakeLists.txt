cmake_minimum_required(VERSION 3.6)
project(kws_decoder)

# Allow the user to specify the Python version
set(PYTHON_VERSION "3.11" CACHE STRING "Python version to use (e.g., 3.11, 3.10, etc.)")

# Find python version
execute_process(
    COMMAND python${PYTHON_VERSION}-config --extension-suffix
    OUTPUT_VARIABLE PYTHON_EXTENSION_SUFFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Find the Python package with pybind11
find_package(pybind11 REQUIRED PATHS ${PB11})

# Add the source files
set(SOURCES
    src/node.cpp
    src/trie.cpp
    src/counter.cpp
    src/kws_decoder.cpp
    src/wrapper.cpp
)

# Create a shared library
add_library(wrapper SHARED ${SOURCES})

# Set compiler options
target_compile_options(wrapper PRIVATE -O3 -Wall -std=c++11 -fPIC)

# Include pybind11 headers
target_include_directories(wrapper PRIVATE ${pybind11_INCLUDE_DIRS})

# Set the output name to wrapper without the lib prefix and .so suffix
set_target_properties(wrapper PROPERTIES OUTPUT_NAME wrapper${PYTHON_EXTENSION_SUFFIX})
set_target_properties(wrapper PROPERTIES PREFIX "")
set_target_properties(wrapper PROPERTIES SUFFIX "")

# Link against Python library
target_link_libraries(wrapper PRIVATE ${pybind11_LIBRARIES})
