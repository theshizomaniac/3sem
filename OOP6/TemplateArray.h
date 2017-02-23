

#ifndef OOP5_TEMPLATEARRAY_H
#define OOP5_TEMPLATEARRAY_H

#include <iostream>
#include <memory>
#include <cstring>
#include "TIterator.h"
#include "TAllocator.h"
template < class T > class TArray {
public:
    friend class TIterator < T >;
    //TAllocator stackitem_allocator;
    //TAllocator stackitem_allocator(sizeof(TArrayItem),100);
    TArray() {
        array = new std::shared_ptr <T> [10];
        size = 10;
       // std::cout << "ddddds\n";
      // stackitem_allocator = new TAllocator(sizeof(T),3);
       // std::cout <<"dafuck\n";
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
        std::cout << "9) Print using iterator" << std::endl;
    }

    void Print(int index) const {
        std::cout << "Index = " << index << " |";
        if (array[index]) {
            array[index]->Print();
        }
        else {
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
    TIterator<T> begin()
    {
        return TIterator<T>(0, array);

    }
    TIterator<T> end()

    {
        return TIterator<T>(size);
    }

   // TAllocator stackitem_allocator(sizeof(TArrayItem),100);
    int size;
    //TAllocator * stackitem_allocator;//(sizeof(T), 10);
private:
    std::shared_ptr <T> * array;


};
//template <class T> TAllocator TArray<T>::stackitem_allocator = TAllocator(sizeof(T),20);

//template < class T > TAllocator TArray<T>::stackitem_allocator(sizeof(T),100);
#endif //OOP5_TEMPLATEARRAY_H
