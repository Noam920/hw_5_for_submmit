#include "FileReader.h"

FileReader::FileReader(char *fileName) : fileName(fileName), size(0), N(0) {
    /* constructor set data members of FileReader
*/
    this->arguments = new int[4];
    argumentsForContainer();
    validationForSize();
    this->matrixOfPop=new double *[size];
    readMatrix();

}


FileReader::~FileReader() {
    //destructor for the class delete the elements that save dynamically
    for (int i = 0; i < size; ++i) {
        delete [] matrixOfPop[i];
    }
    delete [] arguments;


}


void FileReader::validationForSize() const {
    // check the size of the matrix for validation;
    ifstream file(fileName);
    if (!file.is_open()) {
        string err="ERROR: ";
        throw std::invalid_argument(err+ fileName +" does not exist or cannot be opened\n");
    }
    string line;
    int counter = 0;
    while (getline(file, line)) {
        counter++;
    }
    //number rows is in valid
    if ((counter - 1) != size) {
        string err = "ERROR: simulation definition in ";
        throw std::out_of_range( err + fileName + " is invalid\n");
    }
    file.close();
}


void FileReader::argumentsForContainer() {
    // Initializes the variables from the first row of the input file
    ifstream file(fileName);
    if (!file.is_open()) {
        string err="ERROR: ";
        throw std::invalid_argument( err+ fileName + " does not exist or cannot be opened\n");
    }
    int elem;
    int j = 0;

    string line;
    getline(file, line);
    istringstream innerLine(line);
    string element;
    stringstream ss;
    while (getline(innerLine, element, ' ')) {
        ss << element;
        ss >> elem;
        arguments[j] = elem;
        ss.clear();
        j++;
    }
    if (j != 4) {
        string err="ERROR: simulation definition in ";
        throw std::invalid_argument( err+ fileName + " is invalid\n");
    }
    size = arguments[0];
    N = arguments[1];
}

void FileReader::printMatrixHelper() const {
// helper function to print the reading matrix
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrixOfPop[i][j] << " ";
        }
        cout << endl;
    }
}


double **FileReader::getMatrix() const {
// \return the matrix

    return matrixOfPop;
}

void FileReader::readMatrix() {
    // read the matrix and check validation ;
    ifstream file(fileName);
    if (!file.is_open()) {
        string err="ERROR: ";
        throw std::invalid_argument( err+ fileName + " does not exist or cannot be opened\n");
    }
    double numberInMatrix;
    int j = 0;

    string line;
    getline(file, line);// first line to skip

    while (file.good()) {
        for (int i = 0; i < size; i++) {
            matrixOfPop[i] = new double[N];
            getline(file, line);
            istringstream innerLine(line);
            string element;
            stringstream ss;
            while (getline(innerLine, element, ' ')) {
                ss << element;
                ss >> numberInMatrix;
                matrixOfPop[i][j] = numberInMatrix;
                ss.clear();
                j++;
            }
            if (j != N) {
                stringstream ss;
                ss <<i;
                string str = ss.str();
                string err;
                err.append("ERROR: population definition in ").append(fileName).append(" at line ")
                        .append(str).append(" is invalid\n");
                throw std::out_of_range(err);
            }
            j = 0;
        }
        file.close();
    }
}

int *FileReader::getArguments() const {
    // return the array of arguments ;
    return arguments;
}