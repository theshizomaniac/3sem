//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP4_RHOMB_H
#define OOP4_RHOMB_H


#include "TArrayItem.h"

class Rhomb : public TArrayItem {
public:
    Rhomb();
    Rhomb(int x, int angle);
    //static TAllocator stackitem_allocator;
    Rhomb(std::istream &is);
    double Square() override;
    void Print() override;
    virtual ~Rhomb();
    //void * operator new (size_t size);
    //void operator delete(void *p);
private:
    double size_a;
    int angle_alpha, angle_beta;
};


#endif //OOP4_RHOMB_H
