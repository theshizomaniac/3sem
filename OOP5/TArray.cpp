//
// Created by mrhacker on 11/10/16.
//
#include "TArray.h"



template <class T> void TArray<T>::Resize(int newSize) {
    array = CPArray(array, newSize);
    size = newSize;
}
template <class T> bool TArray<T>::Insert(std::shared_ptr <T> tArrayItem, int index) {
    if (index > size) {
        std::cout << "Wrong index! Too big!" << std::endl;
        return false;
    }
    else {
        array[index] = tArrayItem;
        return 1;
    }
}


template <class T> bool TArray<T>::Empty() {
    return size == 0;
}


template <class T> std::shared_ptr <T> TArray<T>::Get (int index) {
    return array[index];
}

template <class T> std::ostream& operator<<(std::ostream& os,const TArray<T> & tarray) {
    for (int i = 0; i < tarray.size; i++) {
        tarray.Print(i);
    }
    return os;

}

template <class T> void TArray<T>::Delete(int index) {
    array[index] = nullptr;

}

template <class T> void TArray<T>::Delete() {
    for (int i = 0; i < size; ++i) {
        Delete(i);
    }
}

template <class T> void TArray<T>::printmenu() {
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
template <class T> void TArray<T>::Print(int index)const {
    std::cout << "Index = " << index << " |";
    if (array[index]) {
        array[index]->Print();
    }
    else {
        std::cout << "Empty!" << std::endl;
    }
}

template <class T>  std::shared_ptr <T> * TArray<T>::CPArray (std::shared_ptr <T> * oldArray, int newSize) {
    std::shared_ptr <T> * newArray = new std::shared_ptr <T> [newSize];
    for (int i = 0; i < size; ++i) {
        newArray[i] = oldArray[i];
    }
    return newArray;
}

