//
// Created by mrhacker on 12/5/16.
//

#ifndef OOP5_TALLOCATOR_H
#define OOP5_TALLOCATOR_H

#include <cstdlib>
#include <iostream>


class TBlock {
public:
    TBlock(size_t size);
    char * block;
    bool free;
    ~TBlock();
    TBlock * parent;
    TBlock * left;
    TBlock * right;
};

class BTree {
public:
    BTree(size_t size);
    friend class TAllocator;
    TBlock * root;
    size_t nodes_count;
    TBlock * Make(size_t height, size_t size, TBlock * prev);
    void Destroy(TBlock * node);
};

class TAllocator {
public:
    TAllocator(size_t size,size_t count);
    void * allocate();
    void deallocate(void *pointer);
    void SearchForFree(TBlock * node);
    void SearchForPointer(TBlock *, void *);
    bool has_free_blocks();
    virtual ~TAllocator();
    TAllocator();
    friend class BTree;
private:
    size_t _size;
    size_t _count;
    BTree * tree;
    void * newFree;

    size_t _free_count;

};

#endif //OOP5_TALLOCATOR_H
