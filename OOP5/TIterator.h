//
// Created by mrhacker on 11/23/16.
//

#ifndef OOP5_TITERATOR_H
#define OOP5_TITERATOR_H

#include <memory>
#include <iostream>
#include "TemplateArray.h"
template <class T>
class TIterator

{
public:
    TIterator(int n,  std::shared_ptr<T> * array) : it(n) , iArray(array) {    }

    TIterator(int n) : it(n) { }

    std::shared_ptr<T> operator * () {
        return iArray[it];
    }



    TIterator operator ++ (){
        it++;
        return * this;
    }


    TIterator operator ++ (int){
        TIterator iter = (*this);
        ++(*this);
        return iter;
    }

    bool operator == (TIterator const& i){
        return it == i.it;
    }

    bool operator != (TIterator const& i){
        return !(*this == i);

    }

private:

    std::shared_ptr<T> * iArray;
    int it;
};


#endif //OOP5_TITERATOR_H
