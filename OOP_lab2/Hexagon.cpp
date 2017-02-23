//
// Created by ayy on 11/8/16.
//
#include "Hexagon.h"
#include <iostream>
#include <math.h>

Hexagon::Hexagon() : Hexagon(0){}

Hexagon::Hexagon(size_t i) : side(i) {
    std::cout << "Hexagon created: side = " << side << std::endl;
}

Hexagon::Hexagon(const Hexagon& orig) {
    std::cout << "Hexagon copy created" << std::endl;
    side = orig.side;
}

double Hexagon::Square() {
    return 3.0 * sqrt(3.0) * side / 2.0;
}

Hexagon& Hexagon::operator=(const Hexagon &right) {
    if(this == &right) return *this;

    std::cout << "Hexagon copied" << std::endl;
    side = right.side;
    return *this;
}

Hexagon& Hexagon::operator++() {
    side++;
    return *this;
}

Hexagon operator+(const Hexagon &left, const Hexagon &right) {
    return Hexagon(left.side + right.side);
}

Hexagon::~Hexagon() {
    std::cout << "Triangle deleted" << std::endl;
}

std::ostream& operator << (std::ostream os, const Hexagon& hexagon) {
    os << "side = " << hexagon.side << std::endl;
    return os;
}

std::istream& operator >> (std::istream is, Hexagon& hexagon) {
    is >> hexagon.side;
    return is;
}