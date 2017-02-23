//
// Created by mrhacker on 12/5/16.
//

#include "TAllocator.h"
#include <iostream>
TAllocator::TAllocator(size_t size,size_t count) {
    tree = new BTree(count);
    tree->root = tree->Make(count, size, tree->root);
    _count = tree->nodes_count;
    _free_count = _count;
    std::cout << "TAllocationBlock: Memory init, size = " << _count <<std::endl;
}
TAllocator::TAllocator() {}

void * TAllocator::allocate() {
    void * result = nullptr;
    if(_free_count > 0) {
        //_free_count--;

        newFree = nullptr;

        SearchForFree(tree->root);

        if (newFree != nullptr) {
            result = newFree;
            std::cout << "TAllocationBlock: Allocate " << (_count - _free_count) <<
                      " of " << _count << std::endl;
        }
    }
    else
    {
        std::cout << "TAllocationBlock: No memory exception :-)" <<
                  std::endl;
    }
    return result;
}

void TAllocator::SearchForFree (TBlock * node) {
    if (node == nullptr || newFree != nullptr) {
        return;
    }
    else if (node->free) {
        newFree = node->block;
        node->free = false;
        _free_count--;
        return;
    }
    else {
        SearchForFree(node->left);
        SearchForFree(node->right);
    }
}

void TAllocator::SearchForPointer (TBlock * node, void * pointer) {
    if (node == nullptr) return;
    if (node->block == pointer) {
        node->free = true;
    }
    else {
        SearchForPointer(node->left, pointer);
        SearchForPointer(node->right, pointer);
    }
}

void TAllocator::deallocate(void *pointer) {
    std::cout << "TAllocationBlock: Deallocate block "<< std::endl;
    _free_count++;
    SearchForPointer(tree->root, pointer);
}
bool TAllocator::has_free_blocks() {
    return _free_count>0;
}
TAllocator::~TAllocator() {
    tree->Destroy(tree->root);
    if(_free_count<_count) std::cout << "TAllocationBlock: Memory leak?" <<
                                     std::endl;
    else std::cout << "TAllocationBlock: Memory freed" <<
                   std::endl;
}

void BTree::Destroy(TBlock * node) {
    if (node == nullptr) {
        return;
    }
    else {
        Destroy(node->left);
        Destroy(node->right);
    }
    delete node;
}

TBlock::TBlock(size_t size)
{
    block = (char*) std::malloc(size);
    free = true;
    left = right = parent = nullptr;
}
TBlock::~TBlock() {
    std::free(block);
}
TBlock* BTree::Make(size_t height, size_t size, TBlock * prev) {
    if (0 == height) {
        return nullptr;
    }
    ++nodes_count;
    TBlock * newblock = new TBlock(size);
    newblock->parent = prev;
    std::cout << "NEW BLOCK!" << std::endl;
    newblock->left = Make(height-1, size, newblock);
    newblock->right = Make(height-1, size, newblock);
    return newblock;
}
BTree::BTree(size_t size) {
    root = new TBlock(size);
    nodes_count = 0;
}