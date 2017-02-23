//
// Created by mrhacker on 10/12/16.
//

#include <iostream>
#include "malloc.h"
#include "TArray.h"
#include "Rectangle2.h"

TArray::TArray() {
    array = (Rectangle *) std::malloc(10 * sizeof(Rectangle));
    size = 10;
    realSize = 0;
}
TArray::TArray(int startsize) {
    array = (Rectangle *) std::malloc(startsize * sizeof(Rectangle));
    size = startsize - 1;
    realSize = 0;

}
void TArray::Resize(int newSize) {
    array = (Rectangle*) realloc(array, newSize * sizeof(Rectangle));
    size = newSize;
}
bool TArray::Insert(Rectangle &&rectangle, int index) {
    if (index > size) {
        std::cout << "Wrong index! Too big!" << std::endl;
        return false;
    }
    else {
        array[index] = rectangle;
        realSize++;
        return 1;
    }
}

bool TArray::Insert (int index) {
    if (index < size) {
        std::cin >> array[index];
    }
    else {
        std::cout << "Wrong index! Try again: ";
        int n;
        std::cin >> n;
        Insert(n);
    }
}

bool TArray::Empty() {
    return size == 0;
}

TArray::~TArray() {
    free(array);
}

Rectangle TArray::Get (int index) {
    return Rectangle(array[index]);
}

std::ostream& operator<<(std::ostream& os,const TArray& tarray) {
    for (int i = 0; i < tarray.size; i++) {
        tarray.Print(i);
    }
    return os;

}

void TArray::Delete(int index) {
    array[index].Delete();
}

void TArray::Delete() {
    //array = NULL;
    free(array);
    array = NULL;
    size = 0;
    std::cout << "Deleted!" << std::endl;
}

void TArray::printmenu() {
    std::cout << "-------------------" << std::endl;
    std::cout << "1) Resize array." << std::endl;
    std::cout << "2) Insert rectangle." << std::endl;
    std::cout << "3) Print by index." << std::endl;
    std::cout << "4) Print all." << std::endl;
    std::cout << "5) Delete by index." << std::endl;
    std::cout << "6) Delete all." << std::endl;
    std::cout << "7) Compare." << std::endl;
    std::cout << "8) Copy" << std::endl;
    std::cout << "9) Exit." << std::endl;
}
void TArray::Print(int index)const {
    std::cout << "Index = " << index << " | " << array[index];
}