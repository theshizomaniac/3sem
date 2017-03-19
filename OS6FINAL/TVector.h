#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MIN_CAP 8
#define EPS 0.000001

typedef struct TElem {
    double id;
    int amount;
    int credit;
} TElem;

typedef struct {
    TElem** body;
    int size;
    int cap;
} TVector;

TElem* NewElem(double id, int amount);
TVector* Create();
TVector* Reset(TVector* vec);
int Size(TVector* vec);
int Empty(TVector* vec);
TElem* Pop(TVector* vec);
TElem* Erase(TVector* vec, int index);
TElem* FindId(TVector* vec, double id);
void RemoveElem(TVector* vec, double id);
void Push(TVector* vec, TElem* value);
void Insert(TVector* vec, TElem* value, int index);
void Delete(TVector* vec);
int Save(TVector* vec, char* fileName);
TVector* Load(char* fileName);
