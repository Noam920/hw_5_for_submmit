#include <iostream>
#include "FileReader.h"

#include "Element.h"
#include "Container.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "ERROR: Invalid input.";
        exit(1);
    }
    char *file = argv[1];
    FileReader fileReader(file);

    double **matrix = fileReader.getMatrix();
    int *arguments = fileReader.getArguments();
    Container container(matrix, arguments[0], arguments[1], arguments[2]);
    container.simulates(arguments[3]);
    container.writeToFile(argv[2]);

    return 0;

}