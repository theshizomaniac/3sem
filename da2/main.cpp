#include <iostream>
#include "rbtree.h"
#include <stdio.h>
#include <cstring>

int main() {
    TRedBlackTree * tree = new TRedBlackTree();
    TData tmp_data;
    TNode * temp;

    char  c;
    while (1) {
        c = getchar();
        switch (c) {
            case '+':
            {
                TData tmpData;
                std::cin >> tmpData.word >> tmpData.key;
                tmpData.ToLower();
                temp = tree->Insert(tmpData);
                if (temp != nullptr) {
                    std::cout << "OK" << std::endl;
                }
                break;
            }
            case '-':
            {
                std::cin >> tmp_data.word;
                tmp_data.ToLower();
                temp = tree->Search(tmp_data);
                if (temp != nullptr) {
                    tree->DeleteNode(temp);
                    std::cout << "OK" << std::endl;
                }
                break;
            }
            case EOF:
            {
                delete tree;
                return 0;
            }
            case '!':
            {
                char sv[10], filename[255];
                std::cin >> sv >> filename;
                if (!strcmp(sv, "Save")) {
                    tree->Serialize(filename);
                } else if (!strcmp(sv, "Load")) {
                    TRedBlackTree * newTree = new TRedBlackTree();
                    bool ifSuccess;
                    ifSuccess = newTree->Deserialize(filename);
                    if (ifSuccess) {
                        delete tree;
                        tree = newTree;
                    }
                    else {
                        delete newTree;
                    }
                }
                break;
            }
            case '\n':
            {
                break;
            }
            case '*':
            {
                std::cin >> tmp_data.word;
                temp = tree->Search(tmp_data);
                std::cout << temp->parent->key << std::endl;
                break;
            }
            default:
            {
                int i = 0;
                while (c != '\n') {
                    tmp_data.word[i] = c;
                    c = getchar();
                    i++;
                }
                tmp_data.word[i] = '\0';
                tmp_data.ToLower();
                temp = tree->Search(tmp_data);
                if (temp != nullptr) {
                    std::cout << "OK: " << temp->key.key << std::endl;
                }
                break;
            }
        }
    }
}