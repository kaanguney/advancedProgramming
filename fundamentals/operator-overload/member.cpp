#include <iostream>
#include "matrix.h"

using namespace std;

Matrix::Matrix() { // default constructor
    
    rowNumber = 0;
    
    columnNumber = 0;
    
    elements = NULL;
}

int Matrix::getRowNumber() const {
    
    return rowNumber;
}

int Matrix::getColumnNumber() const {
    
    return columnNumber;
}

Matrix::~Matrix() {
    
    if(elements != NULL) { // destruct in that case...
        
        for(int i=0; i<rowNumber; i++) {
            
            delete [] elements[i];
        }
        
        delete [] elements;
    }
}

Matrix::Matrix(int Rownum, int ColumnNum, int init) { // user-defined constructor, for deep-copy...
    
    if(Rownum <= 0 || ColumnNum <= 0) { // then, use default constructor...
        
        rowNumber = 0;
        
        columnNumber = 0;
        
        elements = NULL;
    }
    
    else {
        
        rowNumber = Rownum;
        
        columnNumber = ColumnNum;
        
        elements = new int*[rowNumber];
        
        for(int i=0; i<rowNumber; i++) {
            
             elements[i] = new int[columnNumber];
        }
        
        for(int i=0; i<rowNumber; i++) {
            
            for(int j=0; j<columnNumber; j++) {
                
                elements[i][j] = init;
            }
        }
    }
}

int Matrix::getElementAt(int row, int column) const {
    
    int dummy = 0; // to prevent compiler errors...
    
    for(int k=0; k<rowNumber; k++) {
        
        for(int j=0; j<columnNumber; j++) {
            
            if(k == row && j == column) {
                
                return elements[k][j];
            }
        }
    }
    
    return dummy;
}

void Matrix::setElementAt(int row, int column, int elt) const {
    
    for(int k=0; k<rowNumber; k++) {
        
        for(int j=0; j<columnNumber; j++) {
            
            if(k == row && j == column) {
                
                this->elements[k][j] = elt;
            }
        }
    }
}

int ** Matrix::mat_create() const { // get the clone, use for deep-copy...
    
    int ** data = NULL;
    
    if(elements == NULL) {
        
        return data;
    }
    
    else {
        
        data = new int*[rowNumber];
        
        for(int i=0; i<rowNumber; i++) {
            
            data[i] = new int[columnNumber];
        }
        
        for(int i=0; i<rowNumber; i++) {
            
            for(int j=0; j<columnNumber; j++) {
                
                data[i][j] = elements[i][j];
            }
        }
    }
    
    return data;
}

Matrix::Matrix(const Matrix & matrix) { // deep-copy for matrix...
    
    elements = matrix.mat_create(); // returns pointer to pointer
    
    rowNumber = matrix.getRowNumber();
    
    columnNumber = matrix.getColumnNumber();
}

void Matrix::print() { // display the matrix
    
    for(int i=0; i<rowNumber; i++) {
        
        for(int j=0; j<columnNumber; j++) {
            
            cout << elements[i][j] << " ";
        }
        
        cout << "\n";
    }
}

void Matrix::del_matrix() { // useful during assignments...
    
    for(int i=0; i<rowNumber; i++) {
        
        delete [] elements[i];
    }
    
    delete [] elements;
}

const Matrix & Matrix::operator= (const Matrix & matrix) { // assignment...
    
    if(this != &matrix) { // if not already equal...
        
        del_matrix(); // delete previous data...
        
        rowNumber = matrix.getRowNumber(); // deal with the privates...
        
        columnNumber = matrix.getColumnNumber();
        
        elements = matrix.mat_create();
    }
    
    return *this;
}

Matrix Matrix::operator+ (const Matrix & matrix) const {
    
    Matrix res(*this); // this keyword is used to work specifically on that object...
    
    for(int i=0; i<rowNumber; i++) {
        
        for(int j=0; j<columnNumber; j++) {
            
            res.setElementAt(i, j, (matrix.getElementAt(i, j) + this->getElementAt(i, j)));
        }
    }
    
    return res;
}

Matrix Matrix::operator- (const Matrix & matrix) const {
    
    Matrix res(*this);
    
    for(int i=0; i<rowNumber; i++) {
        
        for(int j=0; j<columnNumber; j++) {
            
            res.setElementAt(i, j, (this->getElementAt(i, j) - matrix.getElementAt(i, j)));
        }
    }
    
    return res;
}

bool Matrix::operator== (const Matrix &matrix) const {
    
    if(!(this->columnNumber == matrix.columnNumber && this->rowNumber == matrix.rowNumber)) {
        
        return false;
        
    } // if dimensions not same...
    
    else { // dimensions same, now check if every elements is same...
        
        for(int i=0; i<rowNumber; i++) {
            
            for(int j=0; j<columnNumber; j++) {
                
                if(this->elements[i][j] != matrix.elements[i][j]) { // not all elements are the same in this case...
                    
                    return false;
                }
            }
        }
        
        return true;
    }
}

Matrix Matrix::operator!() const {
    
    Matrix res(columnNumber, rowNumber, 1); // initial value is 1, inverse of the matrix...
    
    // now, fill it in...
    
    for(int i=0; i<this->getRowNumber(); i++) {
        
        for(int j=0; j<this->getColumnNumber(); j++) {
            
            res.elements[j][i] = this->elements[i][j];
        }
    }
    
    return res;
}






