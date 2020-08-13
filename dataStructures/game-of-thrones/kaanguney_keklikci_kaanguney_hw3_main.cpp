
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "kaanguney_keklikci_kaanguney_hw3.h"

using namespace std;

int main() {      
    
    ifstream input;
    
    string filename;
    
    cout << "Please enter a file name." << endl;
    
    cin >> filename;
    
    input.open(filename.c_str());  // open the file first...
    
    while(input.fail()) {
        
        cout << "Please enter a file name." << endl;
        
        cin >> filename;
        
        input.open(filename.c_str()); // try again...
    }
    
    cout << "Successfully opened file " << filename << endl << endl;
    
    // process the file...
    
    string line, h_name, n_name; // read housename first, then read the neighbourname...
    
    linkedlist house;  // for houses-linkedlist...
    
    bool check_h_name; // for house-name check...
    
    bool check_n_name; // for neighbour-house check...
    
    cout << "######## TOPOLOGY ########" << endl << endl;
    
    while(getline(input, line)) {
        
        istringstream iss(line);
        
        while(iss >> h_name >> n_name) {
            
            bool message = false; // for output...
            
            cout << "Processing " << h_name << ", " << n_name << endl;
            
            check_h_name = house.hnExists(h_name); // check if house added is previously existent...
            
            if(!check_h_name) { // house seen first time...
                
                house.addHouseNode(h_name); // house name added...
                
                check_n_name = house.nnExists(h_name, n_name); // check the first house's neighbours...
                
                if(!check_n_name) { // if first time appearence...
                    
                    house.addNeighborNode(h_name, n_name);
                    
                    message = true;
                }
                
                check_h_name = house.hnExists(n_name); // check if the neighbour appeared before as a house...
                
                if(!check_h_name) {
                    
                     house.addHouseNode(n_name); // add another house with the neighbour's name...
                    
                     // check the neighbours of the reverse order...
                    
                    check_n_name = house.nnExists(n_name, h_name);
                    
                    if(!check_n_name) { // add the neighbour of the second house...
                        
                         house.addNeighborNode(n_name, h_name);
                        
                         message = true;
                    }
                }
                
                else { // neighbour appeared as a house before...
                    
                    // check its neighbours...
                    
                    check_n_name = house.nnExists(n_name, h_name);
                    
                    if(!check_n_name) { // if neighbour not appeared, add...
                        
                        house.addNeighborNode(n_name, h_name);
                        
                        message = true;
                    }
                }
                
                if(message) {
                    
                    cout << "Topology information successfully added." << endl << endl;
                }
                
                else {
                    
                    cout << "Redundant information! An entry with " << h_name << " and " << n_name << " is already processed." << endl << endl;
                }
            }
                
            else { // house seen before...
                
                // check neighbours...
                
                check_n_name = house.nnExists(h_name, n_name);
                
                if(!check_n_name) {
                    
                    house.addNeighborNode(h_name, n_name);
                    
                    message = true;
                }
                
                // check the reverse order...
                
                check_h_name = house.hnExists(n_name); // check if the neighbour appeared before as a house...
                
                if(!check_h_name) {
                    
                    house.addHouseNode(n_name); // add another house with the neighbour's name...
                    
                    // check the neighbours of the reverse order...
                    
                    check_n_name = house.nnExists(n_name, h_name);
                    
                    if(!check_n_name) { // add the neighbour of the second house...
                        
                        house.addNeighborNode(n_name, h_name);
                        
                        message = true;
                    }
                }
                
                else { // neighbour appeared as a house before...
                    
                    // check its neighbours...
                    
                    check_n_name = house.nnExists(n_name, h_name);
                    
                    if(!check_n_name) { // if neighbour not appeared, add...
                        
                        house.addNeighborNode(n_name, h_name);
                        
                        message = true;
                    }
                }
                
                if(message) {
                    
                    cout << "Topology information successfully added." << endl << endl;
                }
                
                else {
                    
                    cout << "Redundant information! An entry with " << h_name << " and " << n_name << " is already processed." << endl << endl;
                }
            }
        }
    }
    
    // map construction over, print the map now...
 
    cout << "\n######## MAP ########" << endl << endl;
    
    house.printAll(); // print the map...
    
    // now, continue with options...
    
    cout << endl << endl;
    
    bool option = true; // iterate until exit...
    
    int user_input;

    bool house_check1 = false; // annexation first house entry...
    
    bool house_check2 = false; // annexation second house entry...
    
     bool house_check3 = false; // check annexed...
    
    while(option) {
        
       cout << "Please select an option [1-2-3]." << endl;

       cout << "1. Annexation! War for the iron throne continues..." << endl;
       
       cout << "2. Tyrion must travel, do a path check for the famous imp." << endl;
       
       cout << "3. Exit" << endl;
        
       cin >> user_input;
        
       if(user_input == 1) { // annexation...
           
           string annexer, annexed;
           
           cout << "Please enter two houses first the annexer and the annexed. (ex: Tyrell Stark)."  << endl;
           
           cin >> annexer >> annexed;
           
           if(annexer == annexed) {    // same house entries...
               
               cout << "A House cannot conquer itself!" << endl;
               
               cout << "Update failed." << endl;
               
               cout << endl;
               
               continue; // skip other steps...
           }
           
           house_check1 = house.hnExists(annexer);
           
           if(house_check1) {
               
               house_check2 = house.nnExists(annexer, annexed);
               
               house_check3 = house.hnExists(annexed);
               
               if(house_check1 && house_check2) { // entries valid...
                   
                   cout << annexer << " conquered " << annexed << "!" << endl;
                   
                   // remove annexed's name from annexer first...
                   
                   house.remove(annexer, annexed);
                   
                   // before deletion, add necessary nodes to the annexer form annexed...
                   
                   house.annexation_add(annexer, annexed);
                   
                   // now, delete...
                   
                   house.delete_annexed(annexer, annexed);
                   
                   house.change(annexer, annexed); // update the list...
                   
                   house.removedup(); // to remove duplicates after update...
                   
                   house.printAll(); // display map after annexation...
                   
                   continue;
               }
               
               else { // false cases...
                   
                   if(!house_check3) {
                       
                       cout << annexed << " does not exist." << endl;
                       
                       cout << "Update failed." << endl;
                       
                       cout << endl;
                       
                       continue;
                   }
                   
                   else if(!house_check2) {
                       
                       cout << "A house can only conquer a neighboring house! " << annexed << " is not a neighbor of " << annexer << "." << endl;
                       
                       cout << "Update failed." << endl;
                       
                       cout << endl;
                       
                       continue;
                   }
               }
           }
           
           else {
               
               cout << annexer << " does not exist." << endl;
               
               cout << "Update failed." << endl;
               
               cout << endl;
               
               continue;
           }
       }
        
       else if(user_input == 2) { // tyrion travel...
           
           string path;
        
           string word1, word2, temp;
           
           int count = 0;
           
           bool check_n = false; // check neighbours...
           
           bool check_path = false; // success or failure...

           cout << "Please enter a path. (ex: Tyrell Martell Tully)" << endl;
           
           cin.ignore();
           
           while(getline(cin, path)) {
               
               istringstream iss(path);
               
               while(iss >> word1) {
                   
                   int start=0;
                   
                   istringstream iss2(path);
                   
                   while(iss2>>temp) {
                       
                       if(start==count+1) {
                           
                           word2=temp;
                           
                           break;
                       }
                       word2 = " "; // reset...
                       
                       start++; // begin again...
                       
                   }
                   
                   if(house.hnExists(word1) == false) {
                       
                       cout << word1 << " does not exist in the map." << endl;
                       
                       break;
                   }
                   
                   check_n = house.nnExists(word1, word2);
                   
                   if(word2!= " "){ // if reset...
                       
                       if(word1 == word2) { // if same house entered twice...
                           
                           cout << "You are already in " << word1 << endl;
                           
                           check_path = true;
                       }
                       
                       else if(!check_n) {
                           
                           cout << word2 << " is not a neighbor of " << word1 << endl;
                           
                           check_path = false;
                           
                           break;
                       }
                   
                       else {
                           
                           cout << "Path found between " << word1 << " and " << word2 << endl;
                           
                           check_path = true;
                       }
                   }
                   
                   count++;
               }
               
               if(check_path) {
                   
                   cout << "Path search succeeded." << endl;
               }
               
               else {
                   
                   cout << "Path search failed." << endl;
               }
               
               break;
           }
           
            cout << endl;
           
            continue;
       }
        
       else if(user_input == 3) { // exit the loop...
           
           cout << "List deleted and program ended." << endl;
           
           house.deleteAll();   // clean up the data...
                    
           option = false;
       }
        
       else if(user_input < 1 || user_input > 3) { // in case user input fails...
            
            cout << "Invalid option please select from the menu." << endl;
            
            continue;
        }
    }
    
    return 0;
}

// KAAN GÜNEY KEKLİKÇİ - 24986 HW 3 COMPLETE... //
