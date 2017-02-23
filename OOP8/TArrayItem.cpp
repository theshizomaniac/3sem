//
// Created by mrhacker on 12/9/16.
//
#include "TArrayItem.h"
TAllocator TArrayItem::stackitem_allocator(sizeof(TArrayItem), 20);
/*void TArrayItem::SetAllocator(TAllocator * allocator){
    std::cout <<"luk\n";
    stackitem_allocator = allocator;
    std::cout << "Allocator set!" << std::endl;
}*/
void * TArrayItem::operator new (size_t size) {
    return stackitem_allocator.allocate();
}
void TArrayItem::operator delete(void *p) {
    stackitem_allocator.deallocate(p);
}