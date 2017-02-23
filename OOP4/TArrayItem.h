//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP4_TARRAYITEM_H
#define OOP4_TARRAYITEM_H
#include <cstdlib>
#include <iostream>
#include <memory>



class TArrayItem {
public:
    virtual double Square() = 0;
    virtual void Print() = 0;
    virtual ~TArrayItem() {};
};
#endif //OOP4_TARRAYITEM_H
