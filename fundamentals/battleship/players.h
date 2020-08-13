#include <iostream>
using namespace std;

class players {
    
public:
    players(myboard &board, int playerID); // default constructor
    bool guess(int row, int column);
    bool wins();

private:
    int playerID;
    myboard & player_board; // shared data member...
    
} ;
