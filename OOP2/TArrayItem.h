#ifndef TARRAYITEM_H
#define TARRAYITEM_H
#include "Rectangle.h"

class TStackItem {

public:

    TStackItem(const Triangle& triangle);
    TStackItem(const TStackItem& orig);

    friend std::ostream& operator<<(std::ostream& os, const TStackItem& obj);



    TStackItem* SetNext(TStackItem* next);

    TStackItem* GetNext();

    Triangle GetTriangle() const;

    virtual ~TStackItem();

private:

    Triangle triangle;

    TStackItem *next;

};

#endif /* TARRAYITEM_H */