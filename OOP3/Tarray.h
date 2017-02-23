//
// Created by mrhacker on 10/27/16.
//

#ifndef OOP3_TARRAY_H
#define OOP3_TARRAY_H

#include "TArrayItem.h"
#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhomb.h"
#include <memory>


class TArray {

public:

    void printmenu();
    TArray();
    TArray(int size);
    void Resize(int newSize);
    bool Insert (std::shared_ptr <TArrayItem> tArrayItem, int index);
    bool Insert (int index);
    bool Empty();
    void Print(int index)const;
    std::shared_ptr  <TArrayItem> Get(int index);    // zzz
    friend std::ostream& operator<<(std::ostream& os,const TArray& tarray);  //print
    virtual ~TArray();
    void Delete(int index);
    void Delete();
    int size;

protected:
    std::shared_ptr <TArrayItem> * CPArray (std::shared_ptr <TArrayItem> * oldArray, int newSize);
private:
    std::shared_ptr <TArrayItem> * array;
};
#endif //OOP3_TARRAY_H
