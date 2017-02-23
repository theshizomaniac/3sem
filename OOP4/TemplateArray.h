//
// Created by mrhacker on 11/11/16.
//

#ifndef OOP4_TEMPLATEARRAY_H
#define OOP4_TEMPLATEARRAY_H
//
// Created by mrhacker on 11/10/16.
//
#include <iostream>
#include <memory>
#include <cstring>

template < class T > class TArray {
public:

    TArray() {
        array = new std::shared_ptr <T> [10];
        size = 10;
    }

    void Resize(int newSize) {
        array = CPArray(array, newSize);
        size = newSize;
    }

    bool Insert(std::shared_ptr <T> tArrayItem, int index) {
        if (index > size) {
            std::cout << "Wrong index! Too big!" << std::endl;
            return false;
        } else {
            array[index] = tArrayItem;
            return 1;
        }
    }


    bool Empty() {
        return size == 0;
    }

    std::shared_ptr <T> Get(int index) {
        return array[index];
    }

    friend std::ostream& operator<<(std::ostream& os,const TArray <T> & tarray) {
        for (int i = 0; i < tarray.size; i++) {
            tarray.Print(i);
        }
        return os;

    }

    void Delete(int index) {
        array[index] = nullptr;

    }
    virtual ~TArray() {
        delete [] array;
    };

    void Delete() {
        for (int i = 0; i < size; ++i) {
            Delete(i);
        }
    }

    void printmenu() {
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

    void Print(int index) const {
        std::cout << "Index = " << index << " |";
        if (array[index]) {
            array[index]->Print();
        } else {
            std::cout << "Empty!" << std::endl;
        }
    }

    std::shared_ptr <T> *CPArray(std::shared_ptr <T> *oldArray, int newSize) {
        std::shared_ptr <T> *newArray = new std::shared_ptr<T>[newSize];
        /*for (int i = 0; i < size; ++i) {
            newArray[i] = oldArray[i];
        }*/
        //delete [] oldArray;
        if (newSize > size) {
            memcpy(newArray, oldArray, size * sizeof(std::shared_ptr<T>));
        }
        else {
            for (int i = 0; i < newSize; ++i) {
                newArray[i] = oldArray[i];
            }
        }
        return newArray;
    }
    int size;
private:

    std::shared_ptr <T> * array;
};
#endif //OOP4_TEMPLATEARRAY_H
