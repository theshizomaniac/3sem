//
// Created by mrhacker on 12/20/16.
//

#ifndef OOP6_TBINARYTREE_H
#define OOP6_TBINARYTREE_H


#include <memory>
#include <iostream>
#include "TNode.h"
#include "IRemoveCriteria.h"
#include <typeinfo>
#include <type_traits>
#include <cstdint>

template <class B> class TBinaryTree {
public:
    TBinaryTree (int size) {
        count = 0;
        maxSize = size;
        root = nullptr;
        std::cout << "Tree created!" <<std::endl;
    }

    void PrintAll () {
        Print(root, 1);
    }
    void Print(TNode <B> * node, int depth) {
        for (int i = 0; i < depth; ++i) {
            std::cout << "-.-";
        }
        if (node == nullptr) {
            std::cout << "/ Empty!" << std::endl;
            return;
        }
        if (node->data == nullptr) {
            std::cout << "/ Empty" << std::endl;
        } else {
            std::cout << "/ " << *(node->data);
        }
        ++depth;
        Print(node->left, depth);
        Print(node->right, depth);
    }
    bool Insert(std::shared_ptr <B> data) {
        std::cout << "COUNT = " << count << std::endl;
        if (count == 5) {
            return false;
        }
        if (this->root == nullptr) {
            root = new TNode <B> (data);
            ++count;
            return true;
        }
        bool left;

        TNode<B> * current = root;
        TNode<B> * y = new TNode <B> (data);
        TNode<B> * parent = root;

        if (root->data->Square() > y->data->Square()) {
            current = root->left;
            left = true;
        }
        else {
            current = root->right;
            left = false;
        }

        while (1) {
            if (current != nullptr) {
                parent = current;
                if (current->data->Square() > y->data->Square()) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            else {
                current = parent;
                y->parent = parent;
                if (data->Square() > parent->data->Square()) {
                    current->right = y;
                }
                else {
                    current->left = y;
                }
                break;
            }
        }

        Sort(y,left);
        ++count;
        return true;

    }
    void Sort(TNode <B> * inserted, bool left) {
        if (left) {
            if (inserted->data->Square() == inserted->parent->data->Square()) return;
            while(inserted->data->Square() > inserted->parent->data->Square()) {
                    inserted->data.swap(inserted->parent->data);
                    inserted = inserted->parent;
            }
        }
        else {
            if (inserted->data->Square() == inserted->parent->data->Square()) return;
            while(inserted->data->Square() < inserted->parent->data->Square()) {
                    inserted->data.swap(inserted->parent->data);
                    inserted = inserted->parent;
            }
        }
    }
    void DelSort(TNode <B> * node) {
        if (node == nullptr) return;
        if (node->data == nullptr) {
            if (node->left != nullptr) {
                if (node->left->data != nullptr) {
                    node->data.swap(node->left->data);
                }
            }
            else if (node->right != nullptr) {
                if (node->right->data != nullptr) {
                    node->data.swap(node->right->data);
                }
            }
            else {
                if (node->parent != nullptr) {
                    if (node == node->parent->right) {
                        TNode <B> * x = node->parent;
                        delete node;
                        x->right = nullptr;
                        return;
                    }
                    else {
                        TNode <B> * x = node->parent;
                        delete node;
                        x->left = nullptr;
                        return;
                    }
                }
            }
        }
        DelSort(node->left);
        DelSort(node->right);

    }

    template <class TT> void RemoveB(TNode <B> * node, size_t square) {
        if (node == nullptr) {
            return;
        }
        //TT * x = nullptr;
        RemoveB<TT>(node->right, square);
        RemoveB<TT>(node->left,square);
        //std::shared_ptr<B> value =node->data;
        //B * pd = new derived();
        bool deleting = false;
        if (!square) {
            TT * x = dynamic_cast<TT *>(&*(node->data));
            if (x != nullptr) {
                deleting = true;
            }
        }
        else if (node->data->Square() < square) {
                deleting = true;
        }
        if (deleting) {

            node->data = nullptr;
            --count;
        }
    }
    TNode <B> * GetSuccessor(TNode <B> * node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        TNode <B> * x = node;

        return x;
    }
    /*void RemoveBySquare(int square) {
        std::string a = "\0";
        RemoveByTypeRec(root, a, square, true);
    }*/
    void Destroy(TNode <B> * node) {
        if (node == nullptr) {
            return;
        }
        else {
            Destroy(node->left);
            Destroy(node->right);
        }
        delete node;
    }
    ~TBinaryTree() {
        if (count != 0) {
            Destroy(root);
            count = 0;
        }
        std::cout << "TREE DELETED!\n";
    }

    /*-------------------------------------*/

    TNode <B> * root;
    int count;
    int maxSize;
};




#endif //OOP6_TBINARYTREE_H
