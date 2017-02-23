#include <iostream>
#include <cstring>
//#include <stdlib.h>
#include <sstream>
#include <vector>

typedef struct TRes {
    int num;
    int string;
} TRes;



class ZAlgorithm {
public:
    void calculateZ(unsigned long long * input, size_t inputLength, std::vector <int> &Z) {
       // size_t inputLength = strlen(input);
        //std::cout << input << inputLength <<std::endl;
        //int * Z = new int[inputLength];
        int left = 0;
        int right = 0;
        for (int k = 1; k < inputLength; k++) {
            if (k > right) {
                left = right = k;
                while (right < inputLength && input[right] == input[right - left]) {
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
                    while (right < inputLength && input[right] == input[right - left]) {
                        right++;
                    }
                    Z[k] = right - left;
                    right--;
                }
            }
        }
    }


    int matchPattern(std::vector <unsigned long long> &text,
                        std::vector <unsigned long long> &pattern,
                        std::vector <int> &stringsBar,
                        std::vector <TRes> &result,
                        int lastString, int lastAlpha, int isMoved) {

        size_t pSize = pattern.size();
        size_t tSize = text.size();

        unsigned long long * newString = new unsigned long long [pSize + tSize + 1];
        //std::cout << "pszie = " << pattern.size() << "tSize = " << text.size() << std::endl;

        int i;
        for (i = 0; i < pattern.size(); ++i) {
            newString[i] = pattern[i];
        }
        newString[i] = '?';
        i++;
        //zzzzzzzzzz
        for (int j = i; j < text.size() + pattern.size() + 1; ++j) {
            newString[j] = text[j - pattern.size() - 1];
            i++;
        }
        /*
        for (int l = 0; l < tSize + pSize +1; ++l) {
            std::cout << newString[l] << " ";
        }
        std::cout << std::endl;
        //gggggggggggg*/
        //int currRes = 5;
        std::vector <int> Z (tSize + pSize + 1);
        calculateZ(newString, Z.size(), Z);
        int possibleEntry = 0;
        //int j = 0;

        for (int k = 1; k < tSize + pSize + 1; ++k) {
            //std::cout << "result Z[" << k <<"] = " << Z[k] << std::endl;
            if (Z[k] == pSize) {
                int tmpNum = k - pattern.size();
                TRes tmpRes;
                for (int t = 0; t < stringsBar.size(); ++t) {
                    //std::cout << "strings : "<<stringsBar[t] << " ";
                }
                if (stringsBar.size() > 1) {
                    for (int strNum = 1; strNum < stringsBar.size(); ++strNum) {
                        if (tmpNum <= (stringsBar[strNum]) ) {
                            //std::cout << "str = " << stringsBar[strNum] << " strnum =" << strNum << " tmpNum = "
                                      //<< tmpNum << std::endl;

                            //result[j].num = tmpNum - stringsBar[strNum - 1];
                            //result[j].string = strNum;
                            tmpRes.num = tmpNum - stringsBar[strNum - 1];
                            tmpRes.string = strNum;
                            break;
                        }

                    }
                }
                else {
                        //result[j].num = tmpNum;
                        //result[j].string = 1;
                    //std::cout << " tmpNum = " << tmpNum << std::endl;
                    tmpRes.num = tmpNum;
                    tmpRes.string = 1;
                }
                if (lastAlpha != 0) {
                    //result[j].string += lastString;
                    tmpRes.string += lastString;
                }
                if (isMoved && k == pSize + 1) {
                    tmpRes.string--;
                    tmpRes.num = isMoved;
                }
                result.push_back(tmpRes);
            }
            else if (Z[k] == (pSize + tSize + 1 - k) && Z[k] < pSize) {
             possibleEntry = k - pSize;
            }
        }

        delete [] newString;
        return possibleEntry;
    }

    int resultSize;
};


    int main()
    {
        std::vector <unsigned long long> text (10);
        std::vector <unsigned long long> pattern;
        std::vector <int> stringsBar;

        ZAlgorithm * zAlgorithm = new ZAlgorithm();
        std::vector <TRes> result;

        //int pSize = 5;
        int tSize = 10;
        int i = 0;
        unsigned long long piece;
        std::string string;
        std::getline(std::cin, string);
        std::istringstream iss(string);
        while (iss >> piece) {
            ++i;
            /*if (i > pSize) {
                pSize *= 2;
                pattern.resize(pSize);
            }*/
            pattern.push_back(piece);
        }
        //pattern.resize(i);
        //pSize = i;
        int lastString;
        int lastAlpha = 0;
        int line = 0;
        int count;
        int isMoved;   // 0 if not, else entry index
        //int stringsCount = 3;
        i = 0;

        stringsBar.push_back(0);// = 0;

        while(std::getline(std::cin, string)) {
            count = 0;
            ++line;
            std::istringstream iss(string);
            while (iss >> text[i]) {
                ++i;
                ++count;
                if (i >= tSize) {
                    tSize *= 2;
                    text.resize(tSize);
                }
            }
            //if (line >= stringsCount) {
            //    stringsCount *= 2;
            //    stringsBar.resize(stringsCount);
            //}
            stringsBar.push_back(count);// [line] count;
            if ( line != 0) {
                stringsBar[line] += stringsBar[line - 1];
            }
            if (i > pattern.size() * 3) {   // here dude
                lastString = line;
                text.resize(i);
                //for (int l = 0; l < stringsBar.size(); ++l) {
                //    std::cout << stringsBar[l] << " ";
                //}
                int possibleEntry = zAlgorithm->matchPattern(text, pattern, stringsBar, result, lastString, lastAlpha, isMoved);
                //std::cout << someEntry <<std::endl;
                std::vector <unsigned long long> moved;
                if (possibleEntry != 0) {
                    for (int j = possibleEntry - 1; j < text.size(); ++j) {
                        moved.push_back(text[j]);
                    }
                }
                lastAlpha = stringsBar[line];

                text.clear();
                text.resize(10);
                tSize = 10;
                //stringsBar.resize(3);
                //stringsCount = 3;
                line = 0;
                i = 0;
                if (moved.size() != 0) {
                    for (int l = 0; l < moved.size(); ++l) {
                        text[l] = moved[l];
                    }
                    i = moved.size();
                    isMoved = possibleEntry;
                    moved.clear();
                }
                else {
                    stringsBar.clear();
                }
            }
        }
        if (line != 0) {
            //lastString = line;
            if (lastAlpha != 0) {
                stringsBar.clear();
                stringsBar.push_back(0);
            }
            text.resize(i);
            zAlgorithm->matchPattern(text,pattern,stringsBar, result, lastString,lastAlpha, isMoved);
        }

        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i].string << ", " << result[i].num << std::endl;
        }

        delete zAlgorithm;
    }


