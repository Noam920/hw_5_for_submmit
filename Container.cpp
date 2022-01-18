#include "Container.h"

/*
Eran Helvitz
Noam Efrat
*/


Container::Container(double** matrix , int n_elems , int n_values , int n_after_func):
        n_of_elements(n_elems), n_values(n_values) , n_values_after_func(n_after_func)
{/* constructor set data members of containers initializing the elements
  * matrix  - elements values
  * n_elems  - number of elements
  * n_values - number of values in each element
  * n_after_func - number of values after func in each element
  */
    srand( (unsigned)time( NULL ) );
    randomVector = new double[n_values];
    for(int i = 0 ; i < n_of_elements ; i++) {
        Element *curr = new Element(n_values, matrix[i], n_after_func);
        elements.push_back(curr);
    }
}
Container::~Container(){
    // destructor
    delete[] randomVector;
    elements.clear();

}

void Container::simulates(int n_simulate)
{/* simulate - control func on the simulations
    param n_simulate -  number of simulation from the user
*/

    for(int i = 0 ; i < n_simulate ; i++)
    {
        resize_elements(); // crate more n_elems
        setElementFunc();
        genericSort< vector<Element* > , Element > G(elements);
        elements =  G.ParetoSorting(2*n_of_elements);
        elements.erase(elements.begin()+(n_of_elements) , elements.end() );
        clearRank();
    }
}

void Container:: setElementFunc(){
    for(unsigned int i = 0 ; i< elements.size() ; i++){
        elements[i]->func();
    }
}



void Container:: resize_elements()
{   int curr_elem ; // index for the exists elements
    double res[n_values]; // the new value of this new element
    for(int i =n_of_elements;i < 2*n_of_elements ; i++)// loop for n_elements times
    {
        get_random_vector(); // set randomVector
        for(int curr_index = 0;curr_index <n_values ; curr_index++){
            res[curr_index] = add_vectors(curr_elem, curr_index); // crate new value -  adding element[j] value with randomVector
        }
        curr_elem++;
        Element* e = new Element(n_values , res , n_values_after_func);// crate new element
        elements.push_back(e);// adding to the container
    }

}

double Container:: add_vectors(int curr_elem , int curr_index)
{/* add_vectors - return new value by add 2 values
    param curr_elem - elem[curr_elem].value[i]
    param curr_index - index for the randomVector
    */
    double res;
    res = randomVector[curr_index] + elements[curr_elem]->getvalue(curr_index); // un finish
    return res;
}

void Container::get_random_vector()
{/* get_random_vector - get random number [0,1]
  */

    for(int i = 0;i < n_values;i++){
        randomVector[i] = (double ) rand()/RAND_MAX;
    }
}

void Container::writeToFile(char* filename) const {
    /*writeToFile - print the data of each func result of element*/
    ofstream resultFile(filename,ios::out);
    if (!resultFile.is_open()) {
        string err="ERROR: ";
        throw std::invalid_argument( err+ filename + " does not exist or cannot be opened\n");
    }
    for (int i = 0; i < n_of_elements; ++i) {
        resultFile<<elements[i]->getfuncResult().c_str()<<endl;
//        cout << elements[i]->getfuncResult().c_str()<<endl;
    }
    resultFile.close();
}

Element* Container::operator[](int x) const {
    /*return pointer of the wanted element
     * */
    return this->elements[x];
}


void Container:: clearRank(){
    /* reset the elements ranks to 0
     */
    for(unsigned int i =0 ; i < elements.size() ; i++){
        elements[i]->setRank(0);
    }
}

Container::Container(const Container &other) {
// copy contractor for container
    this->operator=(other);

}
Container &Container::operator=(const Container &other) {
//implementation for operator =
    if(this==&other){
        return (*this);
    }
    elements.clear();

    n_of_elements = other.n_of_elements;
    n_values = other.n_values;

    n_values_after_func = other.n_values_after_func;
    // using operator =  of vector in stl .
    elements = other.elements;

    randomVector = other.randomVector;
    return *this;
}
