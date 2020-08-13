#include <iostream>
#include <string>
#include "binary.h"
using namespace std;

template<class T>
class bst {
    
public:
    bst();
    void insert(const T & item);
    bool find(const string & item);
    T * elts(const string & query); // return the WordItem element

private:
    BinaryNode<T> *root; //
    void insert(const T & x,BinaryNode<T> * & t); // taken from slides, private method //
    
} ;


template<class T> // constructor
bst<T>::bst()
: root(NULL) {}

template<class T> // taken from slides, private method
void bst<T>::insert(const T & x, BinaryNode<T> * & t) {
    
    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode<T>( x, NULL, NULL );
    else if( x.word < t->element.word )
        insert( x, t->left );  // insert at the left or
    else if( t->element.word < x.word )
        insert( x, t->right );  // right subtree
    else
        ;  // Duplicate; do nothing
}

template<class T>
void bst<T>::insert(const T & item) {
    
    insert(item,root);
}

template<class T>
bool bst<T>::find(const string & item) {
    
    BinaryNode<T> * node = root;
    
    while(node != NULL) {
        
        if(node->element.word > item) {
            
            node = node-> left;
        }
        
        else if(node->element.word < item) {
            
            node = node -> right;
        }
        
        else if(node->element.word == item) {
            
            return true;
        }
    }
    
    return false;
}

template<class T>
T * bst<T>::elts(const string & query) { // return the worditem address to a pointer where the intended query string is stored
    
    BinaryNode<T> * ptr = root;
    
    T * word_item;
    
    while(ptr != NULL) {
        
        if(ptr->element.word > query) {
            
            ptr = ptr -> left;
        }
        
        else if(ptr->element.word < query) {
            
            ptr = ptr -> right;
        }
        
        else { // if ptr -> element.word == query, found
            
            word_item = &ptr->element;
            
            return word_item;
        }
    }
    
    return NULL;
}


