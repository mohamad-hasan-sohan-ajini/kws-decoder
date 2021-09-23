#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

class Node
{
    bool is_word;
    char ch;
    vector<Node*> children;

    public:
        Node();
        Node(char, bool);

        vector<Node*> get_children();
        void add_child(Node*);
        char get_char();
        bool get_is_word();
        void set_is_word(bool);
};

#endif
