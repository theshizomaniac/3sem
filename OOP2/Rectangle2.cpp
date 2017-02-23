//
// Created by mrhacker on 10/12/16.
//

#include "Rectangle2.h"
#include <iostream>

Rectangle::Rectangle() {
    Rectangle(0, 0);
}
Rectangle::Rectangle(int i, int j) {
    side_a = i;
    side_b = j;
    std::cout << "Rectangle created" << std::endl;
}

Rectangle& Rectangle::operator++() {
    side_a++;
    side_b++;
}

std::ostream& operator<<(std::ostream &os, const Rectangle &obj) {
    if (obj.side_a > 0) {
        os << "side_a = " << obj.side_a << ", side_b = " << obj.side_b << std::endl;
        return os;
    }
    else {
        os << "Empty!" << std::endl;
    }
}

std::istream& operator>>(std::istream& is, Rectangle& obj) {
    std::cout << "Enter side_a: ";
    is >> obj.side_a;
    std::cout << "Enter side_b: ";
    is >> obj.side_b;
}

Rectangle::Rectangle(const Rectangle& orig) {
    side_a = orig.side_a;
    side_b = orig.side_b;

}

int Rectangle::Square(){
    return  side_a * side_b;
}

Rectangle& Rectangle::operator=(const Rectangle& right) {

    if (this == &right) return *this;

    std::cout << "Rectangle copied" << std::endl;
    side_a = right.side_a;
    side_b = right.side_b;
    return *this;
}
bool operator==(const Rectangle& left, const Rectangle& right) {
    if (left.side_a == right.side_a && left.side_b == right.side_b) {
        return true;
    }
    else {
        return false;
    }
}
Rectangle::~Rectangle() {}

void Rectangle::Delete() {
    side_a = 0;
    side_b = 0;
}
