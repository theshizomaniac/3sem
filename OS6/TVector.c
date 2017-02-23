//
// Created by mrhacker on 1/13/17.
//
#include "TVector.h"

TVector * Init()
{
    TVector * newVector = (TVector*) malloc(sizeof(Client));
    newVector->size = 0;
    return newVector;
}
void Resize(TVector * vector)
{
    vector = realloc(vector, (vector->size + 1) * sizeof(Client));
    vector->size++;
}
void Push (TVector * vector, Client client) {
    Resize(vector);
    vector->data[vector->size - 1] = client;
}