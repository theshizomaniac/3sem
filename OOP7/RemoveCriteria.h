//
// Created by mrhacker on 12/27/16.
//
#include <TBinaryTree.h>
#include <iostream>
#ifndef OOP7_REMOVECRITERIA_H
#define OOP7_REMOVECRITERIA_H
template <class T> class Check {
    if( std::is_same<T,>::value ) {
        std::cout << "Else\n";
    }
};
template <> class Check <int> {

};


template <> bool Check (TNode <B> * node, int square) {
    std::cout << "int" << std::endl;
}
template <class T> bool Check (TNode <B> * node, int square) {
    if( std::is_same<T,B>::value ) {
        std::cout << "Else\n";
    }
}
#endif //OOP7_REMOVECRITERIA_H
