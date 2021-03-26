/*
. Create a sort for 2d matrices. Do a bubble sort, insertion sort, and selection sort
variation of this. Do NOT convert the matrix into a 1D array to sort. You must sort it as a
2D structure.
*/

#include <iostream>
#include <time.h>
#include<vector>
using namespace std;

template<typename mtxType>
class Matrix{
    protected:
        const int Rows, Cols;
    public:
    int mtxSize;
    mtxType** matrix;
        Matrix(mtxType rows, mtxType cols): Rows(rows), Cols(cols) { 
            mtxSize = rows*cols;
            matrix = new mtxType*[Rows];
            for (int i = 0; i < rows; i++)
            {
                matrix[i] = new mtxType[(int)cols]; //cast cols to an int
            }
            
        
        }//default constructor for a matrix
        void fillMatrix();
        void printMatrix();
        void insertionSortMtx();
        void bubbleSort();
        void selectionSort();
};

template<typename mtxType>
void Matrix<mtxType>::insertionSortMtx(){
    for (int i = 0; i < this->Rows; i++) //for each row
    {
        for (int j = 0; j < this->Cols-1; j++) //for each element in the row
        {
            int keyRow = i;// = this->matrix[i][j]; //set current matrix value as the key
            int keyCol = j;
            int tracker = j-1;
            mtxType key = this->matrix[keyRow][keyCol];
            int x = i ; //variable to loop through previous array elements
            int y = j-1; //variable to loop through previous array elements
            //Move the elements of the matrix that are greater than the key one index ahead
            while ( tracker >= 0 && matrix[i][j] > key){//while we are within the bounds of the matrix and the current value is greater than the key
                matrix[x][y+1] = matrix[i][j];
            }
            matrix[x+1][y] = key; //if the current element is less than the key, set it as the new key
            y = 0;
            //Iterate through previous elements (sorted elements)
            //Do not check first element, as it is the first element to be sorted  
            
        }

    }
cout << " Insertion Sort complete." << endl;
this->printMatrix();
}

template<typename mtxType>
void Matrix<mtxType>::bubbleSort(){
    for (int count = 0; count < mtxSize; count++) //until we have sorted each element
    {
        for (int i = 0; i < this->Rows; i++) //for each row
        {
            for (int j = 0; j < this->Cols-1; j++) //for each column in row i
            {
                if (this->matrix[i][j] > this->matrix[i][j+1]){ //compare the value in the current position to the value in the next position
                    //cout << "matrix[" << i << "][" << j << "]" << "> matrix[" << i << "][" << j+1 << "]" << ". Swapping " << this->matrix[i][j] << " and " << this->matrix[i][j+1] << endl;

                    swap(this->matrix[i][j], this->matrix[i][j+1]);//swap the values

                    //this->printMatrix();
                    //cout << "Swapped " << matrix[i][j] << " and " << matrix[i][j+1] << endl;
                    //this->printMatrix();
                }
            }  
        }//sort each row

        //after sorting, each row, 
        for (int i = 0; i < this->Rows-1; i++) //compare the last element of each row with the first element of the next row
        {
            if (this->matrix[i][this->Cols-1] > this->matrix[i+1][0]){ //if the element in the last column is greater than the first element in the next row 
                //cout << "Second swap: matrix[" << i << "][" << this->Cols-1 << "]" << " > matrix[" << i+1 << "][" << 0 << "]" << ". Swapping " << this->matrix[i][this->Cols-1] << " and " << this->matrix[i+1][0] << endl;
                swap( this->matrix[i][this->Cols-1], this->matrix[i+1][0]); //swap the element in last column in the of the current row with the first element of the next row
                //this->printMatrix();
            }
        }//loop comparing last element in a row to first element in next row
    }//loop until entire matrix is sorted
cout << "Bubble Sort complete." << endl;
this->printMatrix();
}

template<typename mtxType>
void Matrix<mtxType>::selectionSort(){
int temp = 0;
    for (int i = 0; i < this->Rows; i++) //for each row
    {
        for (int j = 0; j < this->Cols; j++) //for each column in row i
        {
            int currentMin = this->matrix[i][j]; //set first unsorted element as minimum value
            int minRow=i; int minCol = j ; //keep track of the indices of the minimum value

            int y = j; //
            //Iterate through unsorted elements
            for (int x = i; x < this->Rows; x++) //for the current row (i)
            {
                for (y; y < this->Cols; y++) //for each column in row i
                {   //set new minimum if saved minimum is higher
                    if ( currentMin > this->matrix[x][y]){ //compare current min and the next unsorted value
                        currentMin = this->matrix[x][y]; //set the new minimum
                        minRow = x; //set  indices of new minimum
                        minCol = y;
                    }
                }
                y=0; //after iterating through the first row, begin at the first column of the next row
            }
            swap(this->matrix[i][j], this->matrix[minRow][minCol]); //swap current element with minimum element found in the matrix
        }   
    }
cout << "Selection Sort complete." << endl;
this->printMatrix();
}

template<typename mtxType>
void Matrix<mtxType>::fillMatrix(){   
    for (int i = 0; i < Rows; i++) //iterate through the rows
    {
        for (int j = 0; j < Cols; j++) //for each row, iterate through the columns
        {
            mtxType random = rand()%1000/10.0;
            this->matrix[i][j] = random; //assign each matrix cell with a random value
        }  
    }
    cout << "Matrix Filled." << endl;
    this->printMatrix();
}

template<typename mtxType>
void Matrix<mtxType>::printMatrix(){
    cout << Rows << " x " << Cols << " Matrix: " << endl;
    for (int i = 0; i < Rows; i++) //iterate through the rows
    {
        for (int j = 0; j < Cols; j++) //for each for, iterate through the columns
        {
            cout << matrix[i][j] << "    ";  //print each element in row i
        }
        cout << endl; //print a new line after each row 
    }  
}






int main(){
    srand(time(NULL));
    int rows=3, columns=3;
    cout << "Enter # rows: ";
    //cin >> rows;
    cout << "Enter # columns: ";
    //cin >> columns;

    Matrix<int>* matrix1 = new Matrix<int>(rows,columns);
    matrix1->fillMatrix();
    matrix1->insertionSortMtx();


    Matrix<int>* matrix2 = new Matrix<int>(rows, columns);
    matrix2->fillMatrix();
    matrix2->bubbleSort();



    Matrix<int>* matrix3 = new Matrix<int>(rows, columns);
    matrix3->fillMatrix();
    matrix3->selectionSort();

    /*
    Example matrix:
        0   12 
        1   15
        Given the above matrix, 
        matrix[0][0] = 0
        matrix[0][1] = 12
        matrix[1][0] = 1
        matrix[1][1] = 15

    */

}
