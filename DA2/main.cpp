
#include "rbtree.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

#include <fstream>


void ToLower(char * word) {
    int i = 0;
    while (word[i] != '\0') {
        word[i] = tolower(word[i]);
        i++;
    }
}

int main() {
    TRedBlackTree * tree = new TRedBlackTree();

    TNode * temp;
    char  c;
    while (1) {
        c = getchar();
        switch (c) {
            case '+':
            {
                char tmpWord [257];
                unsigned long long tmpKey;

                std::cin >> tmpWord >> tmpKey;
                ToLower(tmpWord);
                temp = tree->Insert(tmpWord, tmpKey, strlen(tmpWord)+1);
                if (temp != nullptr) {
                    std::cout << "OK" << std::endl;
                }
                break;
            }
            case '-':
            {
                char tmpWord[257];
                std::cin >> tmpWord;
                ToLower(tmpWord);
                temp = tree->Search(tmpWord);
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
                }
                else if (!strcmp(sv, "Load")) {
                    TRedBlackTree * newTree = new TRedBlackTree();
                    bool success;
                    success = newTree->Deserialize(filename);
                    if (success) {
                        delete tree;
                        tree = newTree;
                    }
                    else {
                        delete newTree;
                    }
                }
                else {
                    tree->PrintTree();
                }
                break;
            }
            case '\n':
            {
                break;
            }
            default:
            {
                int i = 0;
                char tmpWord[257];
                while (c != '\n') {
                    tmpWord[i] = c;
                    c = getchar();
                    i++;
                }
                tmpWord[i] = '\0';
                ToLower(tmpWord);
                i = 0;
                temp = tree->Search(tmpWord);
                if (temp != nullptr) {
                    std::cout << "OK: " << temp->GetKey() << std::endl;
                }
                break;
            }
        }
    }
}