# Keyword Spotting Decoder

Here is an implementation of KWS decoder in C++ language to speed up decoding in python.

## How to compile

```bash
cd src
g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) node.cpp trie.cpp counter.cpp kws_decoder.cpp wrapper.cpp -o wrapper$(python3-config --extension-suffix)
```

## How to test

Trie test:

```bash
python3 trie_test.py
```

And decoder test:

```bash
python decoder_test.py
```

---
**NOTE**

The commands needed to the compilation and testing modules is placed in `compile.sh`.

---
