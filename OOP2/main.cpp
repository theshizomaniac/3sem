#include <iostream>
#include "TArray.h"
#include "Rectangle2.h"


int main() {
    TArray array;

    int c, exit = 0;

    array.printmenu();
    while(1) {
        std::cout << "-------------------\nPress 0 to print menu!\nEnter key: ";
        std::cin >> c;
        std::cout << "-------------------\n";
        switch (c)
        {
            case 0:
            {
                array.printmenu();
                break;
            }
            case 1:
            {
                std::cout << "Enter new size: ";
                int newSize;
                std::cin >> newSize;
                array.Resize(newSize);
                break;
            }
            case 2:
            {
                std::cout << "Enter index: ";
                int index;
                std::cin >> index;
                if (index > array.size - 1) {
                    std::cout << "Wrong index! Too big!" << std::endl;
                    break;
                }/*
                array.Insert(index);
                break;*/
                Rectangle A;
                std::cin >> A;
                array.Insert(Rectangle(A),index);
                break;

            }
            case 3:
            {
                std::cout << "Enter index: ";
                int index;
                std::cin >> index;
                array.Print(index);
                break;
            }
            case 4:
            {
                std::cout<<array;
                break;
            }
            case 5:
            {
                std::cout << "Enter index: ";
                int index;
                std::cin >> index;
                array.Delete(index);
                break;
            }
            case 6:
            {
                array.Delete();
                break;
            }
            case 7:
            {
                std::cout << "Enter 1st index: ";
                int index1;
                std::cin >> index1;
                std::cout << "Enter 2nd index: ";
                int index2;
                std::cin >> index2;
                if (array.Get(index1) == array.Get(index2)) {
                    std::cout << "Rectangles are equal" << std::endl;
                }
                else {
                    std::cout << "Rectangles are not equal" << std::endl;
                }
                break;
            }
            case 8:
            {
                std::cout << "Enter 1st index (copy from): ";
                int index1;
                std::cin >> index1;
                std::cout << "Enter 2nd index (where to copy):";
                int index2;
                std::cin >> index2;
                array.Insert(array.Get(index1), index2);
                break;
            }
            case 9:
            {
                exit = 1;
                break;
            }
            default:
            {
                std::cout << "Try again!" << std::endl;
            }
        }
        if (exit == 1) {
            break;
        }
    }


    return 0;
}