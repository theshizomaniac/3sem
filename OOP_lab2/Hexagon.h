//
// Created by ayy on 11/8/16.
//

#ifndef HEXAGON_H
#define HEXAGON_H
#include <stdlib.h>
#include <iostream>

class Hexagon {
public:
    Hexagon();
    Hexagon(size_t i);
    Hexagon(const Hexagon &orig);

    Hexagon& operator++();
    double Square();
    friend Hexagon operator+(const Hexagon &left, const Hexagon &right);

    friend std::ostream&operator << (std::ostream os, const Hexagon& hexagon);
    friend std::istream&operator >> (std::istream is, Hexagon& hexagon);

    Hexagon&operator = (const Hexagon &right);
    virtual ~Hexagon();

private:
    size_t side;
};

#endif //OOP_LAB2_HEXAGON_H
