#include <iostream>
#include <fstream>
#include <sstream>
#include "DynIntStack.h"

using namespace std;

void identation(DynIntStack & pystack, bool & check, int & level, bool & stop_analysis, string & word, bool & proceed, bool & success) { // keyword exists or not -> current level, this line...
    
    if(check) { // keyword exists...
        
        int num; // popped value...
        
        static int count = 0;
        
        pystack.pop(num);
        
        if(num < level && count != 0) { // correctly idented with a new identation level...
            
            cout << "This line proceeds a keyword containing line." << endl;
            
            cout << "Current Level = " << num << " This Line = " << level << endl;
            
            cout << "Keyword " << word << " found on this block." << endl;
            
            pystack.push(num); // push the previous level, too...

            pystack.push(level); // new identation level...
            
            cout << endl;
        }
        
        else if(num == level) {
            
            cout << "Current Level = " << num << " This Line = " << level << endl;
            
            cout << "Line belongs to current block." << endl;
            
            cout << "Keyword " << word << " found on this block." << endl;
            
            cout << endl;
            
            pystack.push(level); // again push the level inside...
        }
        
        else if(num > level) {
            
            pystack.push(num);
            
            cout << "Current Level = " << num << " This Line = " << level << endl;
            
            cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;
            
            while(num != level) {
                
                pystack.pop(num);
            }
            
            cout << "Current Level = " << num << " This Line = " << level << endl;
            
            cout << "Line belongs to the outer block." << endl;
            
            cout << "Keyword " << word << " found on this block." << endl;
            
            cout << endl;
            
            pystack.push(level);
        }
        
        else if(count == 0 && level > num) { // only for first iteration...
            
            cout << "Current Level = " << num << " This Line = " << level << endl;
            
            cout << "Keyword " << word << " found on this block." << endl;
            
            cout << "Incorrect file structure." << endl;
            
            cout << "Current line cannot be greater than the Current indentation level." << endl;
            
            stop_analysis = true; // error handling...
            
            success = false; // not all iterations are successful...
        }
        
        count++;
    }
    
    else {
        
        int num; // popped value...
        
        pystack.pop(num);
        
        if(num == level) {
            
            cout << "Current Level = " << num << " This Line = " << level << endl;
            
            if(proceed) {
                
                cout << "This line proceeds a keyword containing line." << endl;
                
                cout << "Incorrect file structure." << endl;
                
                cout << "Current line cannot be greater than the Current indentation level." << endl;
                
                stop_analysis = true; // error handling...
                
                success = false; // not all iterations are successful...
                
                proceed = false;
            }
            
            else {
                
                cout << "Line belongs to current block." << endl;
            }
            
            pystack.push(level); // again push the level inside...
            
            cout << endl;
        }
        
        else if(num > level) {
            
            cout << "Current Level = " << num << " This Line = " << level << endl;
            
            while(num != level && !pystack.isEmpty()) {
                
                pystack.pop(num);
                
                cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;
                
                cout << "Current Level = " << num << " This Line = " << level << endl;
                
                if(level > num) {
                    
                    cout << "Incorrect file structure." << endl;
                    
                    cout << "An indentation level same as the Current line is not found in outer blocks." << endl;
                    
                    stop_analysis = true;
                    
                    success = false; // not all iterations are successful...
                    
                    break;
                }
            }
            
            pystack.push(num);
            
            if(!stop_analysis) {
                
                cout << "Line belongs to the outer block." << endl;
            }
            
            cout << endl;
        }
        
        else if(num < level) {
            
            if(proceed) {
                
                pystack.push(num);
                
                pystack.push(level);
                
                cout << "This line proceeds a keyword containing line." << endl;
                
                cout << "Current Level = " << num << " This Line = " << level << endl;
                
                cout << "Line correct. Depth " << level << " added to the stack." << endl;
        
                proceed = false;
                
                cout << endl;
            }
            
            else {
                
                pystack.push(num);
                
                cout << "Current Level = " << num << " This Line = " << level << endl;
                
                cout << "Line correct. Depth " << level << " added to the stack." << endl;
                
                pystack.push(level);
                
                proceed = false;
                
                cout << endl;
            }
        }
    }
}

int main() {
    
    bool success = true; // to end the program...
    
    string filename;
    
    bool stop_analysis = false; // control analysis...
    
    cout << "Please enter the file name that is going to be analyzed." << endl;
    
    cin >> filename;
    
    ifstream input; // open and read the file...
    
    input.open(filename.c_str());
    
    while(input.fail()) { // ask again if fails to open the file...
        
        cout << "Please enter the file name that is going to be analyzed." << endl;
        
        cin >> filename;
        
        input.open(filename.c_str()); // open again...
    }
    
    // file opened successully...
    
    cout << "Starting file analysis..." << endl;
    
    cout << "Initial indentation level is pushed to the stack as 0.\n\n";
    
    // creating dynamic stack...
    
    DynIntStack pystack;

    // start processing the file...
    
    string line, word;
    
    bool check; // check keyword appearance...
    
    int line_count = 0; // count the lines...
    
    pystack.push(0);  // push the initial level to the stack...
    
    bool proceed = false; // for keyword proceeders...
    
    while(getline(input, line)) {

        line_count++;
        
        int level = 0; // current line's identation...
        
        cout << "Line number: " << line_count << endl;
        
        cout << "Line: " << line << endl;
        
        // take the word on the line now...
        
        istringstream iss(line);
        
        iss >> word;
        
        if(word == "for" || word == "if" || word == "elif" || word == "while" || word == "else") { // keyword observed...
            
            check = true;
            
            proceed = true;
        }
        
        else {
            
            check = false; // keyword non-existent...
        }
        
        // iterate over the line char by char...
        
        int len = line.length();
        
        for(int i=0; i<len; i++) {
            
            if(line[i] == ' ') { // count spaces in a line...
                
                level++;
            }
            
            else {
                
                break;
            }
        } // spaces counted in a line...
        
        cout << level << " number of spaces observed before the start of the line." << endl;
        
        identation(pystack, check, level, stop_analysis, word, proceed, success); // call the identation function here...
        
        if(stop_analysis) { // end execution...
            
            cout << "Stopping file analysis..." << endl;
            
            // do not forget to empty the stack...
            
            int empty;
            
            while(!pystack.isEmpty()) {
                
                pystack.pop(empty);
            }
            
            cout << "\nStack emptied and program ending." << endl;
            
            break;
        }
    }
    
    // end execution if iterations are all successful, stop analysis is false...
    
    if(success) {
        
        cout << "Finished file analysis. File structure is correct!" << endl;
        
        // do not forget to empty the stack...
        
        int empty;
        
        while(!pystack.isEmpty()) {
            
            pystack.pop(empty);
        }
        
        cout << "Stack emptied and program ending." << endl;
    }
    
    return 0;
}

