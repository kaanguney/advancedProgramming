#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "stack.h"
#include "member.cpp"
using namespace std;

struct coordinates {
    
    int x, y;
};

bool found(Stack<coordinates> visited, Stack<coordinates> inputs) { // element previously visited or not
    
    coordinates search = inputs.top();
    
    while(!visited.isEmpty()) {
        
        if(visited.top().x == search.x && visited.top().y == search.y) {
            
            return true;
        }
        
        visited.pop();
    }
    
    return false;
}

void output(Stack<coordinates> & visited, Stack<coordinates> & inputs) {
    
    coordinates path = inputs.top(); // goto coordinate
    
    if(visited.isEmpty()) {
        
        cout << "Moving to (" << path.x << ", " << path.y << ")" << endl;
        
        int i = 0, j = 0;
        
        while(i < path.x) {
            
            coordinates visit;
            
            i++;
            
            visit.x = i;
            visit.y = j;
            
            cout << "(" << i << ", " << j << ")" << endl;
            
            visited.push(visit);
        }
        
        while(j < path.y) {
            
            coordinates visit2;
            
            j++;
            
            visit2.x = i;
            visit2.y = j;
            
            if(j == path.y && i == path.x) {
                
                cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
            }
            
            else {
                
                cout << "(" << i << ", " << j << ")" << endl;
            }
            
            visited.push(visit2);
        }
    }
    
    else { // after the first input
        
        bool exist = found(visited, inputs);
        
        if(exist) {
            
            cout << "Time travel back to (" << path.x << ", " << path.y << ")" << endl;
            
            while(visited.top().x != path.x || visited.top().y != path.y) {
                
                visited.pop();
            }
        }
        
        else {
            
            cout << "Moving to (" << path.x << ", " << path.y << ")" << endl;
            
            int targetx = visited.top().x; // 5
            int targety = visited.top().y; // 4
            
            if(targetx < path.x) {
                
                while(targetx < path.x) {
                    
                    coordinates coord;
                    
                    targetx++;
                    
                    coord.x = targetx;
                    coord.y = targety;
                    
                    if(targetx == path.x && targety == path.y) {
                        
                        cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                    }
                    
                    else {
                        
                        cout << "(" << targetx << ", " << targety << ")" << endl;
                    }
                    
                    visited.push(coord);
                }
                
                if(targety < path.y) {
                    
                    while(targety < path.y) {
                        
                        coordinates coord;
                        
                        targety++;
                        
                        coord.x = targetx;
                        coord.y = targety;
                        
                        if(targetx == path.x && targety == path.y) {
                            
                            cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                        }
                        
                        else {
                            
                            cout << "(" << targetx << ", " << targety << ")" <<  endl;
                        }
                        
                        visited.push(coord);
                    }
                }
                
                else if(targety > path.y) {
                    
                    while(targety > path.y) {
                        
                        coordinates coord;
                        
                        targety--;
                        
                        coord.x = targetx;
                        coord.y = targety;
                        
                        if(targetx == path.x && targety == path.y) {
                            
                            cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                        }
                        
                        else {
                            
                            cout << "(" << targetx << ", " << targety << ")" <<  endl;
                        }
                        
                        visited.push(coord);
                    }
                }
            }
            
            else if(targetx > path.x){
                
                while(targetx > path.x) {
                    
                    coordinates coord;
                    
                    targetx--;
                    
                    coord.x = targetx;
                    coord.y = targety;
                    
                    if(targetx == path.x && targety == path.y) {
                        
                        cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                    }
                    
                    else {
                        
                        cout << "(" << targetx << ", " << targety << ")" << endl;
                    }
                    
                    visited.push(coord);
                }
                
                if(targety < path.y) {
                    
                    while(targety < path.y) {
                        
                        coordinates coord;
                        
                        targety++;
                        
                        coord.x = targetx;
                        coord.y = targety;
                        
                        if(targetx == path.x && targety == path.y) {
                            
                            cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                        }
                        
                        else {
                            
                            cout << "(" << targetx << ", " << targety << ")" <<  endl;
                        }
                        
                        visited.push(coord);
                    }
                }
                
                else if(targety > path.y) {
                    
                    while(targety > path.y) {
                        
                        coordinates coord;
                        
                        targety--;
                        
                        coord.x = targetx;
                        coord.y = targety;
                        
                        if(targetx == path.x && targety == path.y) {
                            
                            cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                        }
                        
                        else {
                            
                            cout << "(" << targetx << ", " << targety << ")" <<  endl;
                        }
                        
                        visited.push(coord);
                    }
                }
            }
            
            else { // targetx = path.x
                
                if(targety < path.y) {
                    
                    while(targety < path.y) {
                        
                        coordinates coord;
                        
                        targety++;
                        
                        coord.x = targetx;
                        coord.y = targety;
                        
                        if(targetx == path.x && targety == path.y) {
                            
                            cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                        }
                        
                        else {
                            
                            cout << "(" << targetx << ", " << targety << ")" <<  endl;
                        }
                        
                        visited.push(coord);
                    }
                }
                
                else if(targety > path.y) {
                    
                    while(targety > path.y) {
                        
                        coordinates coord;
                        
                        targety--;
                        
                        coord.x = targetx;
                        coord.y = targety;
                        
                        if(targetx == path.x && targety == path.y) {
                            
                            cout << "Arrived to (" << path.x << ", " << path.y << ")" << endl;
                        }
                        
                        else {
                            
                            cout << "(" << targetx << ", " << targety << ")" <<  endl;
                        }
                        
                        visited.push(coord);
                    }
                }
            }
        }
    }
}

int main() {
    
    ifstream input;
    
    string filename;
    
    cout << "Please enter the filename : ";
    
    cin >> filename;
    
    input.open(filename.c_str());
    
    while(input.fail()) { // in case file does not open correctly
        
        cout << "\nIncorrect filename !" << endl << endl;
        
        cout << "Please enter the filename again : ";
        
        cin >> filename;
        
        input.open(filename.c_str()); // try to open the file again
    }
    
    cout << "\nSuccessfully opened the file !" << endl << endl;
    
    string line;
    
    coordinates coord;
    
    Stack<coordinates> inputs; // inputs stored
    
    Stack<coordinates> visited; // all paths on the way
    
    while(getline(input, line)) {
        
        istringstream iss(line);

        while(iss >> coord.x >> coord.y) {
            
            inputs.push(coord);
            
            output(visited, inputs);
        }
    }
    
    // now, return home
    
    cout << "Back to (0, 0)" << endl;
    
    // pop the initial
    
    visited.pop();
    
    while(!visited.isEmpty()) {
        
        cout << "(" << visited.top().x << ", " << visited.top().y << ")" << endl;
        
        visited.pop();
    }
    
    cout << "Home sweet home" << endl;
    
    // res the file here just in case
    
    input.clear();
    
    input.seekg(0);
    
    return 0;
}
