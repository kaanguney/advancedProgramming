#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "stack.h"
using namespace std;

template <class T> // CONSTRUCTOR
Stack<T>::Stack() {
    
    stack_top = NULL;
}

template <class T>
bool Stack<T>::isEmpty() {
    
    bool check = false;
    
    if(stack_top == NULL) {
        
        return !check;
    }
    
    return check;
}

template <class T>
void Stack<T>::push(T coordinate) {
    
    stack_top = new linked(coordinate, stack_top); // create new node
}

template <class T>
void Stack<T>::pop() {
    
    if(isEmpty()) {
        
        cout << "Underflow error !" << endl;
        
        // undeflow error burda nasıl atılır?
    }
    
    else {
        
        // if no underflow
        
        stack_top = stack_top -> next;
        
        // my implementation, just replace the top
    }
}

template <class T>
T Stack<T>::top() {
    
    if(isEmpty()) {
        
        cout << "Underflow error !" << endl;
        
        // undeflow error burda nasıl atılır?
    }
    
    // if no underflow
    
    return stack_top -> element; // return the top element of stack
}








