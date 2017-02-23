//
// Created by mrhacker on 12/27/16.
//

#ifndef OOP7_IREMOVECRITERIAALL_H
#define OOP7_IREMOVECRITERIAALL_H
#include "IRemoveCriteria.h"
template <class T> class IRemoveCriteriaAll : public IRemoveCriteria<T>{
public:
    IRemoveCriteriaAll() {};
    bool isIt(T* value) override {
        return true;
    }
private:
};
#endif //OOP7_IREMOVECRITERIAALL_H
