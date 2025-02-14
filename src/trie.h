#ifndef TRIE_H
#define TRIE_H

#include <string>

#include "node.h"

using namespace std;

class Trie
{
    Node *root;

    public:
        Trie();
        ~Trie();

        void add_word(std::string);
        bool has_word(std::string);
        bool is_promising(std::string);

    private:
        Node* get_root();
        Node* inspect_children(Node*, char);
        Node* traverse(std::string);
};

#endif
