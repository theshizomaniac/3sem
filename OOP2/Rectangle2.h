//
// Created by mrhacker on 10/12/16.
//

#ifndef OOP2_RECTANGLE2_H
#define OOP2_RECTANGLE2_H
#include <cstdlib>
#include <iostream>

class Rectangle {

public:

    Rectangle ();
    Rectangle (int i,int j);

    Rectangle(const Rectangle& orig);
    Rectangle& operator++();

    int Square();
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& obj);
    friend std::istream& operator>>(std::istream& is, Rectangle& obj);
    friend bool operator==(const Rectangle& left,const Rectangle& right);
    Rectangle& operator=(const Rectangle& right);
    void Delete();
    virtual ~Rectangle();

private:

    int side_a;
    int side_b;
};

#endif //OOP2_RECTANGLE2_H
