#include "Tree.h"
#include <stdlib.h>
#include <stdio.h>

TTree::TTree() : root(nullptr){}

TTree::TTree(const TTree& orig) {
    root = orig.root;
}

void TTree::goThrough(const TTree &tTree)const {
    for(int i = 0; i < N && root->child[i] != nullptr; i++){
        goThrough((const TTree &) root->child[i]);
        std::cout << root->child[i] << std::endl;
    }
    std::cout << root << std::endl;
}

std::ostream& operator << (std::ostream& os, const TTree& tTree){
    TTreeNode *node = tTree.root;
    tTree.goThrough(tTree);
    return os;
}

void TTree::add(Hexagon &&hexagon) {
    TTreeNode *node = this->root;
    int a;
    std::cout << "enter number from 1 to 5" << std::endl;
    std::cin >> a;
    while (node->child[a-1]){
        node = node->child[a-1];
        std::cout << "enter number from 1 to 5" << std::endl;
        std::cin >> a;
    }
    node = new TTreeNode(hexagon);
}

bool TTree::empty() {
    return root = nullptr;
}

Hexagon TTree::deleteNode() {
    TTreeNode *node = this->root;
    int a;
    int path[10];
    int i = 1;
    Hexagon result;
    std::cout << "enter number from 1 to 5" << std::endl;
    std::cin >> a;
    path[0] = a;

    while (node->child[a-1]){
        node = node->child[a-1];
        std::cout << "enter number from 1 to 5" << std::endl;
        std::cin >> a;
        path[i] = a;
        i++;
    }
    result = node->GetHexagon();
    node = this->root;
    for(int j = 0; j < i-1; j++){
        node = node->child[path[j]];
    }
    delete node;
    return result;
}

TTree::~TTree() {
    delete root;
}

void TTree::setRoot(Hexagon &&hexagon) {
    root = new TTreeNode(hexagon);
}

Hexagon TTree::getNode() {
    TTreeNode *node = this->root;
    int a;
    std::cout << "enter number from 1 to 5, type 6 to get root" << std::endl;
    std::cin >> a;
    while (a!=6){
        node = node->child[a-1];
        std::cout << "enter number from 1 to 5, type 6 to stop" << std::endl;
        std::cin >> a;
    }
    Hexagon hexagon;
    hexagon = node->GetHexagon();
    return hexagon;
}
