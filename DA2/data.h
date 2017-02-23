//
// Created by mrhacker on 10/23/16.
//

#ifndef DA2_DATA_H
#define DA2_DATA_H

#include <iostream>
#include <cstring>

class TData {
public:
    friend bool operator>(const TData &right, const TData &left);
    friend bool operator==(const TData &right, const TData &left);
    //friend std::ostream& operator<<(std::ostream &os, const TData obj);
    void ToLower ();
    unsigned long long key;
    char word[257];
};
#endif //DA2_DATA_H
