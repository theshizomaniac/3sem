//
// Created by mrhacker on 1/4/17.
//
#include "event.h"
#include "stdio.h"
#include "malloc.h"
#include "TList.h"

void Insert(TList *list, uint32_t data, int index) {
    if (list->head == NULL) {
        list->head = (TNode*) malloc(sizeof(TNode));
        list->head->data = data;
        list->head->prev = NULL;
        list->head->next = NULL;
        printf("OK\n");
        list->size = 1;
    }
    else {
        if (-1 == index || index >= list->size) {
            TNode * newNode = (TNode*) malloc(sizeof(TNode));
            newNode->data = data;
            if (list->head->next == NULL) {
                list->head->next = newNode;
                list->head->prev = newNode;
                newNode->next = list->head;
                newNode->prev = list->head;
                printf("OK\n");
                list->size++;
                return;
            }
            TNode * tmp = list->head->prev;
            list->head->prev->next = newNode;
            newNode->prev = tmp;
            newNode->next = list->head;
            list->head->prev = newNode;
            printf("OK\n");
            ++list->size;
            return;
        }
        else {
            TNode * newNode = (TNode*) malloc(sizeof(TNode));
            newNode->data = data;
            TNode * tmp = list->head;
            for (int i = 0; i < index; ++i) {
                tmp = tmp->next;
            }
            newNode->next = tmp;
            newNode->prev = tmp->prev;
            tmp->prev->next = newNode;
            tmp->prev = newNode;
            printf("OK\n");
        }
    }
}

void Remove(TList *list, int index) {
    TNode * x = list->head->next;
    if (list->head == NULL) {
        return;
    }
    if (index == 0) {
        TNode * tmp = list->head;
        list->head = list->head->next;
        list->head->prev = tmp->prev;
        list->head->prev->next = list->head;
        free(tmp);
        printf("OK");
        --list->size;
        return;

    }
    int i = 1;
    for (int j = 1; j < index; ++j) {
        x = x->next;
        if (x == list->head) {
            return;
        }
    }
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x);
    --list->size;
    return;
}

TList * Init() {
    TList * newList = (TList*) malloc(sizeof(TList));
    if (newList == NULL) {
        printf("Error!\n");
        return NULL;
    }
    newList->size = 0;
    newList->head = NULL;
    printf("List created!\n");
    return newList;
}

void Print(TList *list) {
    if (list->size == 0) {
        printf("Empty!\n");
        return;
    }
    if (list->head->next == NULL) {
        printf("%d \n", list->head->data);
        return;
    }
    TNode * x = list->head->next;
    printf("%d", list->head->data);
    int i = 2;
    while(x != list->head) {
        printf(" <-> %d",x->data);
        ++i;
        x = x->next;
    }
    printf("\n");
    return;
}

void FreeList(TList *list) {
    TNode * x = list->head->prev;
    TNode * y = list->head->prev;

    while(x != list->head) {
        x = x->prev;
        free(y);
        y = x;
    }
    free(list->head);
}
