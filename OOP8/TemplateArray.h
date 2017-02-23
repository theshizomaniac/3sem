

#ifndef OOP5_TEMPLATEARRAY_H
#define OOP5_TEMPLATEARRAY_H

#include <iostream>
#include <memory>
#include <cstring>
#include <climits>
#include "TIterator.h"
#include "TAllocator.h"
#include <future>
#include <mutex>

template < class T > class TArray {
public:
    friend class TIterator < T >;
    TArray() {
        array = new std::shared_ptr <T> [10];
        size = 10;
        currentIndex = -1;
        popIndex = 0;
    }
    TArray(size_t initSize) {
        array = new std::shared_ptr <T> [initSize];
        size = initSize;
        currentIndex = -1;
        popIndex = 0;
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
        std::cout << "3) Push." << std::endl;
        std::cout << "4) Print all." << std::endl;
        std::cout << "5) Delete by index." << std::endl;
        std::cout << "6) Delete all." << std::endl;
        std::cout << "7) Print by index." << std::endl;
        std::cout << "8) Exit" << std::endl;
        std::cout << "9) Sort" << std::endl;
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
        std::shared_ptr <T> * newArray = new std::shared_ptr<T>[newSize];
        if (newSize > size) {
            for (int i = 0; i < size; ++i) {
                newArray[i] = oldArray[i];
            }
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
    size_t check_size () {
        size_t check = 0;
        for (int i = 0; i < size; ++i) {
            if (array[i] != nullptr) {
                ++check;
            }
        }
        std::cout << "SIZE " << check << std::endl;
        return check;
    }
    size_t GetLastIndex () {
        return currentIndex;
    }
    void push(std::shared_ptr<T> item) {
        ++currentIndex;
        if (currentIndex == size) {
            Resize(currentIndex);
        }
        array[currentIndex] = item;
    }
    std::shared_ptr <T> pop_last() {
        std::shared_ptr <T> popped = array[currentIndex];
        if (popped == nullptr) {
            throw std::bad_alloc();
        }
        //Delete(currentIndex);
        array[currentIndex] = nullptr;
        --currentIndex;
        return popped;
    }
    std::shared_ptr <T> pop() {
        std::shared_ptr <T> popped = Get(popIndex);
        if (popped == nullptr) {
            throw std::bad_alloc();
        }
        Delete(popIndex);
        ++popIndex;
        return popped;
    }

    void check_markers() {
        size_t pop = 0, curr = 0;
        while(array[curr] != nullptr) {
            curr++;
        }
        curr--;
        popIndex = pop;
        currentIndex = curr;
    }
    void shift () {
        for (int j = 0; j < size; ++j) {
            if (array[j] == nullptr) {
                for (int i = 0; i < size - 1; ++i) {
                    if (array[i] == nullptr) {
                        array[i].swap(array[i + 1]);
                    }
                }
            }
        }
    }

    void sort() {
        if (check_size() > 1) {
            check_markers();
            std::shared_ptr<T> middle = pop_last();
            TArray<T> left(size/2 + 1), right(size/2 + 1);
            while (check_size()) {
                std::shared_ptr<T> item = pop_last();
                if (item->Square() < middle->Square()) {
                    left.push(item);
                } else {
                    right.push(item);
                }
            }
            left.sort();
            right.sort();
            if(!check_size())  {
                currentIndex = -1;
                popIndex = 0;
            }
            while (left.check_size()) {
                push(left.pop());
            }
            push(middle);
            while (right.check_size()) {
                push(right.pop());
            }
        }
    }
    std::future <void> sort_in_background(std::mutex * x) {
        x->lock();
        std::packaged_task < void(void) >
                task(std::bind(std::mem_fn(&TArray<T>::sort_parallel), this));
        std::future<void> res(task.get_future());
        std::thread th(std::move(task));
        th.detach();
        x->unlock();
        return res;
    }
    void sort_parallel() {
        if (check_size() > 1) {
            check_markers();
            std::shared_ptr<T> middle = pop_last();
            TArray<T> left(size/2 + 1), right(size/2 + 1);
            while (check_size()) {
                std::shared_ptr<T> item = pop_last();
                if (item->Square() < middle->Square()) {
                    left.push(item);
                } else {
                    right.push(item);
                }
            }
            std::mutex x;
            std::future<void> left_res = left.sort_in_background(&x);
            std::future<void> right_res = right.sort_in_background(&x);
            left_res.get();
            while (left.check_size()) push(left.pop());
            push(middle);
            right_res.get();
            while (right.check_size()) push(right.pop());
        }
    }
    void quicksort() {
        shift();
        std::cout << "zzz\n";
        check_markers();
        std::cout << "1) Common\n2) Parallel\n";
        int choice;
        std::cin >> choice;
        if (1 == choice) {
            sort();
        }
        else if (2 == choice) {
            sort_parallel();
        }
        else {
            std::cout << "Try again!" << std::endl;
        }
    }

    size_t size;

private:
    std::shared_ptr <T> * array;
    size_t currentIndex;
    size_t popIndex;

};

#endif //OOP5_TEMPLATEARRAY_H
