//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP6_TARRAYITEM_H
#define OOP6_TARRAYITEM_H
#include <cstdlib>
#include <iostream>
#include <memory>
#include "TAllocator.h"


class TArrayItem {
public:
    virtual double Square() = 0;
    virtual void Print() = 0;
    virtual ~TArrayItem() {};
    //void SetAllocator(TAllocator *);
    friend std::ostream& operator<<(std::ostream& os, TArrayItem& obj) {
        obj.Print();
        return  os;
    }
    //TAllocator stackitem_allocator(sizeof(TArrayItem),100);
    friend bool operator==(const TArrayItem& left,const TArrayItem& right) {
        return left==right;
    }
    static TAllocator stackitem_allocator;

    void * operator new (size_t size);
    void operator delete(void *p);
};



#endif //OOP6_TARRAYITEM_H
