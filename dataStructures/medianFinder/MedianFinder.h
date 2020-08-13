#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#define MAX 100000
using namespace std;

template<class T>
class Heap {
public:
    Heap() { // constructor
        
        current_size = 0;
    }
    
    virtual void insert_min(T key) = 0;
    virtual void insert_max(T key) = 0;
    virtual T get_top() = 0;
    virtual int GetCount() = 0;
    virtual void heapify_MAX(T key) = 0;
    virtual void heapify_MIN(T key) = 0;
    virtual void min_key(T key) = 0;
    virtual void max_key(T key) = 0;
    virtual T extract_min() = 0;
    virtual T extract_max() = 0;
    
protected:
    int current_size;
    T array[MAX];
    int max(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }
    
    void swap(int *a, int *b) {
        int t = *a;
        *a = *b;
        *b = t;
    }
    
    // parent
    int parent(int i) {
        return (i - 1) / 2;
    }
    

    // left child
    int left(int i) {
        return 2 * i + 1;
    }
    

    // right child
    int right(int i) {
        return 2 * i + 2;
    }
    
    // get the top of the element
    T top() {
        
        T x = array[0];
        return x;
    }
    
    int count() {
        
        return current_size;
    }
    
    void heapify_min(int i) {
        int l = left(i);
        int r = right(i);
        int child = i;
        if (l < current_size && array[l] < array[i]) {
            child = l;
        }
        if (r < current_size && array[r] < array[child]) {
            child = r;
        }
        
        if (child != i) {
            swap(&array[i], &array[child]);
            heapify_min(child);
        }
    }
    
    T extractMIN() {
        if (current_size <= 0) {
            return INT_MIN;
        } else if (current_size == 1) {
            current_size--;
            return array[0];
        }
        T root = array[0];
        array[0] = array[current_size - 1];
        current_size--;
        heapify_min(0);
        return root;
    }
    
    T extractMAX() {
        if (current_size <= 0) {
            return INT_MIN;
        } else if (current_size == 1) {
            current_size--;
            return array[0];
        }
        T root = array[0];
        array[0] = array[current_size - 1];
        current_size--;
        heapify_max(0);
        return root;
    }
    
    void heapify_max(int i) {
        int l = left(i);
        int r = right(i);
        int child = i;
        if (l < current_size && array[l] > array[i]) {
            child = l;
        }
        if (r < current_size && array[r] > array[child]) {
            child = r;
        }
        
        if (child != i) {
            swap(&array[i], &array[child]);
            heapify_max(child);
        }
    }
    
    void deleteMinkey(int i) {
        
        if (i >= current_size) { // cannot delete in this case
            cout << "No deletion\n";
            return;
        }
        if (current_size == 1) {
            current_size--;
            return; // all deleted at this point
        }
        
        array[i] = array[current_size - 1];
        current_size--;
        heapify_min(i);
    }
    
    void deleteMaxkey(int i) {
        
        if (i >= current_size) { // cannot delete in this case
            cout << "No deletion\n";
            return;
        }
        if (current_size == 1) {
            current_size--;
            return; // all deleted at this point
        }
        
        array[i] = array[current_size - 1];
        current_size--;
        heapify_max(i);
    }
    
    
    void insertHeapMax(int x) {
        
        if (current_size == MAX) {
            cout << "heap overflow\n";
            return;
        }
        array[current_size] = x;
        current_size++;
        int i = current_size - 1;
        while (i!= 0 && array[parent(i)] < array[i]) {
            swap(&array[parent(i)], &array[i]);
            i = parent(i);
        }
    }
    
    void insertHeapMin(int x) {
        
        if (current_size == MAX) {
            cout << "heap overflow\n";
            return;
        }
        array[current_size] = x;
        current_size++;
        int i = current_size - 1;
        while (i!= 0 && array[parent(i)] > array[i]) {
            swap(&array[parent(i)], &array[i]);
            i = parent(i);
        }
    }
};

template<class T>
class MaxHeap : public Heap<T> {
    
public:
    MaxHeap() {
        
        this->current_size = 0;
    }
    
    T get_top() {
        
        return this->top();
    }
    
    int GetCount() {
        
        return this->count();
    }
    
    void heapify_MAX(int x) {
        
        this->heapify_max(x);
    }
    
    void heapify_MIN(int x) {
        
        this->heapify_min(x);
    }
    
    void min_key(int key) {
        
        this->deleteMinkey(key);
    }
    
    void max_key(int key) {
        
        this->deleteMaxkey(key);
    }
    
    void insert_min(int x) {
        
        this->insertHeapMin(x);
    }
    
    void insert_max(int x) {
        
        this->insertHeapMax(x);
    }
    
    T extract_min() {
        
        return this->extractMIN();
    }
    
    T  extract_max() {
        
        return this->extractMAX();
    }
};

template<class T>
class MinHeap : public Heap<T> {
    
public:
    MinHeap() {
        
        this->current_size = 0;
    }
    
    T get_top() {
        
        return this->top();
    }
    
    int GetCount() {
        
        return this->count();
    }
    
    void heapify_MAX(int x) {
        
        this->heapify_max(x);
    }
    
    void heapify_MIN(int x) {
        
        this->heapify_min(x);
    }
    
    void min_key(int key) {
        
        this->deleteMinkey(key);
    }
    
    void max_key(int key) {
        
        this->deleteMaxkey(key);
    }
    
    void insert_min(int x) {
        
        this->insertHeapMin(x);
    }
    
    void insert_max(int x) {
        
        this->insertHeapMax(x);
    }
    
    T extract_min() {
        
        return this->extractMIN();
    }
    
    T  extract_max() {
        
        return this->extractMAX();
    }
};


