#include "Element.h"
/*
Eran Helvitz
Noam Efrat
*/

Element::Element(int nVal, double *xVector1, int m) : n_val(nVal), m(m),
                                                     rank(0) {

    // deep copy-
    xVector=new double [nVal];
    for (int i = 0; i < nVal; ++i) {
        xVector[i]=xVector1[i];
    }
    // create f result
    funcResult=new double [m];
}
//destructor for the class
Element::~Element() {

    delete [] funcResult;
    delete [] xVector;
}

//\param index
// \return  xVector[i]
double Element::getvalue(int index){
    return xVector[index];
}

// this func calculate the result and save the data member funcResult
void Element::func() {
    for (int i = 0; i < m; i++) {
        double sum =0;
        for (int j = 0; j < n_val; j++) {
            sum+=pow((xVector[j]-(i+1)) , 2);
        }
        funcResult[i] =sum;
    }

}
bool Element::operator<(const Element*  other)const {
//
//\param other element
// \return - if this element is controlled  by other vector

    int equalCounter=0;
    int smallCounter=0;
    for (int i = 0; i < m; i++) {
        if(funcResult[i] <=other->funcResult[i]){ // x<=y
            smallCounter++;
        }
        if(funcResult[i]==other->funcResult[i]){ //x == y
            equalCounter++;
        }
    }
    if ((equalCounter <m) && (smallCounter == m) ){ //
        return true;
    }
    return false;
}

int Element::getRank() const {
    return rank;
}

void Element::setRank(int r) {
    rank = r;
}

string Element::getfuncResult() const {
    string  toReturn;
    for (int i = 0; i < m; ++i) {
        double temp=funcResult[i];
        stringstream ss;
        ss.clear();
        ss<<setprecision(6)<<fixed<<temp;
        toReturn+=ss.str();
        if (i<m-1)
            toReturn+=" ";


    }
    return toReturn;
}
int Element::operator[](int x) const {
//
// \param
// \return get the rank of element

    return rank;
}

void Element:: operator++()  {
//raise the rank of element in 1;
    rank+=1;
}

Element:: Element(const Element *p1){
    //coy constructor
    this->operator=(p1);
}


bool Element::operator>(const Element* other) const{
// \param other element
    //check what is the relations between two elements and return
    // false or true;

    return this->rank > other->rank;
}

Element &Element::operator=(const Element &other) {
    //implementation for operator =

    if(this==&other){
        return (*this);
    }
    //deep copy of each filed
   rank=other.rank;
    m=other.m;
   n_val=other.n_val;

    for (int i = 0; i < n_val; ++i) {
       xVector[i]= other.xVector[i];
    }
    this->funcResult = new double[m];
    for (int i = 0; i < m; ++i) {
        funcResult[i]=other.funcResult[i];
    }
    return *this;
}
