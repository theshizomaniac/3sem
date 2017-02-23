//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP5_TARRAYITEM_H
#define OOP5_TARRAYITEM_H
#include <cstdlib>
#include <iostream>
#include <memory>



class TArrayItem {
public:
    virtual double Square() = 0;
    virtual void Print() = 0;
    virtual ~TArrayItem() {};
    friend std::ostream& operator<<(std::ostream& os, TArrayItem& obj) {
        obj.Print();
        return  os;
    }

    friend bool operator==(const TArrayItem& left,const TArrayItem& right) {
        return left==right;
    }
};
#endif //OOP5_TARRAYITEM_H
