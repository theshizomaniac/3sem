#include <iostream>
//#include "TArray.h"
#include "TArrayItem.h"
//#include "TArray.cpp"
#include <memory>
#include "TemplateArray.h"

#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhomb.h"
int main() {

    TArray <TArrayItem> array;
    int exit;


    int c;
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
                std::cout << "1) Rectangle\n2) Trapeze\n3) Rhomb\n";
                int choice;
                std::cin >> choice;
                if (choice == 1) {
                    std::shared_ptr <TArrayItem> item (new Rectangle(std::cin));
                    array.Insert(item ,index);
                }
                else if (choice ==  2) {
                    std::shared_ptr <TArrayItem> item (new Trapeze(std::cin));
                    array.Insert(item ,index);
                }
                else if (choice == 3) {
                    std::shared_ptr <TArrayItem> item (new Rhomb(std::cin));
                    array.Insert(item ,index);
                }
                else {
                    std::cout << "Try again!" <<std::endl;
                }

                break;

            }
            case 7:
            {
                std::cout << "Enter index: ";
                int index;
                std::cin >> index;
                array.Print(index);
                break;
            }
            case 4:
            {
                std::cout << array;
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
                //array.Delete();
                array.quicksort();
                break;
            }
            case 3:
            {
                std::cout << "1) Rectangle\n2) Trapeze\n3) Rhomb\n";
                int choice;
                std::cin >> choice;
                if (choice == 1) {
                    std::shared_ptr <TArrayItem> item (new Rectangle(std::cin));
                    array.push(item);
                }
                else if (choice ==  2) {
                    std::shared_ptr <TArrayItem> item (new Trapeze(std::cin));
                    array.push(item);
                }
                else if (choice == 3) {
                    std::shared_ptr <TArrayItem> item (new Rhomb(std::cin));
                    array.push(item);
                }
                else {
                    std::cout << "Try again!" <<std::endl;
                }
                break;
            }
            case 8:
            {
                exit = 1;
                break;
            }
            case 9:
            {
                array.sort_parallel();
                //array.quicksort();
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