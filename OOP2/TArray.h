#ifndef TArray_H
#define TArray_H

#include "Rectangle2.h"

class TArray {

public:
    void printmenu();
    TArray();
    TArray(int size);
    void Resize(int newSize);
    bool Insert (Rectangle &&rectangle, int index);
    bool Insert (int index);
    bool Empty();
    void Print(int index)const;
    Rectangle Get(int index);    // zzz
    friend std::ostream& operator<<(std::ostream& os,const TArray& tarray);  //print
    virtual ~TArray();
    void Delete(int index);
    void Delete();
public:
    int size;
private:
    Rectangle * array;
    int realSize;
};

#endif /* Array_H */