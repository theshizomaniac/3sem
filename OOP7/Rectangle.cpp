//
// Created by mrhacker on 11/10/16.
//
#include "Rectangle.h"

//TAllocator Rectangle::stackitem_allocator(sizeof(Rectangle), 2);
Rectangle::Rectangle() {
    Rectangle(0, 0);
}
Rectangle::Rectangle(int i, int j) {
    side_a = i;
    side_b = j;
    std::cout << "Rectangle created" << std::endl;
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

double Rectangle::Square(){
    std::cout << "Rectangle square: ";
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
Rectangle::~Rectangle() {
    std::cout <<"Rectangle deleted\n";
}

void Rectangle::Print() {
    std::cout << "side_a = " << side_a << ", side_b = " << side_b << std::endl;
    return;
}
Rectangle::Rectangle(std::istream &is) {
    std::cout << "Rectangle: enter two lengths:" << std::endl;
    is >> side_a;
    is >> side_b;
    std::cout << "Rectangle created" << std::endl;
}
/*void * Rectangle::operator new (size_t size) {
    void * res = stackitem_allocator.allocate();
    if (res == nullptr) {
        std::cout << "Not enough space\n";
        throw std::bad_alloc();
    }
    return res;
}
void Rectangle::operator delete(void *p) {
    stackitem_allocator.deallocate(p);
}*/
