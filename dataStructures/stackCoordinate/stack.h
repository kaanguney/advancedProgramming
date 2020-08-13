#pragma once
using namespace std;

template <class T>
class Stack {
    
    public:
        Stack();
    
        void push(T coor);
        void pop();
        
    
        T top();
        bool isEmpty();
    
        const static T noItem;
    
	private:
		// Put your internal data representation here
    
        struct linked {
            
            T element;
            
            linked *next;
            
            linked(const T & elts, linked *other_node = NULL)
            :
            element(elts), next(other_node)
            {}
        } ;
    
        linked *stack_top;
};

