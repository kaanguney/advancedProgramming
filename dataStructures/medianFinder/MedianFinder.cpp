#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MedianFinder.h"
using namespace std;

void add_value(int value, Heap<int> *minptr, Heap<int> *maxptr) {
    
    // Insert in max heap first
    maxptr->insert_max(value);
    /* If difference between two heap size is more than 1
     or the maximum element in max heap more than least element in min heap
     then remove from max heap and add to min heap*/
    
    if((maxptr->GetCount() - minptr->GetCount()) >1 || (minptr->GetCount() != 0 && maxptr->get_top() > minptr->get_top())) {
        int top = maxptr->get_top();
        maxptr->max_key(0);
        minptr->insert_min(top);
    }
    /* If difference between two heap size is more than 1 */
    
    if((minptr->GetCount() !=0 && (minptr->GetCount() - maxptr->GetCount()) >1)){
        int top = minptr->get_top();
        minptr->min_key(0);
        maxptr->insert_max(top);
    }
}

double median( Heap<int> *minptr, Heap<int> *maxptr) { // prints out the median
    
    double median = 0;
    
    if(minptr->GetCount() == maxptr->GetCount()) { // if the sizes are equal
        
        median = (minptr->get_top() + maxptr->get_top());
        
        median = median / 2;
    }
    
    else { // if max_heap_size - min_heap_size == 1
        
        if(maxptr->GetCount() > minptr->GetCount()) {
            
            median = maxptr->get_top(); // get the root
        }
        
        else { // only for the first insertion
            
            median = minptr->get_top();
        }
    }
    
    return median;
}

int main() {
    
    MinHeap<int> min; // heaps defined here
    MaxHeap<int> max;
    Heap<int> *minptr = &min;
    Heap<int> *maxptr = &max;
    
    ifstream input;
    
    string filename, line;
    
    int key; // heap keys
    
    bool notfirst = false;
    
    do {
        
        if(notfirst) {
            
            input.open(filename.c_str());
            
            while(getline(input,line)) {
                
                istringstream iss(line);
                
                iss >> key;
                
                add_value(key, minptr, maxptr);
            }
            
            cout << "current median: " << median(minptr, maxptr) << endl;
            
            input.close();
        }
        
        notfirst = true;
        
        cout << "Please enter the next filename that contains integer stream: ";
        
    } while(getline(cin,filename));
    
    return 0;
}
