//
// Created by mrhacker on 12/9/16.
//
#include "TArrayItem.h"
#include <stdio.h>
#include <exception>
TAllocator TArrayItem::stackitem_allocator(sizeof(TArrayItem), 2);

void * TArrayItem::operator new (size_t size) {
    std::cout << "new\n";
    void * res = stackitem_allocator.allocate();
    if (res == nullptr) {
        std::cout << "Not enough space\n";
        throw std::bad_alloc();
    }
    return res;
}
void TArrayItem::operator delete(void *p) {
    std::cout << "delete called\n";
    stackitem_allocator.deallocate(p);
}