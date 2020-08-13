#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "HashTable.h"
using namespace std;

struct DocumentItem { // value
    
    string docname;
    
    int count;
};

struct WordItem {
    
    string word; // use as key
    
    vector<DocumentItem> info; // value storing vector
};

string make_upper(string my_str) { // convert all chars to same type in case ASCII differs
    
    for(int i=0; i<my_str.length(); i++) {
        
        my_str[i] = toupper(my_str[i]);
    }
    
    return my_str;
}

string make_lower(string my_str) { // for better visualization, taken from class strutils
    
    for(int i=0; i<my_str.length(); i++) {
        
        my_str[i] = tolower(my_str[i]);
    }
    
    return my_str;
}

// taken from class strutils

string separator(string temp) { // for words such as face2face, face.face -> face face(correct form)
    
    int len = temp.length();
    
    for(int i=0; i<len; i++) {
        
        if(!isalpha(temp[i])) {
            
            temp[i] = ' ';
        }
        
        else {
            
            // do nothing
        }
    }
    
    return temp;
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
    } // use control + Z or if mac-user control + D to break the loop
    
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
                    word = separator(word);
                    
                    if(separator(make_upper(StripPunc(query[i]))) == word) { // if word found
                        
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
    
    // hashtable...
    
    HashTable<string, WordItem> table(7); // hashtable constructed
   
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
                    word = separator(word);
                    
                    if(separator(make_upper(StripPunc(query[i]))) == word) { // if word found
                        
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
        
        table.insert(inserted.word, inserted);
    }
    
    cout << "\nAfter preprocessing, the unique word count is " << table.unique() << ". Current load ratio is " << table.loadFactor() << endl;
    
    // at this point, hash is constructed...
    
    // now, the output...
    
    // linearly scan the query...
    
    for(int i=0; i<query.size(); i++) {
        
        if(table.find(query[i])) { // if hashtable contains at least one of the query elements
            
            WordItem * ptr = table.elts(query[i]); // found worditem returned
            
            for(int j=0; j<ptr->info.size(); j++) { // iterate as long as the input file number
                
                cout << "in Document " << ptr->info[j].docname << ", " << separator(make_lower(StripPunc(ptr->word ))) << " found " << ptr->info[j].count << " times." << endl;
            }
        }
    }
    
    // linearly scan the query...

    for(int i=0; i<query.size(); i++) {
        
        if(search_tree.find(query[i])) { // if tree contains at least one of the query elements
            
            WordItem * ptr = search_tree.elts(query[i]); // found worditem returned
            
            for(int j=0; j<ptr->info.size(); j++) {
                
                cout << "in Document " << ptr->info[j].docname << ", " << separator(make_lower(StripPunc(ptr->word ))) << " found " << ptr->info[j].count << " times." << endl;
            }
        }
    }
    
    // now for time measurements...
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < query.size(); i++)
    {
        search_tree.find(query[i]);  // QueryDocuments (with bst);
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds> // bst time
    (std::chrono::high_resolution_clock::now() - start).count();
    cout << "\nTime: " << BSTTime / query.size() << "\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < query.size(); i++)
    {
        table.find(query[i]); // QueryDocuments (with hashtable);
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds> // hashtime
    (std::chrono::high_resolution_clock::now() - start).count();
    cout << "\nTime: " << HTTime / query.size() << "\n";
    double time_ratio = (double)BSTTime / (double)HTTime;
    cout << "Speed up: " << time_ratio << "\n";

    return 0;
}

