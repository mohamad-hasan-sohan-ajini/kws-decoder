clear
cd src
echo "compiling the sources..."
g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) node.cpp trie.cpp counter.cpp kws_decoder.cpp wrapper.cpp -o wrapper$(python3-config --extension-suffix)
cd ..
mv src/wrapper.cpython-38-x86_64-linux-gnu.so .
echo "running the tire test..."
python3 trie_test.py
echo "running the decoder test..."
python3 decoder_test.py
