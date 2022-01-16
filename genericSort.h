#ifndef HOMEWORK5GIT_GENERICSORT_H
#define HOMEWORK5GIT_GENERICSORT_H
#include <iostream>
#include <vector>
using namespace std;
template<class C , class E>

/*
 *------important!----------
 *This class makes comparisons between items
 * in order to use this class the items are required to be comparable,
 *  defined on the operator <
 */

class genericSort {
private:
    C container;
    E* curr;
    E* other;
    E* tmp;
public:


    genericSort(C v ):container(v),curr(NULL), other(NULL),tmp(NULL){
    // constructor for the class ;
   // init all data members ;
   //C v is the pointer for the elements in container.h class

    }
    void ParetoRanking( int index , int n_elements){
//check what the relationship is between two elements based on their rank
// param index of element in the container
//param total n_elements amount of element in the container

        curr = container[index];
        for (int i = 0; i <  n_elements; i++)
        {//loop on the elements
            if(index != i ){ //  check if its not the same elem
                other = container[i];
                // using operator < of element.h
                if(curr->operator<(other) ){
                     other->operator++(); // adding 1 for the rank
                }
            }
        }
    }

    void ElementsReordering(int n_elements){
        //This function rearranges the container according to its rank

        // using bubble sort algorithm
        int currIndex, otherIndex;
        for (currIndex = 0; currIndex < n_elements-1; currIndex++) {
            for (otherIndex = 0; otherIndex < n_elements - currIndex - 1; otherIndex++) {
                curr = container[otherIndex];
                other = container[otherIndex+1];
                //swap the elements
                if (curr->operator>(other)){
                    tmp = container[otherIndex+1];
                    container[otherIndex+1] = container[otherIndex];
                    container[otherIndex]=tmp;
                }}
        }
    }
    C ParetoSorting( int n_elements){
//Activates both functions

// \param n_elements in the container
// \return the arrange and sort container.
        for (int i = 0; i < n_elements ; i++) {
            ParetoRanking( i , n_elements);
        }
        ElementsReordering( n_elements);
        return container;
    }
    };



#endif //HOMEWORK5GIT_GENERICSORT_H