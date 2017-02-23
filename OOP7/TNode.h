//
// Created by mrhacker on 12/20/16.
//

#ifndef OOP6_TNODE_H
#define OOP6_TNODE_H

#include <memory>
template < class A > class TNode {
public:
    TNode () { }
    ~TNode() {
    }
    TNode (std::shared_ptr <A> newdata) {
        data = newdata;
        left = right = parent = nullptr;
    }

    std::shared_ptr <A> data;
    TNode <A> * left;
    TNode <A> * right;
    TNode <A> * parent;
};

#endif //OOP6_TNODE_H
