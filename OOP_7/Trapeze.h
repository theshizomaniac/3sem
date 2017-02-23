//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP4_TRAPEZE_H
#define OOP4_TRAPEZE_H


#include "TArrayItem.h"
#include <cmath>

class Trapeze : public TArrayItem {
public:
    Trapeze();
    std::string GetType() {
        return "";
    }
    Trapeze(std::istream &is);
    Trapeze(int i, int j, int m, int n);
    void Print() override;
    ~Trapeze();
    double Square() override;
private:
    double side_a;
    double side_b;
    double side_c;
    double side_d;
};

#endif //OOP4_TRAPEZE_H
