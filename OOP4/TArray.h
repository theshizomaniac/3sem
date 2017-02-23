//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP4_ARRAY_H
#define OOP4_ARRAY_H

#include <memory>
#include <iostream>


#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhomb.h"

template <class T>
class TArray;

template<class T>
std::ostream& operator<< ( std::ostream& os, const TArray <T> & L);

template < class T > class TArray {
public:
    void printmenu();
    TArray() {
        array = new std::shared_ptr <T> [10];
        size = 10;
    }
    TArray(int size);
    void Resize(int newSize);
    bool Insert (std::shared_ptr <T> tArrayItem, int index);
    bool Insert (int index);
    bool Empty();
    void Print(int index)const;
    std::shared_ptr  <T> Get(int index);    // zzz
    friend std::ostream& operator<< <>(std::ostream& os,const TArray & tarray);  //print
    virtual ~TArray() {};
    void Delete(int index);
    void Delete();


    int size;
private:
    std::shared_ptr <T> * CPArray (std::shared_ptr <T> * oldArray, int newSize);
    std::shared_ptr <T> * array;
};

#endif //OOP4_ARRAY_H
