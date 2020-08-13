#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <string>
#include "bst.h"
using namespace std;

template<class K, class V>
class HashTable; // prototype

template <class K, class V>
class HashNode {

    K key;
    
    V value;
    
    HashNode *next; // separate chaining
    
    // keys are going to be strings, values are stored in a vector for each word
    
    HashNode(K temp_key, V temp_value, HashNode *ptr = NULL) { // constructor
        
        key = temp_key;
        
        value.word = temp_value.word;
        value.info = temp_value.info;
        
        next = ptr;
        
    }
    
    friend class HashTable<K,V>; // to use HashNode
};

template<class K, class V>
class HashTable {
    
public:
    HashTable(int tablesize);
    int HashCode(K key);
    void insert(K key, V value);
    void resize(); // rehashing function
    
    int unique() const {
        
        return unique_words;
    }
    
    float loadFactor() const {
        
        return (float)(unique_words) / (float)(TableSize); // convert to double, else always will be zero
    }
    bool find(K key); // search for the given key
    bool isPrime(int n); // taken from slides
    int nextPrime(int n); // taken from slides
    V * elts(K key); // returns a pointer to the address of the element with the given key
    
private:
    int unique_words; // the number of indexes occupied
    int TableSize; // capacity
    HashNode<K,V> **table; // pointer to pointer for chaining
};

template<class K, class V>
bool HashTable<K,V>::isPrime(int n) {
    
    if( n == 2 || n == 3 )
        return true;
    
    if( n == 1 || n % 2 == 0 )
        return false;
    
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}

template<class K, class V>
int HashTable<K,V>::nextPrime(int n) {
 
    if ( n % 2 == 0 )
        n++;
    
    for ( ; ! isPrime( n ); n += 2 )
        ;
    
    return n;

}
template<class K, class V>
HashTable<K, V>::HashTable(int tablesize) { // constructor for hash object
    
    TableSize = tablesize;
    
    table = new HashNode<K, V> *[TableSize];
    
    int i = 0;
    
    while(i<TableSize) {
        
        table[i] = NULL;
        
        i++;
    }
    
    // all indexes are NULL at first
    
    unique_words = 0; // since no elements inserted yet
}

template<class K, class V>
V * HashTable<K,V>::elts(K key) { // retrieve the worditem element
    
    int HashIndex = HashCode(key);
    
    V * worditem = NULL;
    
    HashNode<K, V> * ptr = table[HashIndex]; // locate at the initial array
    
    while(ptr != NULL) {
        
        if(ptr -> key == key) {
            
            worditem = &ptr->value;
            
            return worditem;
        }
        
        ptr = ptr -> next;
    }
    
    return worditem;
}

template<class K, class V>
int HashTable<K, V>::HashCode(K key) { // returns hash code
    
    int len = key.length();
    
    int hashvalue = 0; // initally 0
    
    for(int i=0; i<len; i++) {
        
        hashvalue = 37 * hashvalue + key[i];
    }
    
    hashvalue %= TableSize;
    
    if(hashvalue < 0) { // fix negative sum
        
        hashvalue += TableSize;
    }
    
    return hashvalue;
}

template<class K, class V>
void HashTable<K, V>::insert(K key, V value) {
    
    int index = HashCode(key);  // get the hashcode first
    
    HashNode<K, V> * added, * prev = NULL; // to connect and add
    
    added = table[index];
    
    while (added != NULL) {
        
        prev = added;
        
        added = added->next;
    }
    
    // scan the given chain until the end, previous pointer points to the last node
    
    if (added == NULL) {
        
        added = new HashNode<K,V>(key, value);
        
        unique_words++;
        
        if (prev == NULL) {
            
            table[index] = added;
        }
        
        else {
            
            prev->next = added;
        }
        
        if(unique_words > TableSize * 0.75) 
            resize(); // rehashing occurs here
    }
    
    else {
        
        added -> value.word = value.word; // word as key
        added -> value.info = value.info; // DocumentItem vector
    }
}

template<class K, class V>
bool HashTable<K,V>::find(K key) { // return if existent or not
    
    int HashIndex = HashCode(key);
    
    HashNode<K, V> * ptr = table[HashIndex]; // locate at the initial array
    
    while(ptr != NULL) {
        
        if(ptr -> key == key)
            return true;
        
        ptr = ptr -> next;
    }
    
    return false; // if not found initally or in the end, return false
}

template<class K, class V>
void HashTable<K,V>::resize() { // when lambda reaches 0.5, double the array size and create a new one
    
    int prevsize = TableSize, new_size = nextPrime(2 * prevsize); // utilize the prime function here to be fast
    
    // start mapping the old table to the new one
    
    TableSize = new_size; // construct the table again
    
    HashNode<K,V> ** ptr = new HashNode<K,V> * [TableSize];
    
    for (int i = 0; i < TableSize; i++) {
        
        ptr[i] = NULL;
    }
    
    for(int i=0; i<prevsize; i++) { // map the old ones from old
        
        HashNode<K,V> * prev_head = table[i];
        
        for(HashNode<K,V> *temp = prev_head; temp != NULL; temp = temp -> next) { // to the new table
            
            K old_key = temp->key;
            
            V old_value = temp->value;
            
            int new_hash_code = HashCode(old_key);
            
            if(ptr[new_hash_code] == NULL) {
                
                ptr[new_hash_code] = new HashNode<K, V>(old_key, old_value);
                
                ptr[new_hash_code] -> next = NULL; // end the chain here
            }
            
            else { // if again reaches the same index
                
                HashNode<K, V> *prev = ptr[new_hash_code];
                
                HashNode<K, V> * added = prev;
                
                while(added -> next != NULL) { // connect the list after adding to the chain
                    
                    added = added -> next;
                }
                
                HashNode<K, V> *add_chain = new HashNode<K, V>(old_key, old_value);
                
                added -> next = add_chain;
                
                add_chain -> next = NULL;
            }
        }
    }
    
    table = ptr; // pointer to pointer address changed
    
    cout << "rehashed..." << endl;
    
    cout << "previous table size:" << prevsize << ", new table size:" << new_size << ", current unique word count " << unique_words << "," << endl;
    
    cout<< "current load factor:" << loadFactor() << endl;
}









