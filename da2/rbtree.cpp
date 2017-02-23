//
// Created by mrhacker on 10/23/16.
//

#include "rbtree.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "data.h"

TRedBlackTree::TRedBlackTree()
{
    nil = new TNode;
    nil->left = nil->right = nil->parent = nil;
    nil->red = 0;
    nil->key.word[0] = 0;
    nil->key.key = 0;

    root = new TNode;
    root->parent = root->left = root->right = nil;
    root->key.key = 30000;
    root->key.word[0] = 0;
    root->red = 0;
}

TNode::TNode(TData data) {
    key = data;

}

TNode::TNode(std::istream& file) {
    file >> key.word >> key.key >> red;
    std::cout << key.word << " " << key.key << " " << red << std::endl;
}

TNode * TRedBlackTree::Insert(TData key)
{
    TNode * y;
    TNode * x;
    TNode * newNode;
    bool success;

    x = new TNode(key);
    success = BinInsert(x);
    if (!success) {
        delete x;
        return nullptr;
    }

    newNode = x;
    x->red=1;
    while(x->parent->red) {
        if (x->parent == x->parent->parent->left) {
            y=x->parent->parent->right;
            if (y->red) {
                x->parent->red=0;
                y->red=0;
                x->parent->parent->red=1;
                x=x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x=x->parent;
                    LeftRotate(x);
                }
                x->parent->red=0;
                x->parent->parent->red=1;
                RightRotate(x->parent->parent);
            }
        } else {
            y=x->parent->parent->left;
            if (y->red) {
                x->parent->red=0;
                y->red=0;
                x->parent->parent->red=1;
                x=x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x=x->parent;
                    RightRotate(x);
                }
                x->parent->red=0;
                x->parent->parent->red=1;
                LeftRotate(x->parent->parent);
            }
        }
    }
    root->left->red=0;
    return(newNode);
}


void TRedBlackTree::LeftRotate(TNode* x) {
    TNode* y;

    y=x->right;
    x->right=y->left;

    if (y->left != nil) y->left->parent=x;
    y->parent=x->parent;

    if( x == x->parent->left) {
        x->parent->left=y;
    } else {
        x->parent->right=y;
    }
    y->left=x;
    x->parent=y;

}

void TRedBlackTree::RightRotate(TNode* y) {
    TNode* x;

    x=y->left;
    y->left=x->right;

    if (nil != x->right)  x->right->parent=y;

    x->parent=y->parent;
    if( y == y->parent->left) {
        y->parent->left=x;
    } else {
        y->parent->right=x;
    }
    x->right=y;
    y->parent=x;
}

bool TRedBlackTree::BinInsert(TNode * z) {

    TNode * x;
    TNode * y;

    z->left=z->right=nil;
    y=root;
    x=root->left;
    while(x != nil) {
        y = x;
        if (x->key > z->key) {
            x = x->left;
        }
        else if (x->key == z->key) {
            std::cout << "Exists!" << std::endl;
            return false;
        }
        else { /* x->key <= z->key */
            x = x->right;
        }
    }
    z->parent = y;
    if ( (y == root) || (y->key > z->key) ) {
        y->left=z;
    }
    else {
        y->right=z;
    }
    return true;
}

TNode::TNode() {}

TNode::~TNode() {}

TRedBlackTree::~TRedBlackTree() {
    if (root->left->key.word[0] == 0) {
        Destruction(root->left);
    }

    delete root;
    delete nil;
}

void TRedBlackTree::Destruction(TNode * node) {
    if (node != nil) {
        Destruction(node->right);
        Destruction(node->left);
        delete node;
    }
    else return;
}

void TRedBlackTree::DeleteFixUp(TNode* x) {
    TNode * w;
    TNode * rootLeft = root->left;

    while( (!x->red) && (rootLeft != x)) {
        if (x == x->parent->left) {
            w=x->parent->right;
            if (w->red) {
                w->red=0;
                x->parent->red=1;
                LeftRotate(x->parent);
                w=x->parent->right;
            }
            if ( (!w->right->red) && (!w->left->red) ) {
                w->red=1;
                x=x->parent;
            } else {
                if (!w->right->red) {
                    w->left->red=0;
                    w->red=1;
                    RightRotate(w);
                    w=x->parent->right;
                }
                w->red=x->parent->red;
                x->parent->red=0;
                w->right->red=0;
                LeftRotate(x->parent);
                x=rootLeft;
            }
        } else {
            w=x->parent->left;
            if (w->red) {
                w->red=0;
                x->parent->red=1;
                RightRotate(x->parent);
                w=x->parent->left;
            }
            if ( (!w->right->red) && (!w->left->red) ) {
                w->red=1;
                x=x->parent;
            } else {
                if (!w->left->red) {
                    w->right->red=0;
                    w->red=1;
                    LeftRotate(w);
                    w=x->parent->left;
                }
                w->red=x->parent->red;
                x->parent->red=0;
                w->left->red=0;
                RightRotate(x->parent);
                x=rootLeft; /* this is to exit while loop */
            }
        }
    }
    x->red=0;
}

TNode * TRedBlackTree::GetSuccessorOf(TNode * x) const
{
    TNode* y;

    if (nil != (y = x->right)) {
        while(y->left != nil) {
            y=y->left;
        }
        return(y);
    } else {
        y=x->parent;
        while(x == y->right) {
            x=y;
            y=y->parent;
        }
        if (y == root) return(nil);
        return(y);
    }
}

TNode * TRedBlackTree::GetPredecessorOf(TNode * x) const {
    TNode* y;

    if (nil != (y = x->left)) {
        while(y->right != nil) {
            y=y->right;
        }
        return(y);
    } else {
        y=x->parent;
        while(x == y->left) {
            if (y == root) return(nil);
            x=y;
            y=y->parent;
        }
        return(y);
    }
}

void TRedBlackTree::PrintTree() {
    Print(root->left);
}

void TRedBlackTree::Print(TNode * node) const {
    if (node == nil) {
        return;
    }
    std::cout << "key = " << node->key <<" red = " << node->red;
    std::cout << "|| left son = " << node->left->key << " right son = " << node->right->key << std::endl;
    Print(node->left);
    Print(node->right);
}

TData TRedBlackTree::DeleteNode(TNode * z){
    TNode* y;
    TNode* x;
    TData returnValue = z->key;

    y= ((z->left == nil) || (z->right == nil)) ? z : GetSuccessorOf(z);
    x= (y->left == nil) ? y->right : y->left;
    if (root == (x->parent = y->parent)) {
        root->left=x;
    } else {
        if (y == y->parent->left) {
            y->parent->left=x;
        } else {
            y->parent->right=x;
        }
    }
    if (y != z) {

        y->left=z->left;
        y->right=z->right;
        y->parent=z->parent;
        z->left->parent=z->right->parent=y;
        if (z == z->parent->left) {
            z->parent->left=y;
        } else {
            z->parent->right=y;
        }
        if (!(y->red)) {
            y->red = z->red;
            DeleteFixUp(x);
        } else
            y->red = z->red;
        delete z;
    } else {
        if (!(y->red)) DeleteFixUp(x);
        delete y;
    }
    return returnValue;
}

TNode * TRedBlackTree::Search(TData value) {
    TNode * x;
    x = root->left;
    while (x != nil) {
        if (value == x->key) {
            return x;
        }
        else if (value > x->key) {
            x = x->right;
        }
        else {
            x = x->left;
        }

    }
    std::cout <<"NoSuchWord"<<std::endl;
    return nullptr;
}

bool TRedBlackTree::Serialize(char * filename) {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "Error: could't create file" << std::endl;
        return 0;
    }
    SerializeRec(root->left, file);
    file.close();
    std::cout << "OK" << std::endl;
    return  1;
}

void TRedBlackTree::SerializeRec(TNode * node, std::ostream &file) {
    if (node == nil) {
        file << "# 0 2 ";
        return;
    }
    else {
        file << node->key << node->red << " ";
        SerializeRec(node->left, file);
        SerializeRec(node->right, file);
    }
}

bool TRedBlackTree::Deserialize(char * filename) {
    readErrors = false;
    std::ifstream file(filename);
    if (file.fail()) {
        std::cout << "Error: couldn't open file" << std::endl;
        return 0;
    }
    root->left = DeserializeRec(root, file);
    file.close();
    if (!readErrors) {
        std::cout << "OK" << std::endl;
        return true;
    }
    else {
        std::cout << "Error: couldn't read file" << std::endl;
        return false;
    }
}

TNode * TRedBlackTree::DeserializeRec(TNode * prevnode, std::istream &file) {
    TNode *newnode = new TNode();
    file >> newnode->key.word >> newnode->key.key >> newnode->red;
    if (file.fail()) {
        delete newnode;
        readErrors = true;
        return nullptr;
    }
    newnode->parent = prevnode;

    if (newnode->red == 2) {
        delete newnode;
        return nil;
    }

    newnode->left = DeserializeRec(newnode, file);
    newnode->right = DeserializeRec(newnode, file);
    return newnode;
}