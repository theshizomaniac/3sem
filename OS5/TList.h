//
// Created by mrhacker on 1/4/17.
//

#ifndef OS5_TLIST_H
#define OS5_TLIST_H

typedef struct TList {
    struct TNode * head;
    int size;
} TList;

typedef struct TNode {
    struct TNode * next;
    struct TNode * prev;
    uint32_t data;
} TNode;

extern void Insert(TList * list, uint32_t data, int index);
extern void Remove(TList * list, int index);
extern TList * Init ();
extern void Print (TList * list);

extern void FreeList(TList * list);

#endif //OS5_TLIST_H
