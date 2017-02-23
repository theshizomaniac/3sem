//
// Created by mrhacker on 12/27/16.
//

#ifndef OOP7_IREMOVECRITERIA_H
#define OOP7_IREMOVECRITERIA_H

template <class T> class IRemoveCriteria {
public:
virtual bool isIt(T* value) = 0;
private:
};
#endif //OOP7_IREMOVECRITERIA_H
