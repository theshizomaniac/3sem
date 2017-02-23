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
    std::string GetType() {
        return "";
    }
    Rhomb(std::istream &is);
    double Square() override;
    void Print() override;
    virtual ~Rhomb();

private:
    double size_a;
    int angle_alpha, angle_beta;
};


#endif //OOP4_RHOMB_H
