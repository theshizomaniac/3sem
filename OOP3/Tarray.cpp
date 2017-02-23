//
// Created by mrhacker on 10/12/16.
//

#include <iostream>
#include "malloc.h"
#include "Tarray.h"
#include "TArrayItem.h"
#include "Rectangle.h"
#include <cstring>

TArray::TArray() {
    array = new std::shared_ptr <TArrayItem> [10];
    size = 10;

}
TArray::TArray(int startsize) {
    array = new std::shared_ptr <TArrayItem> [startsize];
    size = startsize;


}
void TArray::Resize(int newSize) {
    array = CPArray(array, newSize);
    size = newSize;
}
bool TArray::Insert(std::shared_ptr <TArrayItem> tArrayItem, int index) {
    if (index > size) {
        std::cout << "Wrong index! Too big!" << std::endl;
        return false;
    }
    else {
        array[index] = tArrayItem;
        return 1;
    }
}


bool TArray::Empty() {
    return size == 0;
}

TArray::~TArray() {
    delete [] array;
}

std::shared_ptr <TArrayItem> TArray::Get (int index) {
    return array[index];
}

std::ostream& operator<<(std::ostream& os,const TArray& tarray) {
    for (int i = 0; i < tarray.size; i++) {
        tarray.Print(i);
    }
    return os;

}

void TArray::Delete(int index) {
    array[index] = nullptr;

}

void TArray::Delete() {
    for (int i = 0; i < size; ++i) {
        Delete(i);
    }
}

void TArray::printmenu() {
    std::cout << "-------------------" << std::endl;
    std::cout << "1) Resize array." << std::endl;
    std::cout << "2) Insert figure." << std::endl;
    std::cout << "3) Print by index." << std::endl;
    std::cout << "4) Print all." << std::endl;
    std::cout << "5) Delete by index." << std::endl;
    std::cout << "6) Delete all." << std::endl;
    std::cout << "7) Square." << std::endl;
    std::cout << "8) Exit" << std::endl;
}
void TArray::Print(int index)const {
    std::cout << "Index = " << index << " |";
    if (array[index]) {
        array[index]->Print();
    }
    else {
        std::cout << "Empty!" << std::endl;
    }
}

std::shared_ptr <TArrayItem> * TArray::CPArray (std::shared_ptr <TArrayItem> * oldArray, int newSize) {
    std::shared_ptr <TArrayItem> * newArray = new std::shared_ptr <TArrayItem> [newSize];
    if (newSize > size) {
        memcpy(newArray, oldArray, size * sizeof(std::shared_ptr<TArrayItem>));
    }
    else {
        for (int i = 0; i < newSize; ++i) {
            newArray[i] = oldArray[i];
        }
    }
    return newArray;
}