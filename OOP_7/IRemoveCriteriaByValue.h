//
// Created by mrhacker on 12/27/16.
//

#ifndef OOP7_IREMOVECRITERIABYVALUE_H
#define OOP7_IREMOVECRITERIABYVALUE_H

#include "IRemoveCriteria.h"
template <class T> class IRemoveCriteriaByValue : public IRemoveCriteria<T>{
public:
    IRemoveCriteriaByValue(T&& value) : _value(value) {};
    bool isIt(T* value) override{
        return _value==*value;
    }
private:
    T _value;
};

#endif //OOP7_IREMOVECRITERIABYVALUE_H
