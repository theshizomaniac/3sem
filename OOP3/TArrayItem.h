//
// Created by mrhacker on 10/27/16.
//

#ifndef OOP3_FIGURE_H
#define OOP3_FIGURE_H

#include <cstdlib>
#include <iostream>
#include <memory>

class TArrayItem {
public:
    virtual double Square() = 0;
    virtual void Print() = 0;
    virtual ~TArrayItem() {    };
};

#endif //OOP3_FIGURE_H
