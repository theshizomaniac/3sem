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
            while(inserted->data->Square() > inserted->parent->data->Square()) {
                    inserted->data.swap(inserted->parent->data);
                    inserted = inserted->parent;
            }
        }
        else {
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
                node->data.swap(node->left->data);
            }
        }
        DelSort(node->left);
        DelSort(node->right);

    }

    int RemoveByType (std::string & type) {
        RemoveByTypeRec(root, type, 0, false);
        return count;
    }
    bool CheckCriteria(TNode <B> * node, std::string &type, int square, bool bySquare) {
        if (bySquare) {
            return node->data->Square() < square;
        }
        else {
            return node->data->GetType() == type;
        }
    }

    /*---------------------------------------------*/
    template <class TT> void RemoveSubitem(IRemoveCriteria<TT> * criteria) {
        std::cout << "---------------------->" << std::endl;
        for (auto i : * this) {
            B copy;
            while (!i->empty()) {
                std::shared_ptr<TT> value = i->pop();
                if (criteria->isIt(&*value))
                    std::cout << "List: Delete element " << *value << std::endl;
                else {copy.push(new TT(*value));
                }
            }
            //while (!copy.empty()) i->push(new TT(*copy.pop()));
        }
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    }
    template <class TT> void Remove(TNode <B> * node, IRemoveCriteria<TT> * criteria) {
        std::cout << "---------------------->" << std::endl;
            B copy;
            if (node == nullptr) {
                return;
            }
        Remove(node->left, criteria);
        Remove(node->right, criteria);
                std::shared_ptr<TT> value = node->data;
                if (criteria->isIt(&*value)) {
                    std::cout << "Tree: Delete element " << *value << std::endl;

                }
            //while (!copy.empty()) i->push(new TT(*copy.pop()));
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
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
    /*---------------------------------------------------*/
   void RemoveByTypeRec(TNode <B> * node, std::string &type, int square, bool bySquare) {
        if (node == nullptr) {
            return;
        }
        RemoveByTypeRec(node->right, type, square, bySquare);
        RemoveByTypeRec(node->left, type, square, bySquare);
        if (CheckCriteria(node, type,square,bySquare)) {
            if (node->left != nullptr && node->right != nullptr) {
                if (node->parent->right == node) {
                    node->parent->right = GetSuccessor(node->right);
                    node->parent->right->left = node->left;
                    node->parent->right->right = node->right;
                    node->parent->right->parent = node->parent;
                    delete node;
                } else {
                    node->parent->left = GetSuccessor(node->right);
                    node->parent->left->left = node->left;
                    node->parent->left->right = node->right;
                    node->parent->left->parent = node->parent;
                    delete node;
                }
            }
            else if (node->left == nullptr && node->right == nullptr) {
                if (node == root) {
                    delete root;
                    root == nullptr;
                }
                else if (node->parent != nullptr) {
                    if (node == node->parent->right) {
                        node->parent->right = nullptr;
                        delete node;
                    } else {
                        node->parent->left = nullptr;
                        delete node;
                    }
                }
                else {
                    delete node;
                }
            }
            else if (node->left == nullptr || node->right == nullptr) {
                if (node->right == nullptr) {
                    if (node != root) {
                        if (node == node->parent->right) {
                            node->parent->right = node->left;
                            node->left->parent = node->parent;
                            delete node;
                        } else {
                            node->parent->left = node->left;
                            node->left->parent = node->parent;
                            delete node;
                        }
                    }
                    else {
                        root = node->left;// = nullptr;
                        delete node;
                    }
                }
                else {
                    if (node != root) {
                        if (node == node->parent->right) {
                            node->parent->right = node->right;
                            node->right->parent = node->parent;
                            delete node;
                        }
                        else {
                            node->parent->left = node->left;
                            node->left->parent = node->parent;
                            delete node;
                        }
                    }
                    else {
                        root = node->right;
                        delete node;
                    }
                }
            }
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
    void RemoveBySquare(int square) {
        std::string a = "\0";
        RemoveByTypeRec(root, a, square, true);
    }
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
