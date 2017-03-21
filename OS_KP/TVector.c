#include "TVector.h"

TElem* NewElem(double id, int amount) {
    TElem* elem = (TElem*)malloc(sizeof(TElem));
    elem->id = id;
    //elem->amount = amount;
    //elem->credit = 0;
    return elem;
}

TVector* Create() {
    TVector* vec = (TVector*)malloc(sizeof(TVector));
    vec->size = 0;
    vec->cap = MIN_CAP;
    vec->body = (TElem**)malloc(sizeof(TElem*) * vec->cap);
    for (int i = 0; i < vec->cap; i++)
        vec->body[i] = (TElem*)malloc(sizeof(TElem));
    return vec;
}

int Empty(TVector* vec) {
    return vec->size == 0;
}

int Size(TVector* vec) {
    return vec->size;
}

void Resize(TVector* vec, int vSize) {
    if (vSize == vec->cap) return;
    else if (!vSize) {
        Reset(vec);
        return;
    }
    else if (vSize > vec->cap)
        while (vSize > vec->cap)
            vec->cap = (int)(vec->cap*1.5 + 1);
    else {
        vec->cap = vSize;
        if (vec->size > vSize)
            vec->size = vSize;
    }
    TElem** result = (TElem**)malloc(sizeof(TElem*) * vec->cap);
    for (int i = 0; i < vec->size; i++)
        result[i] = vec->body[i];
    free(vec->body);
    vec->body = result;
}

TElem* FindId(TVector* vec, double id) {
    for (int i = 0; i < vec->size; i++)
        if(fabs(vec->body[i]->id - id) < EPS)
            return vec->body[i];
    return NULL;
}

void Push(TVector* vec, TElem* value) {
    if (vec->size + 1 > vec->cap)
        Resize(vec, vec->size + 1);
    vec->body[vec->size] = (TElem*)malloc(sizeof(TElem));
    vec->body[vec->size] = value;
    vec->size++;
}

void Insert(TVector* vec, TElem* value, int index){
    if (index < 0 || index > vec->size) return;
    if (vec->size + 1 > vec->cap)
        Resize(vec, vec->size + 1);
    vec->body[vec->size] = (TElem*)malloc(sizeof(TElem));
    for (int i = vec->size; i > index; i--)
        vec->body[i] = vec->body[i - 1];
    vec->body[index] = value;
    vec->size++;
}

TElem* Pop(TVector* vec) {
    vec->size--;
    TElem* buf = vec->body[vec->size];
    if (vec->size < vec->cap / 2)
        Resize(vec, vec->size);
    return buf;
}

TElem* Erase(TVector* vec, int index) {
    TElem* buf = vec->body[index];
    vec->size--;
    for (int i = index; i < vec->size; i++)
        vec->body[i] = vec->body[i + 1];
    if (vec->size < vec->cap / 2)
        Resize(vec, vec->size);
    return buf;
}

void RemoveElem(TVector* vec, double id) {
    for (int i = 0; i < vec->size; i++)
        if (fabs(vec->body[i]->id - id) < EPS) {
            Erase(vec, i);
            return;
        }
}

TVector* Reset(TVector* vec) {
    if (vec->cap) free(vec->body);
    vec = Create();
    return vec;
}
void Delete(TVector* vec) {
    for (int i = 0; i < vec->cap; i++)
        free(vec->body[i]);
    free(vec->body);
    free(vec);
}

int Save(TVector* vec, char* fileName) {
    FILE *out = fopen(fileName, "wb");
    if (!out) return -1;
    if (!vec) {
        int res = 0;
        fwrite(&res, sizeof(res), 1, out);
        return 0;
    }
    fwrite(&vec->size, sizeof(vec->size), 1, out);
    fwrite(&vec->cap, sizeof(vec->cap), 1, out);
    for (int i = 0; i < vec->size; i++) {
        //fwrite(&vec->body[i]->amount, sizeof(vec->body[i]->amount), 1, out);
        fwrite(&vec->body[i]->id, sizeof(vec->body[i]->id), 1, out);
    }
    fclose(out);
    return 0;
}

TVector* Load(char* fileName) {
    FILE *in = fopen(fileName, "rb");
    if (!in) return Create();
    int res;
    fread(&res, sizeof(res), 1, in);
    if (res == 0)
        return Create();
    TVector* vec = (TVector*)malloc(sizeof(TVector));
    vec->size = res;
    fread(&vec->cap, sizeof(vec->cap), 1, in);
    vec->body = (TElem**)malloc(sizeof(TElem*) * vec->cap);
    for (int i = 0; i < vec->cap; i++)
        vec->body[i] = (TElem*)malloc(sizeof(TElem));
    for (int i = 0; i < vec->size; i++) {
        //fread(&vec->body[i]->amount, sizeof(vec->body[i]->amount), 1, in);
        fread(&vec->body[i]->id, sizeof(vec->body[i]->id), 1, in);
    }
    fclose(in);
    return vec;
}
