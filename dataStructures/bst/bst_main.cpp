#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include "bst.h"
using namespace std;

struct DocumentItem {
    
    string docname;
    
    int count;
} ;

struct WordItem {
    
    string word;

    vector<DocumentItem> info;
} ;

string make_upper(string my_str) { // convert all chars to same type in case ASCII differs
    
    for(int i=0; i<my_str.length(); i++) {
        
        my_str[i] = toupper(my_str[i]);
    }
    
    return my_str;
}

 // code taken from strutils.cpp provivded in CS201 SEMESTER and modified to string fucntion instead of void

string StripPunc(string word)
{
    int first = 0;
    int len = word.length();
    
    while (first < len && ispunct(word[first]))
    {
        first++;
    }
    // assert: first indexes either '\0' or non-punctuation
    
    // now find last non-nonpunctuation character
    
    int last = word.length() - 1;  // last char in s
    
    while(last >= 0 && ispunct(word[last]))
    {
        last--;
    }
    word = word.substr(first,last-first+1);
    
    return word;
}

// code taken from strutils.cpp provivded in CS201 SEMESTER and modified to string fucntion instead of void
 
int main() {
    
    int file_num = 0, file_start = 1; // init.
    
    cout << "Enter the number of input files: ";
    
    cin >> file_num; // overwrite
    
    string filename;
    
    vector<string>inputfiles; // store input files
    
    while(file_start <= file_num) {
        
        cout << "Enter " << file_start << ". file name: ";
        
        cin >> filename;
        
        inputfiles.push_back(filename);
        
        file_start++;
    }
    
    bst<WordItem> search_tree; // binary search tree constructed
    
    vector<string>query; // store queried words
    
    string word, line;
    
    cout << "Enter queried words in one line: ";
    
    while(getline(cin, line)) { // query taken from the console, stored in vector
        
        istringstream iss_query(line);
        
        while(iss_query >> word) {
            
            query.push_back(word);
        }
    } // use control + Z or if macuser control + D to break the loop
    
    ifstream input; // open the file
    
    for(int i=0; i<query.size(); i++) { // iterate for each query word
        
        WordItem inserted; // node to be inserted
        
        for(int j=0; j<inputfiles.size(); j++) { // search in each file
            
            input.clear(); // clear possible flags
            
            int wordcount = 0; // counter for occurences
            
            input.open(inputfiles[j].c_str()); // open the file
            
            if(input.fail())
                cout << "Failed to open the file !" << endl; // to see whether continued execution is safe or not
            
            while(getline(input, line)) {
                
                istringstream iss(line);
                
                while(iss >> word) {
                    
                    // strip punctuation if any
                    
                    word = StripPunc(word);
                    word = make_upper(word); // make all chars uppercase
                    
                    if(make_upper(StripPunc(query[i])) == word) { // if word found
                        
                        wordcount++;
                    }
                }
            }
            
            DocumentItem store_details; // struct to hold detailed info
            store_details.count = wordcount;
            store_details.docname = inputfiles[j];
            
            inserted.info.push_back(store_details);
            
            input.close(); // close the file to iterate over loop
        }
        
        inserted.word = query[i];
        
        search_tree.insert(inserted);
    }
    
    // at this point, tree is constructed...
    
    // now, the output...
    
    // linearly scan the query...
    
    for(int i=0; i<query.size(); i++) {
        
        if(search_tree.find(query[i])) { // if tree contains at least one of the query elements
            
            WordItem * ptr = search_tree.elts(query[i]); // found worditem returned
            
            for(int j=0; j<ptr->info.size(); j++) {
                
                cout << "in Document " << ptr->info[j].docname << ", " << ptr->word << " found " << ptr->info[j].count << " times." << endl;
            }
        }
    }

    return 0;
}

