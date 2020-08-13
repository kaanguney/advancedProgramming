#include <iostream>
#include <string>
using namespace std;

template<class T>
class bst; // binary search tree class

template<class T>
class BinaryNode {
    
    T element;
    
    BinaryNode *left, *right;
    
    BinaryNode(const T & item, BinaryNode *left_node, BinaryNode *right_node):
    
    element(item), left(left_node), right(right_node)
    
    {}
    
    friend class bst<T>; // templated
} ;


