#include <iostream>
#include <cstring>
//#include <stdlib.h>
#include <sstream>
#include <vector>

typedef struct TRes {
    int num;
    int string;
} TRes;

int resIndex = 0;
size_t resSize = 100;

class ZAlgorithm {
public:
    void calculateZ(std::vector <unsigned long long> &input, size_t inputLength, std::vector <int> &Z) {
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
                     int lastString, int lastAlpha, int lastEntry) {

        size_t pSize = pattern.size();
        size_t tSize = text.size();

        std::vector <int> Z (tSize);
        calculateZ(text, Z.size(), Z);

        int j = resIndex;
        int possibleEntry = 0;
        bool entryIndicator = false;
        for (int k = 1; k < tSize; ++k) {
            std::cout << "result Z[" << k <<"] = " << Z[k] << std::endl;
            if (Z.at(k) == pSize) {
                int tmpNum = k - pattern.size();
                TRes tmpRes;
                for (int t = 0; t < stringsBar.size(); ++t) {
                    std::cout << "strings : "<<stringsBar[t] << " ";
                }
                if (stringsBar.size() > 1) {
                    for (int strNum = 1; strNum < stringsBar.size(); ++strNum) {
                        if (tmpNum <= (stringsBar.at(strNum) ) ) {
                            std::cout << "str = " << stringsBar[strNum] << " strnum =" << strNum << " tmpNum = "
                            << tmpNum << std::endl;

                            tmpRes.num = tmpNum - stringsBar.at(strNum - 1);
                            tmpRes.string = strNum;
                            break;
                        }

                    }
                }
                else {
                    //std::cout << " tmpNum = " << tmpNum << std::endl;
                    tmpRes.num = tmpNum;
                    tmpRes.string = 1;
                }
                if (lastAlpha != 0) {
                    tmpRes.string += lastString;
                }
                if (lastEntry && j == resIndex) {
                    std::cout << "last entry: " << lastEntry << std::endl;
                    tmpRes.num = lastEntry - pSize;
                    lastEntry = 0;
                }
                result.at(resIndex) = tmpRes;
                ++resIndex;
                if (resIndex >= resSize) {
                    resSize *= 2;
                    result.resize(resSize);
                }
                //result.push_back(tmpRes);
            }
            else if (Z.at(k) == (tSize - k) && Z.at(k) < pSize && (!entryIndicator) ) {
                possibleEntry = k;
                entryIndicator = true;
            }
        }
        return  possibleEntry;
    }
};


int main()
{
    //std::vector <unsigned long long> text (20);
    std::vector <unsigned long long> pattern (5);
    std::vector <int> stringsBar (5);

    ZAlgorithm * zAlgorithm = new ZAlgorithm();
    std::vector <TRes> result (100);

    int pSize = 5;
    int tSize = 20;
    int sSize = 5;
    int i = 0;
    unsigned long long piece;
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
    std::vector <unsigned long long> text (pattern.size()* 6 + 1);
    int j;
    for (j = 0; j < pattern.size(); ++j) {
        text.at(j) = pattern.at(j);
    }
    text.at(j) = '?';
    i = j + 1;
    tSize = 1 + pattern.size() * 6;
    pSize = pattern.size();
    int lastString = 0;
    int lastAlpha = 0;
    int line = 0;
    int count;
    int possibleEntry = 0;
    int added = 0;
    //i = 0;
    stringsBar.at(0) = 0;
    //stringsBar.push_back(0);// = 0;
    while(std::getline(std::cin, string)) {
        count = 0;
        ++line;
        std::istringstream iss(string);
        while (iss >> piece) {
            text.at(i) = piece;
            ++i;
            ++count;
            if (i >= tSize) {
                tSize *= 2;
                text.resize(tSize + 1);
            }
        }
        stringsBar.at(line) = count;
        //stringsBar.push_back(count);// [line] count;
        if ( line != 0) {
            stringsBar.at(line) += stringsBar.at(line - 1) + added;
        }

        if (line >= sSize - 1) {
            sSize *= 2;
            stringsBar.resize(sSize);
        }
        if (i > pattern.size() * 5) {
            //lastString += line;
            text.resize(i);
            stringsBar.resize(line + 1);
            std::cout << "b4 Z strBar\n";
            for (int n = 0; n < stringsBar.size(); ++n) {
                std::cout << stringsBar.at(n) << " ";
             }
            possibleEntry = zAlgorithm->matchPattern(text, pattern, stringsBar, result, lastString, lastAlpha, possibleEntry);
            std::cout << "poss entry = " << possibleEntry << std::endl;
            int stringN = 0;
            i = pSize + 1;
            if (possibleEntry) {
                for (int k = possibleEntry; k < text.size(); ++k) {
                    text.at(k - possibleEntry) = text.at(k);
                }
                i += text.size() - possibleEntry;
                if (line != 1) {
                    for (int strNum = 0; strNum < stringsBar.size(); ++strNum) {
                        if (possibleEntry <= (stringsBar.at(strNum) + pSize + 1) ) {
                            stringN = strNum;
                            break;
                        }
                    }
                    lastString +=stringN;// line;
                    lastAlpha += stringsBar.at(line - 1);
                    //added = text.size() - possibleEntry;
                    stringsBar.at(1) = text.size() - possibleEntry;
                    std::cout << "line " << line <<  "laststr = " << lastString << "str = " << stringN<< std::endl;
                    //stringsBar.at(1) = stringsBar.at(stringN);
                    //stringsBar.resize(6);
                    if (stringN != line) line = 1;//1;
                    else {
                        line = 0;
                    }
                    sSize = line + 4;
                }
                else {
                    //lastString += line;
                    lastAlpha += stringsBar.at(line);
                    line = 1;
                    stringsBar.at(1) = text.size() - possibleEntry;
                    stringsBar.resize(5);
                    sSize = 4;
                    added = 0;

                }
                for (int l = 0; l < text.size(); ++l) {
                    std::cout << text.at(l) << " ";
                }
                printf("\n");
                for (int m = 0; m < stringsBar.size(); ++m) {
                    std::cout << stringsBar[m] << " ";
                }
                printf("\n");
            }
            else {
                lastString += line;
                lastAlpha += stringsBar.at(line);
                line = 0;
                stringsBar.resize(5);
                sSize = 4;
                added = 0;
            }


            text.resize(pSize + 1 + 20);
            tSize = pSize + 21;
            stringsBar.at(0) = 0;
        }
    }
    if (line != 0) {
        if (line == 1) {
            stringsBar.resize(line);
        }
        else {
            stringsBar.resize(line + 1);
        }
        text.resize(i);
        std::cout << "b4 Z strBar\n";
        for (int n = 0; n < stringsBar.size(); ++n) {
            std::cout << stringsBar.at(n) << " ";
        }
        zAlgorithm->matchPattern(text,pattern,stringsBar, result, lastString,lastAlpha, possibleEntry);
    }
    result.resize(resIndex);
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result.at(i).string << ", " << result.at(i).num << std::endl;
    }

    delete zAlgorithm;
}

