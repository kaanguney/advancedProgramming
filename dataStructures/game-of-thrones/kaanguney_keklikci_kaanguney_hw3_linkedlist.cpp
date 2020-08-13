
#include "kaanguney_keklikci_kaanguney_hw3.h"
#include <iostream>
#include <string>

using namespace std;

linkedlist::linkedlist() { // constructor...
    
   head = NULL;
}

void linkedlist::addHouseNode(string hname) {
    
    houseNode *ptr = head;
    
    if(ptr == NULL) { // first house-node added...
        
        houseNode *new_house;
        
        new_house = new houseNode;
        
        new_house -> houseName = hname;
        
        new_house -> next = NULL;
        
        head = new_house;
    }
    
    else {
        
        ptr = head;
        
        while(ptr -> next != NULL) { // find the last house of the current list...
            
            ptr = ptr -> next;
        }
        
        houseNode *new_house; // construct the new-house...
        
        new_house = new houseNode;
        
        new_house -> houseName = hname;
        
        new_house -> next = NULL;
        
        ptr -> next = new_house; // now, add to the current house list...
    }
}

bool linkedlist::hnExists(string hname) {
    
    houseNode *ptr = head;
    
    while (ptr != NULL) {
        
        if (ptr->houseName == hname) {
            
            return true; // if exists...
        }
        
        ptr = ptr->next;
    }
    
    return false; // if non-existent...
}

void linkedlist::addNeighborNode(string hname, string nname) {
    
    bool found = hnExists(hname); // if housename existent or not...
    
    if(found) { // house found, add its neighbour...
        
        houseNode *ptr = head;
        
        while(ptr != NULL) { // get to the the relevant pointer...
            
            if(ptr -> houseName == hname) {
                
                break;
            }
            
            ptr = ptr -> next;
        }
        
        if(ptr -> neighborListHead == NULL) { // if it's the first element to be added to the other dimension...
            
            neighborNode *nptr;
            
            nptr = new neighborNode;
            
            nptr -> neighborName = nname;
            
            nptr -> next = NULL;
            
            ptr -> neighborListHead = nptr;
        }
        
        else { // neighbourlisthead is not NULL anymore...
            
            neighborNode *new_neighbour; // construct the new neighbour...
                
            new_neighbour = new neighborNode;
                
            new_neighbour -> neighborName = nname;
            
            neighborNode *point = ptr -> neighborListHead;
            
            while(point -> next != NULL) {    // scan the neighbours and connect...
                
                point = point -> next;
            }
            
            new_neighbour -> next = NULL;
            
            point -> next = new_neighbour;
        }
    }
}

bool linkedlist::nnExists(string hname, string nname) {
    
    bool check = false;
    
    houseNode *ptr = head; // first get to the relevant house...
    
    while(ptr != NULL) {
        
        if(ptr -> houseName == hname) {
            
            break;
        }
        
        ptr = ptr -> next;
    }
    
    // relevant house found...
    
    neighborNode *p = ptr -> neighborListHead;
    
    while(p != NULL) {
        
        if(p-> neighborName == nname) {
            
            return !check; // neighbour exists...
        }
        
        p = p-> next;
    }
    
    return check;
}

void linkedlist::printAll() {
    
    houseNode *ptr = head;
    
    while(ptr != NULL) {
        
        cout << ptr -> houseName << ": ";
        
        neighborNode *nptr = ptr -> neighborListHead;
        
        while(nptr != NULL) {
            
            cout << nptr -> neighborName << ", ";
            
            nptr = nptr -> next;
        }
        
        cout << endl;
        
        ptr = ptr -> next;
    }
}
    
void linkedlist::annexation_add(string annexer, string annexed) {
    
    houseNode *house = head;
    
    while(house != NULL) {   // annexed found as a house, now add the necessary nodes to the annexer...
        
        if(house -> houseName == annexed) {
            
            break;
        }
        
        house = house -> next;
    }
    
    houseNode *myptr = head;
    
    while(myptr != NULL) {    // find annexer...
        
        if(myptr -> houseName == annexer) {
            
            break;
        }
    
        myptr = myptr -> next;
    }
    
    // annexer found...
    
    // now, add...

    neighborNode *scan_annexed = house -> neighborListHead;
    
    neighborNode *scan_annexer = myptr -> neighborListHead;
    
    neighborNode *connect_new = myptr -> neighborListHead;
    
    bool exist = false; // check the nodes...
    
    while(scan_annexed != NULL) {
        
        scan_annexer = myptr -> neighborListHead;
        
        while(scan_annexer != NULL) {
            
            if(scan_annexed -> neighborName != scan_annexer -> neighborName) {
                
                exist = false;
            }
            
            else {
                
                exist = true;
                
                break;
            }
            
            scan_annexer = scan_annexer -> next;
        }
        
        if(!exist) { // if node to be added...
            
            if(annexer != scan_annexed -> neighborName) { // if annexer's name is in annexed's neigbours list...
                
                neighborNode *new_node = new neighborNode;
                
                new_node -> neighborName = scan_annexed -> neighborName;
                
                while(connect_new -> next != NULL) {
                    
                    connect_new = connect_new -> next;
                }
                
                connect_new -> next = new_node;
                
                new_node -> next = NULL;
            }
        }
        
        scan_annexed = scan_annexed -> next;
    }
}

void linkedlist::delete_annexed(string annexer, string annexed) {
    
    houseNode *ptr = head;
    
    while(ptr != NULL) { // find the annexer, then the annexed...
        
        if(ptr -> houseName == annexer) { // annexer found...
            
            break;
        }
        
        ptr = ptr -> next;
    }
    
    houseNode *house = head;
    
    while(house != NULL) {
        
        if(house -> houseName == annexed) {
            
            break;
        }
        
        house = house -> next;
    }
    
    neighborNode *point = house -> neighborListHead; // delete annexed from the map...
    
    while(point != NULL) {
        
        neighborNode *temp = point -> next;
        
        delete point;
        
        point = temp;
    }
    
    // now, finally delete the head of the house...
    
    houseNode *pointer = head;
    
    if(pointer -> houseName == annexed) {
        
        head = pointer -> next;
        
        delete pointer;
    }
    
    else {
        
        while(pointer -> next -> houseName != annexed) { // connect prev and next first...
            
            pointer = pointer -> next;
        }
        
        // prev found -> pointer...
        
        // house is the head...
        
        pointer -> next = house -> next; // rest of the list connected...
        
        delete house;
    }
}

void linkedlist::deleteAll() {
    
    houseNode *ptr = head;
    
    while(ptr != NULL) {
        
        neighborNode *ptr2 = ptr -> neighborListHead; // head of neighbours for each head...
        
        while(ptr2 != NULL) {
            
            neighborNode *temp = ptr2 -> next;
            
            ptr -> neighborListHead = temp;
            
            delete ptr2;
            
            ptr2 = ptr2 -> next;
        }
        
        ptr = ptr -> next;
    }
    
    // neighbours deleted, now delete the house list...
    
    houseNode *myptr = head;
    
    while(myptr != NULL) {
        
        houseNode *temp = myptr -> next;
        
        delete myptr;
        
        head = temp;
        
        myptr = myptr -> next;
    }
    
    // housenodes deleted...
}

void linkedlist::remove(string annexer, string annexed) {
    
    houseNode *ptr = head;
    
    while(ptr != NULL && ptr -> houseName != annexer) {
        
        ptr = ptr -> next;
    }
    
    // annexer found...
    
    neighborNode *n2= ptr -> neighborListHead;
    
    while(n2!=NULL && n2 -> neighborName != annexed) { // annexed found...
        
        n2 = n2 -> next;
    }
    
    if(n2-> next != NULL) {
        
        neighborNode *n = ptr -> neighborListHead;
        
        if(n2 != ptr -> neighborListHead) {
            
            while(n -> next != NULL && n -> next -> neighborName != annexed) {
                
                n = n -> next;
            }
            
            // prev found..
        }
        
        if(n2 == ptr -> neighborListHead) { // if it's head...
            
            ptr -> neighborListHead = n2 -> next;
            
            delete n2;
        }
        
        else if(n2 -> next == NULL) { // if it's the last item...
            
            n-> next = NULL;
            
            delete n2;
        }
        
        else {
            
            n -> next = n2 -> next;
            
            delete n2;
        }
        
    }
}

void linkedlist::change(string annexer, string annexed) {
    
    houseNode *ptr = head;
    
    while(ptr!=NULL) {
        
        neighborNode *nptr = ptr -> neighborListHead;
        
        while(nptr!=NULL) {
            
            if(nptr -> neighborName == annexed) {
                
                nptr -> neighborName = annexer;
                
                break;
            }
            
            nptr = nptr -> next;
        }
        
        ptr = ptr -> next;
    }
}

void linkedlist::removedup() {
    
    houseNode *ptr = head;
    
    neighborNode *ptr1,  *ptr2, *dup;
    
    ptr1 = ptr -> neighborListHead;

    while (ptr1 != NULL && ptr1->next != NULL) {
        
        ptr2 = ptr1;
        
        while (ptr2->next != NULL) {
            
            if (ptr1-> neighborName == ptr2->next->neighborName) {
                
                dup = ptr2->next;
                
                ptr2->next = ptr2->next->next;
                
                delete(dup);
            }
            
            else {
                
                ptr2 = ptr2->next;
            }
        }
        
        ptr1 = ptr1->next;
    }
}
