//
// Created by mrhacker on 11/10/16.
//


#include "Trapeze.h"

//TAllocator Trapeze::stackitem_allocator(sizeof(Trapeze), 2);
Trapeze::Trapeze() {
    Trapeze(0, 0, 0, 0);
}
Trapeze::Trapeze (int i, int j, int m, int n) {
    side_a = i;
    side_b = j;
    side_c = m;
    side_d = n;
    std::cout << "Trapeze created" << std::endl;
}
Trapeze::~Trapeze() {
    std::cout << "Trapeze deleted!"<< std::endl;
}
double Trapeze::Square() {
    double a = side_b - side_a;
    double c = std::pow(side_c, 2);
    double d = std::pow(side_d, 2);
    double b = (std::pow(a, 2) + c - d) / (2 * a);
    b = std::pow(b, 2);
    double s = std::sqrt(c - b);
    std::cout << "Trapeze square: ";
    return s * (side_a + side_b) / 2;

}
void Trapeze::Print() {
    std::cout << "a = " << side_a << " b = " << side_b << " c = " << side_c << " d = " << side_d << std::endl;
}

Trapeze::Trapeze(std::istream &is) {
    std::cout << "Trapeze: enter four lengths:" << std::endl;
    is >> side_a;
    is >> side_b;
    is >> side_c;
    is >> side_d;
    std::cout << "Trapeze created" << std::endl;
}
/*void * Trapeze::operator new (size_t size) {
    void * res = stackitem_allocator.allocate();
    if (res == nullptr) {
        std::cout << "Not enough space\n";
        throw std::bad_alloc();
    }
    return res;
}
void Trapeze::operator delete(void *p) {
    stackitem_allocator.deallocate(p);
}*/