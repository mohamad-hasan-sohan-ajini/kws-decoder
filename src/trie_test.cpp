#include <iostream>

#include "trie.h"

using namespace std;

int main()
{
    Trie trie;
    cout<<"hello world"<<trie.get_root()->get_char()<<endl;
    cout<<"has مادر: "<<trie.has_word("مادر")<<endl;
    trie.add_word("مادرید");
    cout<<"has مادر: "<<trie.has_word("مادر")<<endl;
    cout<<"is promising مادر:"<<trie.is_promising("مادر")<<endl;
    cout<<"has مادرید: "<<trie.has_word("مادرید")<<endl;
    return 0;
}
