#include <iostream>
using namespace std;

int main() {
    
    // note that only simple arithmetic is used to switch the values between the two numbers
    // no variable type checks are performed, assuming the two inputs are correctly taken from the console
    
    int first, sec;
    cout << "Enter the numbers respectively: ";
    cin >> first >> sec;
    
    cout << "First: " << first << "\n";
    cout << "Second: " << sec << "\n";
    
    if(first == sec) { // equal
        
        cout << "No switch needed, produces the same result." << endl;
        cout << "First: " << first << "\n";
        cout << "Second: " << sec << "\n";
        return 0;
    }
    
    else if(first < sec) { // first is smaller
        
        first = sec - first;
        sec -= first;
        first += sec;
    }
    
    else { // first is larger
        
        first = first - sec;
        sec += first;
        first = sec - first;
    }
    
    // output
    cout << "Values are now switched!" << endl;
    cout << "First: " << first << "\n";
    cout << "Second: " << sec << "\n";
    
    return 0;
}
