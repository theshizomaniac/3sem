//
// Created by mrhacker on 1/13/17.
//

#ifndef OS6_TVECTOR_H
#define OS6_TVECTOR_H

#include "stdlib.h"
#include "memory.h"

typedef struct {
    char * id;
    long cash;

} Client;

typedef struct {
    Client * data;
    size_t size;
} TVector;

TVector * Init ();
void Resize(TVector * vector);
void Push(TVector * vector, Client client);



#endif //OS6_TVECTOR_H
