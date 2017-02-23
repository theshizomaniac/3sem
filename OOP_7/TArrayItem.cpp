//
// Created by mrhacker on 12/9/16.
//
#include "TArrayItem.h"
TAllocator TArrayItem::stackitem_allocator(sizeof(TArrayItem)*10, 20);

void * TArrayItem::operator new (size_t size) {
    void * res = stackitem_allocator.allocate();
    if (res == nullptr) {
        throw std::bad_alloc();
    }
    return stackitem_allocator.allocate();
}
void TArrayItem::operator delete(void *p) {
    stackitem_allocator.deallocate(p);
}
std::string TArrayItem::GetType(){
    return 0;
}