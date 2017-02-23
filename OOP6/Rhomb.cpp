//
// Created by mrhacker on 11/10/16.
//

#include "Rhomb.h"
#include <cmath>

TAllocator Rhomb::stackitem_allocator(sizeof(Rhomb), 2);
Rhomb::Rhomb() {
    angle_alpha = angle_beta = 0;
    size_a = 0;
}

Rhomb::Rhomb(int x, int angle) {
    size_a = x;
    angle_alpha = angle;
    angle_beta = 180 - angle_alpha;
}

Rhomb::Rhomb(std::istream &is) {
    std::cout << "Rhomb: enter one lenght and one angle:" << std::endl;
    is >> size_a;
    is >> angle_alpha;
    angle_beta = 180 - angle_alpha;
    std::cout << "Rhomb created!" << std::endl;
}

double Rhomb::Square() {
    std::cout << "Rhomb square: ";
    return std::pow(size_a, 2) * std::sin(angle_alpha * 3.14159265 / 180);
}

void Rhomb::Print() {
    std::cout << "a = " << size_a << " angle1 = " << angle_alpha << " angle2 = " << angle_beta << std::endl;
}

Rhomb::~Rhomb() {
    std::cout << "Rhomb deleted!" << std::endl;
}
void * Rhomb::operator new (size_t size) {
    void * res = stackitem_allocator.allocate();
    if (res == nullptr) {
        std::cout << "Not enough space\n";
        throw std::bad_alloc();
    }
    return res;
}
void Rhomb::operator delete(void *p) {
    stackitem_allocator.deallocate(p);
}