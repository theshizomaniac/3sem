#include <iostream>
#include "TArrayItem.h"
#include <memory>
#include <random>
#include <ctime>
#include "TemplateArray.h"
#include "TBinaryTree.h"
#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhomb.h"



int main() {

    TArray <TBinaryTree, TArrayItem> array;
    int exit;

    int c;
    int currentIndex = 0;
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
                std::cout << "1) Rectangle\n2) Trapeze\n3) Rhomb\n";
                int choice;
                std::cin >> choice;
                if (choice == 1) {
                    std::shared_ptr <TArrayItem> item (new Rectangle(std::cin));
                    array.Push(item);
                }
                else if (choice ==  2) {
                    std::shared_ptr <TArrayItem> item (new Trapeze(std::cin));
                    array.Push(item);
                }
                else if (choice == 3) {
                    std::shared_ptr <TArrayItem> item (new Rhomb(std::cin));
                    array.Push(item);
                }
                else {
                    std::cout << "Try again!" <<std::endl;
                }
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
                std::cout << array;
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
                std::cout << "1) BY TYPE\n2) BY SQUARE?\n";
                int choice;
                std::cin >> choice;
                switch(choice) {
                    case 1:
                    {
                        int type;
                        std::cout << "1)Rectangle\n2)Trapeze\n3)Rhomb\n";
                        std::cin >> type;
                        int index = 0;
                        switch(type) {
                            case 1: {
                                for (auto i : array) {
                                    if (i != nullptr) {
                                        i->RemoveB<Rectangle>(i->root, 0);;
                                        if (i->count == 0) {
                                            array.Delete(index);
                                        }
                                    }
                                    ++index;
                                }
                                break;
                            }
                            case 2: {
                                for (auto i : array) {
                                    if (i != nullptr) {
                                        i->RemoveB<Trapeze>(i->root, 0);;
                                        if (i->count == 0) {
                                            array.Delete(index);
                                        }
                                    }
                                    ++index;
                                }
                                break;
                            }
                            case 3: {
                                for (auto i : array) {
                                    if (i != nullptr) {
                                        i->RemoveB<Rhomb>(i->root, 0);;
                                        if (i->count == 0) {
                                            array.Delete(index);
                                        }
                                    }
                                    ++index;
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        std::cout << "ENTER SQUARE: ";
                        size_t square;
                        std::cin >> square;
                        int index = 0;
                        for (auto i : array) {
                            if (i != nullptr) {
                                i->RemoveB<TArrayItem>(i->root, square);
                                if (i->count == 0) {
                                    array.Delete(index);
                                }
                            }
                            ++index;
                        }
                        break;
                    }

                }
                for (auto i : array) {
                    if (i != nullptr)
                        for (int j = 0; j < 5; ++j) {
                            i->DelSort(i->root);
                        }
                }
                break;
            }
            case 7:
            {
                std::cout << "Test remove\n";

                break;
            }
            case 8:
            {
                exit = 1;
                break;
            }
            case 9:
            {
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