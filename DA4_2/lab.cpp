//
// Created by mrhacker on 12/2/16.
//

#include <iostream>
#include <cstring>
//#include <stdlib.h>
#include <sstream>
#include <vector>
#include <time.h>
typedef struct TElement {
    unsigned long long num;
    int index;
    int string;
} TElement;

typedef struct TRes {
    int num;
    int string;
} TRes;

int resIndex = 0;
size_t resSize = 100;

class TZAlgorithm {
public:
    void CalculateZ(std::vector <TElement> &input, size_t inputLength, std::vector <int> &Z) {
        int left = 0;
        int right = 0;
        for (int k = 1; k < inputLength; k++) {
            if (k > right) {
                left = right = k;
                while (right < inputLength && input[right].num == input[right - left].num) {
                    right++;
                }
                Z[k] = right - left;
                right--;
            }
            else {
                int k1 = k - left;
                if (Z[k1] < right - k + 1) {
                    Z[k] = Z[k1];
                }
                else {
                    left = k;
                    while (right < inputLength && input[right].num == input[right - left].num) {
                        right++;
                    }
                    Z[k] = right - left;
                    right--;
                }
            }
        }
    }


     void MatchPattern(std::vector <TElement> &text,
                     std::vector <unsigned long long> &pattern,
                     std::vector <TRes> &result,
                     std::vector <TElement> &entries) {

        size_t pSize = pattern.size();
        size_t tSize = text.size();

        std::vector<int> Z(tSize);
        CalculateZ(text, Z.size(), Z);
         int checkOnce = true;
        for (int k = 1; k < tSize; ++k) {
            if (Z.at(k) == pSize) {
                result.at(resIndex).num = text.at(k).index;
                result.at(resIndex).string = text.at(k).string;
                ++resIndex;
                if (resIndex >= resSize) {
                    resSize *= 2;
                    result.resize(resSize + 1);
                }
            }
            else if (Z.at(k) == (tSize - k) && Z.at(k) < pSize && checkOnce) {
                for (int i = k; i < tSize; ++i) {
                    entries.push_back(text.at(i));
                }
                checkOnce = false;
            }
        }
    }
};


int main()
{
    long start = clock();
    //std::vector <unsigned long long> text (20);
    std::vector <unsigned long long> pattern (5);
    TZAlgorithm * zAlgorithm = new TZAlgorithm();
    std::vector <TRes> result (100);
    int pSize = 5;
    int tSize = 20;
    int i = 0;
    std::string string;
    std::getline(std::cin, string);
    std::istringstream iss(string);
    while (iss >> pattern[i]) {
        ++i;
        if (i >= pSize) {
            pSize *= 2;
            pattern.resize(pSize);
        }
    }
    pattern.resize(i);
    std::vector <TElement> entries;
    std::vector <TElement> text (pattern.size()* 6 + 1);
    int j;
    for (j = 0; j < pattern.size(); ++j) {
        text.at(j).num = pattern.at(j);
    }
    text.at(j).num = '?';
    i = j + 1;
    tSize =pattern.size() * 6;
    pSize = pattern.size();
    int line = 0;
    int count;
    //stringsBar.push_back(0);// = 0;
    while(std::getline(std::cin, string)) {
        count = 0;
        ++line;
        std::istringstream iss(string);
        while (iss >> text.at(i).num) {
            //text.at(i).num = piece;
            ++count;
            text.at(i).index = count;
            text.at(i).string = line;
            ++i;
            if (i >= tSize) {
                tSize += pSize * 6;
                text.resize(tSize);
            }
        }
        if (i > pattern.size() * 5) {
            //lastString += line;
            text.resize(i); /////zzzzzzzz
            zAlgorithm->MatchPattern(text, pattern, result, entries);
            i = pSize + 1;
            if (entries.size()) {
                for (int k = 0; k < entries.size(); ++k) {
                    text.at(k + pSize + 1).num = entries.at(k).num;
                    text.at(k + pSize + 1).index = entries.at(k).index;
                    text.at(k + pSize + 1).string = entries.at(k).string;
                }
                i += entries.size();
                entries.clear();
            }
            text.resize(pSize * 6);
            tSize = pSize * 6;

        }
    }
    if (line != 0) {
        text.resize(i);
        zAlgorithm->MatchPattern(text, pattern, result, entries);
    }
    result.resize(resIndex);
    /*for (int i = 0; i < result.size(); ++i) {
        std::cout << result.at(i).string << ", " << result.at(i).num << std::endl;
    }*/
    long end = clock();
        std::cout << "time = " << (end - start) / (CLOCKS_PER_SEC/1000)<< std::endl;
    delete zAlgorithm;
}

