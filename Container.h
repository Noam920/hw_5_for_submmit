#ifndef HOMEWORK5GIT_CONTAINER_H
#define HOMEWORK5GIT_CONTAINER_H

/*
Eran Helvitz
Noam Efrat
*/


#include <vector>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "genericSort.h"
#include <stdexcept>
#include "Element.h"

using namespace std;

class Element;

class Container {
private:
    int n_of_elements; // mue
    int n_values; // n
    int n_values_after_func; //m
    vector<Element *> elements;
    double *randomVector;


public:
    Container();

    Container(const Container &other);

    ~Container();

    Container(double **matrix, int n_elems, int n_values, int n_after_func);

    Container &operator=(const Container &other);

    void simulates(int n_simulate);

    void resize_elements();

    void get_random_vector();

    double add_vectors(int curr_elem, int curr_index);

    void setElementFunc();

    void writeToFile(char *filename) const;

    Element *operator[](int x) const;

    void clearRank();
};


#endif //HOMEWORK5GIT_CONTAINER_H