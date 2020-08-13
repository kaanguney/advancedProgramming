#include <iostream>
using namespace std;

class Matrix {
    
    public:
        Matrix();
        ~Matrix(); // destructor
        Matrix(int rowNumber, int columnNumber, int init); // constructor
        Matrix(const Matrix &); // deep copy constructor
        int getRowNumber() const; // no parameter, const reference
        int getColumnNumber() const; // no parameter, const reference
        int getElementAt(int row, int column) const;
        void setElementAt(int row, int column, int elt) const;
        int ** mat_create() const;
        void print();
        void del_matrix();
        const Matrix & operator= (const Matrix & matrix);
        Matrix operator+ (const Matrix & matrix) const;
        Matrix operator- (const Matrix & matrix) const;
        bool operator== (const Matrix & matrix) const;
        Matrix operator! () const; // no parameter, value return...
        
    
    private:
        int rowNumber, columnNumber;
        int **elements;
};


