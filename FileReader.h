#ifndef HOMEWORK5GIT_FILEREADER_H
#define HOMEWORK5GIT_FILEREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include<iostream>
#include<cstdlib>



using namespace std;

class FileReader {
private:
    // file name -- init.dat
    char *fileName;
    // matrix size = number of element
    int size;
    // number of valve in each element -> each row
    int N;

    // hold the matrix .
    double ** matrixOfPop;

    // hold the first line of arguments in the input .
    int * arguments;
    //read the matrix from the input
    void readMatrix();


public:

    // constructor
    FileReader(char *fileName);

    virtual ~FileReader();

    void validationForSize() const;

    void argumentsForContainer();

    void printMatrixHelper() const;

    double **getMatrix() const;

    int *getArguments() const;
};


#endif //HOMEWORK5GIT_FILEREADER_H