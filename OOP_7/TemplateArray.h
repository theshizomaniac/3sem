

#ifndef OOP5_TEMPLATEARRAY_H
#define OOP5_TEMPLATEARRAY_H

#include <iostream>
#include <memory>
#include <cstring>
#include "TIterator.h"
#include "TAllocator.h"
#include "TBinaryTree.h"
template < template < class A > class T , class Sub> class TArray {
public:
    friend class TIterator < T <Sub> >;
    //TAllocator stackitem_allocator;
    //TAllocator stackitem_allocator(sizeof(TArrayItem),100);
    TArray() {
        array = new std::shared_ptr <T <Sub> > [10];
        size = 10;
       currentIndex = 0;
    }

    void Resize(int newSize) {
        array = CPArray(array, newSize);
        size = newSize;
    }

    bool Insert(std::shared_ptr <T <Sub> > tArrayItem, int index) {
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

    std::shared_ptr <T <Sub> > Get(int index) {
        return array[index];
    }

    friend std::ostream& operator<<(std::ostream& os,const TArray <T, Sub> & tarray) {
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

    void Push(std::shared_ptr<Sub> item) {
        if (this->Get(currentIndex) == nullptr) {
            std::shared_ptr < T <Sub> > newTree(new T <Sub> (5));
            this->Insert(newTree, currentIndex);
        }
        else if (this->Get(currentIndex)->count == 5) {
            ++currentIndex;
            if (currentIndex == size) {
                this->Resize(currentIndex);
            }
            std::shared_ptr < T <Sub> > newTree(new T <Sub> (5));
            this->Insert(newTree, currentIndex);
        }
        bool result = this->Get(currentIndex)->Insert(item);
    }

    void printmenu() {
        std::cout << "-------------------" << std::endl;
        std::cout << "1) Resize array." << std::endl;
        std::cout << "2) Insert figure." << std::endl;
        std::cout << "3) Print by index." << std::endl;
        std::cout << "4) Print all." << std::endl;
        std::cout << "5) Delete by index." << std::endl;
        std::cout << "6) Delete all." << std::endl;
        std::cout << "8) Exit" << std::endl;
    }

    void Print(int index) const {
        std::cout << "Index = " << index << " |";
        if (array[index]) {
            std::cout << "There is tree!\n";
            array[index]->PrintAll();
        }
        else {
            std::cout << "Empty!" << std::endl;
        }
    }

    std::shared_ptr <T <Sub> > * CPArray(std::shared_ptr < T <Sub> > * oldArray, int newSize) {
        std::shared_ptr <T <Sub>> *newArray = new std::shared_ptr<T <Sub>>[newSize];
        if (newSize > size) {
            memcpy(newArray, oldArray, size * sizeof(std::shared_ptr<T <Sub> >));
        }
        else {
            for (int i = 0; i < newSize; ++i) {
                newArray[i] = oldArray[i];
            }
        }
        return newArray;
    }
    TIterator<T <Sub> > begin()
    {
        return TIterator<T <Sub> >(0, array);

    }
    TIterator<T <Sub>> end()

    {
        return TIterator<T <Sub>>(size);
    }

    int size;

private:
    int currentIndex;
    std::shared_ptr <T <Sub> > * array;


};

#endif //OOP5_TEMPLATEARRAY_H
