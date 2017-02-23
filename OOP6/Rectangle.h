//
// Created by mrhacker on 11/10/16.
//

#ifndef OOP4_RECTANGLE_H
#define OOP4_RECTANGLE_H


#include "TArrayItem.h"



class Rectangle : public TArrayItem{
public:

    static TAllocator stackitem_allocator;

    Rectangle ();
    Rectangle (int i,int j);

    Rectangle(const Rectangle& orig);
    //virtual Figure& operator++();
    ~Rectangle();
    double Square() override;
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& obj);
    friend std::istream& operator>>(std::istream& is, Rectangle& obj);
    friend bool operator==(const Rectangle& left,const Rectangle& right);
    Rectangle& operator=(const Rectangle& right);
    void Print() override;
    Rectangle(std::istream &is);
    void * operator new (size_t size);
    void operator delete(void *p);
protected:
    int side_a;
    int side_b;

};

#endif //OOP4_RECTANGLE_H
