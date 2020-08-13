#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// create a struct for linked list...

struct node {
    
    string driver_name;
    
    int laptime;
    
    node *next;
} ;


/* Begin: code taken from pointers-linkedlists.ppt */

void DeleteOneNode (node * toBeDeleted, node * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
 post: deletes the node pointed by toBeDeleted, updates head if changes */
{
    node * ptr;
    if (toBeDeleted == head)  //if the node to be deleted is the first node
    {     head = head->next;
        delete toBeDeleted;
    }
    else  //if the node to be deleted is in the middle or at the end
    {     ptr = head;
        while (ptr->next != toBeDeleted)
            ptr = ptr->next;
        //after while, ptr points to the node just before toBeDeleted
        
        //connect the previous node to the next node and delete
        ptr->next = toBeDeleted->next;
        delete toBeDeleted;
    }
}

/* End: code taken from pointers-linkedlists.ppt */

void update_list(node *& head, int time, string name) {
    
    node *ptr = head;
    
    int count = 0;
    
    while(ptr != NULL) {
        
        if(ptr -> driver_name == name) {
            
            count++;
            
            if(count == 2) { // if a name is seen for the second time, delete it...

                DeleteOneNode(ptr, head);
                
                break;
            }
        }
    
        ptr = ptr -> next;
    }
}

/* Begin: code taken from pointers-linkedlists.ppt and updated... */

node * add_node(node *head, string name, int time) { // adds node to the linked list and returns the new head of the list...
    
    node *ptr = head;
    
    static int dash = 0; // this loop will only execute once for the output...
    
    if(dash == 0) {
        
        cout << "###############################" << endl;
        
        cout << "Qualifying Laps:" << endl;
        
        cout << "###############################" << endl;
    }
    
    if(head == NULL || time < head -> laptime) { // if the added node is the new head...
        
        node *temp;
        
        temp = new node;
        
        temp -> laptime = time;
        
        temp -> driver_name = name;
        
        temp -> next = head;
        
        cout << temp -> driver_name << " completed the lap in " << temp -> laptime << " milliseconds" << endl;
        
        dash++;
        
        return temp;
    }
    
    while(ptr -> next != NULL && ptr->next->laptime <= time) { // check one node ahead...
        
        ptr = ptr -> next;
    }
    
    node *temp;
    
    temp = new node;
    
    temp -> laptime = time;
    
    temp -> driver_name = name;
    
    cout << temp -> driver_name << " completed the lap in " << temp -> laptime << " milliseconds" << endl;
    
    temp -> next = ptr -> next;
    
    ptr -> next = temp;
    
    return head;
}

/* End: code taken from pointers-linkedlists.ppt and updated... */

int main() {
    
    // start of by reading the 1st txt file...
    
    ifstream input;
    
    string filename;
    
    cout << "Please enter a filename." << endl;
    
    cin >> filename;
    
    input.open(filename.c_str());
    
    while(input.fail()) {  // if file could not be opened...
        
        cout << "Unable to open file " << filename << endl;
        
        cout << "Please enter a different filename." << endl;
        
        cin >> filename;
        
        input.open(filename.c_str());
    }
    
    // if file opened...
    
    cout << "Successfully opened file " << filename << "\n" << endl;
    
    string line;
    
    string word;
    
    int lap_time;

    node *head = NULL; // head of my linked list...
    
    while(getline(input, line)) {  // read the file...
        
        istringstream iss(line);
        
        while(iss >> word >> lap_time) { // get the driver name and laptime...
            
            head = add_node(head, word, lap_time); // new head returned...
            
            update_list(head, lap_time, word); // update the linked list...
            
            // cout the personal bests...
            
            int count = 1;
            
            node *pointer = head;
            
            while(pointer != NULL) {
                
                if(pointer -> driver_name == word) {
                    
                    break;
                }
                
                pointer = pointer -> next;
                
                count++;
            }
            
            cout << pointer -> driver_name << ": current personal best is " << pointer -> laptime << "; current position is " << count << endl;
            
        }
    }
    
    cout << "\n";
    
    cout << "###############################" << endl;
    
    cout << "Results:" << endl;
    
    cout << "###############################" << endl;
    
    node *ptr = head;
    
    int order = 1; // orderly print the results...
    
    while(ptr != NULL) {
        
        cout << order << ". " << ptr -> driver_name << " " << ptr -> laptime << endl;
        
        ptr = ptr -> next;
    
        order++;
    }
    
    /* Begin: code taken from pointers-linkedlists.ppt and updated... */
    
    // delete all nodes before the end of execution...
    
    node *clear_list;
    
    while (head != NULL) {
        
        clear_list = head->next;
        
        delete head;
        
        head = clear_list;
    }
    
    // nodes deleted, list cleared...
    
    /* End: code taken from pointers-linkedlists.ppt and updated... */
    
    return 0;
}


