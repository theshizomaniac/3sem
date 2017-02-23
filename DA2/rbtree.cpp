

#include "rbtree.h"
#include <iostream>
#include <cstdlib>
#include <cstring>


unsigned long long TNode::GetKey() {
    return key;
}

TRedBlackTree::TRedBlackTree()
{
    nil = new TNode();
    nil->left = nil->right = nil->parent = nil;
    nil->red = 0;
    nil->word = (char*) std::malloc (sizeof(char));
    nil->word[0] = 0;
    nil->key = 0;

    root = new TNode();
    root->parent = root->left = root->right = nil;
    root->key = 30000;
    root->word = (char*) std::malloc (sizeof(char));
    root->word[0] = 1;
    root->red = 0;
}


TNode::TNode(char * data, unsigned long long iKey, int length) {
    key = iKey;
    word = (char*) std::malloc (length+1 * sizeof(char));
    strcpy(word,data);
}


TNode * TRedBlackTree::Insert(char * iWord, unsigned long long iKey, int length)
{
    TNode * y;
    TNode * x;
    TNode * newNode;
    bool successInsert;
    try {
        x = new TNode(iWord, iKey, length);
    }
    catch (std::bad_alloc) {
        std::cout << "ERROR: not enough memory" << std::endl;
        return nullptr;
    }
    successInsert = BinInsert(x);
    if (!successInsert) {
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
            }
            else {
                if (x == x->parent->right) {
                    x=x->parent;
                    LeftRotate(x);
                }
                x->parent->red=0;
                x->parent->parent->red=1;
                RightRotate(x->parent->parent);
            }
        }
        else {
            y=x->parent->parent->left;
            if (y->red) {
                x->parent->red=0;
                y->red=0;
                x->parent->parent->red=1;
                x=x->parent->parent;
            }
            else {
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
        int cmpRes = strcmp(x->word, z->word);
        if (cmpRes > 0) {
            x = x->left;
        }
        else if (cmpRes == 0) {
            std::cout << "Exist" << std::endl;
            return false;
        }
        else { /* x->key <= z->key */
            x = x->right;
        }
    }
    z->parent = y;
    if ( (y == root) || ( strcmp(y->word, z->word) > 0 ) ) {
        y->left=z;
    }
    else {
        y->right=z;
    }
    return true;
}

TNode::TNode() {}

TNode::~TNode() {
    std::free(word);
}

TRedBlackTree::~TRedBlackTree() {
    if (root->left != nil) {
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
                x=rootLeft;
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
    }
    else {
        y=x->parent;
        while(x == y->right) {
            x=y;
            y=y->parent;
        }
        if (y == root) return(nil);
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
    std::cout << "key = " << node->word <<" red = " << node->red;
    std::cout << "|| left son = " << node->left->word << " right son = " << node->right->word << std::endl;
    Print(node->left);
    Print(node->right);
}

void TRedBlackTree::DeleteNode(TNode * z){
    TNode* y;
    TNode* x;


    y= ((z->left == nil) || (z->right == nil)) ? z : GetSuccessorOf(z);
    x= (y->left == nil) ? y->right : y->left;
    if (root == (x->parent = y->parent)) {
        root->left=x;
    }
    else {
        if (y == y->parent->left) {
            y->parent->left=x;
        }
        else {
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
        }
        else {
            z->parent->right=y;
        }
        if (!(y->red)) {
            y->red = z->red;
            DeleteFixUp(x);
        }
        else
            y->red = z->red;
        delete z;
    }
    else {
        if (!(y->red)) DeleteFixUp(x);
        delete y;
    }
    return;
}

TNode * TRedBlackTree::Search(char * sWord) {
    TNode * x;
    x = root->left;
    while (x != nil) {
        int cmpRes = strcmp(sWord, x->word);
        if (cmpRes == 0) {
            return x;
        }
        else if (cmpRes > 0) {
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
        std::cout << "ERROR: could't create file" << std::endl;
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
        file << node->word << " " << node->key << " " << node->red << " ";
        SerializeRec(node->left, file);
        SerializeRec(node->right, file);
    }
}

bool TRedBlackTree::Deserialize(char * filename) {
    readErrors = false;
    std::ifstream file(filename);
    if (file.fail()) {
        std::cout << "ERROR: couldn't open file" << std::endl;
        return 0;
    }
    root->left = DeserializeRec(root, file);
    file.close();
    if (!readErrors) {
        std::cout << "OK" << std::endl;
        return true;
    }
    else {
        std::cout << "ERROR: couldn't read file" << std::endl;
        return false;
    }
}

TNode * TRedBlackTree::DeserializeRec(TNode * prevnode, std::istream &file) {
    TNode * newnode = new TNode();
    char tmpWord [257];
    file >> tmpWord >> newnode->key >> newnode->red;
    if (file.fail()) {
        delete newnode;
        readErrors = true;
        return nullptr;
    }
    newnode->word = (char*) std::malloc((strlen(tmpWord)+1) * sizeof(char));
    strcpy(newnode->word, tmpWord);
    newnode->parent = prevnode;
    if (newnode->red == 2) {
        delete newnode;
        return nil;
    }

    newnode->left = DeserializeRec(newnode, file);
    newnode->right = DeserializeRec(newnode, file);
    return newnode;
}