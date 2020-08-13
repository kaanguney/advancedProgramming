#include <iostream>
using namespace std;

class myboard {
    
public:
    myboard(); // default constructor...
    void displayBoard();
    bool putShip(int playerID, int shipID, int rowStart, int colStart, int rowEnd, int colEnd);
    bool makeAHit(int row, int column);
    bool checkIfPlayerWon(int playerID);
    
private:
    
    int theBoard [6][6]; // board to play the game
    
} ;
