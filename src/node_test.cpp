#include <iostream>

#include "node.h"

using namespace std;

int main()
{
    cout<<"hello world"<<endl;
    Node root;
    Node *a = new Node('a', false);
    Node *b = new Node('b', false);
    root.add_child(a);
    a->add_child(b);
    root.add_child(b);
    root.add_child(&root);
    return 0;
}
