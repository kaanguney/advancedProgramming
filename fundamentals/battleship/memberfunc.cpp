#include "myboard.h"
#include "players.h"
#include <iostream>
#include <iomanip> // for setw
using namespace std;


myboard::myboard() { // default constructor for myboard.h, initialize all to zero...
    
    for(int i=0; i<6; i++) {
        
        for(int j=0; j<6; j++) {
            
            theBoard[i][j] = 0;
        }
    }
}

void myboard::displayBoard() {
    
    cout << "Board:" << endl;
    
    cout << "      ";
    
    for(int i=1; i<=2; i++) {
        
        cout << "P" << i;
        
        if(i==1) {
            
            cout << "       |";
        }
        
        cout << "      ";
    }
    
    cout << endl;
    
    for(int i=0; i<6; i++) {
    
        for(int j=0; j<6; j++) {
            
            if(j==3) {
                
                cout << "   |";
            }
        
            cout << setw(4) << theBoard[i][j];
        }
        
        cout << endl;
    }
}

players::players(myboard &board, int ID)  // default constructor for players.h

:player_board(board), playerID(ID)

{ }

bool myboard::putShip(int playerID, int shipID, int rowStart, int colStart, int rowEnd, int colEnd) {
    
    if(!(shipID == 1 || shipID == 2)) { // check ship ID...
        
        return false;
    }
    
    if(rowStart < 0 || colStart < 0 || rowEnd < 0 || colEnd < 0) { // negative coordinates
        
        return false;
    }
    
    // to check whether coordinates match with ID's...
    
    int row_diff = abs(rowEnd - rowStart);
    
    int col_diff = abs(colEnd - colStart);
    
    bool check_shape = false;
    
    // checking if ship shape matches ID...
    
    if(row_diff == 0 && col_diff == 1 && shipID == 1) { // small ship type 1
        
        check_shape = true;
    }
    
    else if(row_diff == 1 && col_diff == 0 && shipID == 1) { // small ship type 2
        
        check_shape = true;
    }
    
    else if(row_diff == 0 && col_diff == 2 && shipID == 2) { // big ship type 1
        
        check_shape = true;
    }
    
    else if(row_diff == 2 && col_diff == 0 && shipID == 2) { // big ship type 2
        
        check_shape = true;
    }
    
    else {
        
        return false; // wrong ship shape...
    }
    
    // ship shape checked...
    
    bool check_coord = false; // check coordinates
    
    if(check_shape) { // if ship shape is true...
        
        if(playerID == 1) {
            
            if(row_diff == 0 && col_diff == 1) { // small ship type 1
                
                if(!(rowStart > 5)) {
                    
                    if(colStart > 2 || colEnd > 2) {
                        
                        return false;
                    }
                    
                    else {
                        
                        check_coord = true;
                    }
                }
                
                else {
                    
                    return false; // exceeds row
                }
            }
            
            else if(row_diff == 1 && col_diff == 0) { // small ship type 2
                
                if(!(colStart > 2)) {
                    
                    if(rowStart > 5 || rowEnd > 5) {
                        
                        return false;
                    }
                    
                    else {
                        
                        check_coord = true;
                    }
                }
                
                else {
                    
                    return false; // exceeds columns
                }
            }
            
            else if(row_diff == 0 && col_diff == 2) { // big ship type 1
                
                if(!(rowStart > 5)) {
                    
                    if(colStart > 2 || colEnd > 2) {
                        
                        return false;
                    }
                    
                    else {
                        
                        check_coord = true;
                    }
                }
                
                else {
                    
                    return false; // exceeds rows
                }
            }
            
            else { // big ship type 2
                
                if(!(colStart > 2)) {
                    
                    if(rowStart > 5 || rowEnd > 5) {
                        
                        return false;
                    }
                    
                    else {
                        
                        check_coord = true;
                    }
                }
                
                else {
                    
                    return false; // exceeds columns
                }
            }
        }
        
        else { // player ID is 2...
            
            if(playerID == 2) {
                
                if(row_diff == 0 && col_diff == 1) { // small ship type 1
                    
                    if(!(rowStart > 5)) {
                        
                        if(colStart < 3 || colStart > 5) {
                            
                            return false;
                        }
                        
                        else {
                            
                            if(colEnd < 3 || colEnd > 5) {
                                
                                return false;
                            }
                            
                            else {
                                
                                check_coord = true;
                            }
                        }
                    }
                    
                    else {
                        
                        return false; // exceeds rows
                    }
                }
                
                else if(row_diff == 1 && col_diff == 0) { // small ship type 2
                    
                    if(!(colStart < 3 || colStart > 5)) {
                        
                        if(rowStart > 5 || rowEnd > 5) {
                            
                            return false;
                        }
                        
                        else {
                            
                            check_coord = true;
                        }
                    }
                    
                    else {
                        
                        return false; // exceeds cols
                    }
                }
                
                else if(row_diff == 0 && col_diff == 2) { // big ship type 1
                    
                    if(!(rowStart > 5)) {
                        
                        if(colStart < 3 || colStart > 5) {
                            
                            return false;
                        }
                        
                        else {
                            
                            if(colEnd < 3 || colEnd > 5) {
                                
                                return false;
                            }
                            
                            else {
                                
                                check_coord = true;
                            }
                        }
                    }
                    
                    else {
                        
                        return false; // exceeds rows
                    }
                }
                
                else { // big ship type 2
                    
                    if(!(colStart < 3 || colStart > 5)) {
                        
                        if(rowStart > 5 || rowEnd > 5) {
                            
                            return false;
                        }
                        
                        else {
                            
                            check_coord = true;
                        }
                    }
                    
                    else {
                        
                        return false; // exceeds cols
                    }
                }
            }
        }
    }
    
    // coordinates checked... ship shape checked....
    
    // now, check if previously occupied or not...
    
    if(check_coord) {
        
        // check previosuly occupied cell...
        
        if(row_diff == 0) {
            
            if(colEnd > colStart) {
                
                for(int i=colStart; i<=colEnd; i++) {
                    
                    if(theBoard[rowStart][i] == 1) {
                        
                        return false;
                    }
                }
            }
            
            else {
                
                for(int i=colEnd; i<=colStart; i++) {
                    
                    if(theBoard[rowStart][i] == 1) {
                        
                        return false;
                    }
                }
            }
        }
        
        else if(row_diff == 1) {
            
            if(rowEnd > rowStart) {
                
                for(int i=rowStart; i<=rowEnd; i++) {
                    
                    if(theBoard[i][colStart] == 1) {
                        
                        return false;
                    }
                }
            }
            
            else {
                
                for(int i=rowEnd; i<=rowStart; i++) {
                    
                    if(theBoard[i][colStart] == 1) {
                        
                        return false;
                    }
                }
            }
        }
        
        else if(row_diff == 2) {
            
            if(rowEnd > rowStart) {
                
                for(int i=rowStart; i<=rowEnd; i++) {
                    
                    if(theBoard[i][colStart] == 1) {
                        
                        return false;
                    }
                }
            }
            
            else {
                
                for(int i=rowEnd; i<=rowStart; i++) {
                    
                    if(theBoard[i][colStart] == 1) {
                        
                        return false;
                    }
                }
            }
        }
        
        // previously occupied cell checked...
        
        // unoccupied cell, place 1's for valid coordinates...
        
        if(row_diff == 0) {
            
            if(colStart > colEnd) {
                
                for(int i=colEnd; i<=colStart; i++) {
                    
                    theBoard[rowStart][i] = 1;
                }
            }
            
            else {
                
                for(int i=colStart; i<=colEnd; i++) {
                    
                    theBoard[rowStart][i] = 1;
                }
            }
        }
        
        else {
            
            if(rowStart > rowEnd) {
                
                for(int i=rowEnd; i<=rowStart; i++) {
                    
                    theBoard[i][colStart] = 1;
                }
            }
            
            else {
                
                for(int i=rowStart; i<=rowEnd; i++) {
                    
                    theBoard[i][colStart] = 1;
                }
            }
        }
    }
    
    return true;
}

bool myboard::makeAHit(int row, int column) {
    
    for(int i=0; i<6; i++) {
        
        for(int j=0; j<6; j++) {
            
            if(i == row && j == column) {
                
                if(theBoard[i][j] == 1) { // guess is valid
                    
                    theBoard[i][j] = -1; // successful hit
                    
                    return true;
                }
            }
        }
    }
    
    return false; // guess not containing a ship piece
}

bool myboard::checkIfPlayerWon(int playerID) {
    
    int count= 0;
    
    bool check = false;
    
    if(playerID == 1) {
        
        for(int i=0; i<6; i++) {
            
            for(int j=3; j<6; j++) {
                
                if(theBoard[i][j] == -1) {
                    
                    count++;
                }
            }
        }
    }
    
    else if(playerID == 2) {
        
        for(int i=0; i<6; i++) {
            
            for(int j=0; j<3; j++) {
                
                if(theBoard[i][j] == -1) {
                    
                    count++;
                }
            }
        }
    }
    
    if(count == 5) {
        
        check = true;
    }
    
    return check;
}

bool players::guess(int row, int column) {
    
    bool check = player_board.makeAHit(row, column);
    
    return check;
}

bool players::wins() {
    
    bool check = player_board.checkIfPlayerWon(playerID);
    
    return check;
}

