# Keyword Spotting Decoder

Here is an implementation of KWS decoder in C++ language to speed up decoding in python using pybind.

## How to compile
A g++ compiler is needed for compiling c++ codes. It can be installed with installing build-essential as follow: <br>
**ubuntu**
```bash
sudo apt-get install build-essential
```

You need to have python3 installed. The requirements can be installed with pip as follow:

>### (Optional) run sample python codes
>If you want to run the sample codes available here, you need to install `pygtrie`, `torch`, `tqdm` using pip: <br>
> `pip install pygtrie, torch, tqdm`


### Python library requirements
For compiling the c++ codes and building python packages you need to install pybind using pip:
<br>`pip install pybind11`

### Complite c++ codes and make as python callable code
```bash
cd src
g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) node.cpp trie.cpp counter.cpp kws_decoder.cpp wrapper.cpp -o wrapper$(python3-config --extension-suffix)
```
### Use python build wrapper in your codes

copy `wrapper.*.so` file in running directory and use it as follow:

`from wrapper import KWSDecoder`

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

## Compile with make file

After installing PyBind11 using pip, locate the configuration file by running the following command:

```
find /path/to/venv -name "pybind11Config.cmake"
```

Next, create a build directory and navigate into it. While inside the build directory, run:

```bash
cmake -Dpybind11_DIR=/output/of/above/command/till/pybind11/folder ..
```

Finally, to build the package, execute:

```bash
make
```

You will find the Python package in the build directory.
