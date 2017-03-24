#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MIN_CAP 8
#define EPS 0.000001

typedef struct TElem {
    double id;
    char name[20];
    char sex[1];
    char age[2];
    char country[20];
    char login[12];
    char pass[12];
    bool online;
} TElem;

typedef struct {
    TElem** body;
    int size;
    int cap;
} TVector;

TElem* NewElem(char id[], int amount);
TVector* Create();
TVector* Reset(TVector* vec);
int Size(TVector* vec);
int Empty(TVector* vec);
TElem* Pop(TVector* vec);
TElem* Erase(TVector* vec, int index);
TElem* FindId(TVector* vec, char id[]);
void RemoveElem(TVector* vec, double id);
void Push(TVector* vec, TElem* value);
void Insert(TVector* vec, TElem* value, int index);
void Delete(TVector* vec);
int Save(TVector* vec, char* fileName);
TVector* Load(char* fileName);
