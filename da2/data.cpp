//
// Created by mrhacker on 11/1/16.
//
#include "data.h"
#include <iostream>

bool operator>(const TData &left, const TData &right) {
    int i = 0;
    while(i != 255) {
        if (left.word[i] > right.word[i]) {
            return 1;
        }
        else if (left.word[i] < right.word[i]) {
            return 0;
        }
        i++;
    }
    return 0;
}

bool operator==(const TData right, const TData left) {
    return !(strcmp(left.word, right.word));
}

std::ostream& operator<<(std::ostream &os, const TData obj) {
    os << obj.word << " " << obj.key << " ";
}

void TData::ToLower() {
    int i = 0;
    while (word[i] != '\0') {
        word[i] = tolower(word[i]);
        i++;
    }
}