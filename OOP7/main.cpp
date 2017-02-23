#include <iostream>
//#include "TArray.h"
#include "TArrayItem.h"
//#include "TArray.cpp"
#include <memory>
#include <random>
#include <ctime>
#include "TemplateArray.h"
#include "TBinaryTree.h"
#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhomb.h"


void Random(TArray <TBinaryTree, TArrayItem> &array, int n) {
    for (int i = 0; i < n; ++i) {
        std::random_device d;
        // Choose a random mean between 1 and 6
        std::default_random_engine z1(d());
        std::uniform_int_distribution<int> uniform_dist(1, 3);
        int random = 1;//uniform_dist(z1);
        if (random == 1) {
            int a = 1 +std::rand()%100, b = 1 +std::rand()%100;
            std::cout << "a = " << a << "b = " << b;
            std::shared_ptr <TArrayItem> item (new Rectangle(a,b));
            std::cout << "RECT " << item->Square();
            array.Push(item);
        }
        if (random == 2) {
            std::random_device r;
            // Choose a random mean between 1 and 6
            std::default_random_engine e1(r());
            std::uniform_int_distribution<int> uniform_dist(1, 100);
            int a = uniform_dist(e1), b = uniform_dist(e1), c = uniform_dist(e1), d = uniform_dist(e1);
            std::cout << "a = " << a << "b = " << b << "c = " << c << "d = " << d;
            std::shared_ptr <TArrayItem> item (new Trapeze(a,b,c,d));
            std::cout << "TRAP " << item->Square();
            array.Push(item);
        }
        if (random == 3) {
            int a = 1 +std::rand()%100, b =  1+std::rand()%89;
            std::shared_ptr <TArrayItem> item (new Rhomb(a,b));
            std::cout << "Rhomb " << item->Square();
            array.Push(item);
        }
    }

}


int main() {

    //TArray <TArrayItem> array;
    TArray <TBinaryTree, TArrayItem> array;
    int exit;
    /*TBinaryTree <TArrayItem> treetest (5);
    std::shared_ptr <TArrayItem> item (new Rectangle(std::cin));
    std::shared_ptr <TArrayItem> item2 (new Rectangle(std::cin));
    std::shared_ptr <TArrayItem> item3 (new Rectangle(std::cin));
    treetest.Insert(item);
    treetest.Insert(item2);
    treetest.Insert(item3);
    treetest.PrintAll();*/

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
                    //result = array.Get(currentIndex)->Insert(item);
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
                /*std::cout << "Enter index: ";
                int index;
                std::cin >> index;
               // array.Delete(index);
//                array.Get(index)->Remove();
                std::cout << "1) BY TYPE\n2) BY SQUARE?\n";
                int choice;
                std::cin >> choice;
                switch(choice) {
                    case 1:
                    {
                        std::string type;
                        std::cout << "ENTER TYPE: ";
                        std::cin >> type;
                        if (array.Get(index) != nullptr) {
                            int x = array.Get(index)->RemoveByType(type);
                            if (array.Get(index)->count == 0) {
                                array.Delete(index);
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        std::cout << "ENTER SQUARE: ";
                        int square;
                        std::cin >> square;
                        if (array.Get(index) != nullptr) {
                            array.Get(index)->RemoveBySquare(square);
                            if (array.Get(index)->count == 0) {
                                array.Delete(index);
                            }
                        }
                        break;
                    }
                }*/
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
                    i->DelSort(i->root);
                }
                break;
            }
            case 7:
            {
                std::cout << "Test remove\n";
               // array.Get(0)->RemoveB<Rectangle>(array.Get(0)->root, 0);
                break;
            }
            case 8:
            {
                exit = 1;
                break;
            }
            case 9:
            {
                Random(array,20);
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