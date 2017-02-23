//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP3_RHOMB_H
#define OOP3_RHOMB_H

#include "TArrayItem.h"

class Rhomb : public TArrayItem {
public:
    Rhomb();
    Rhomb(int x, int angle);

    Rhomb(std::istream &is);
    double Square() override;
    void Print() override;
    virtual ~Rhomb();
private:
    double size_a;
    int angle_alpha, angle_beta;
};


#endif //OOP3_RHOMB_H
