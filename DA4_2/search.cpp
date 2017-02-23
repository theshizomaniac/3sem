#include <iostream>
#include <vector>
#include <cstring>
//#include <stdlib.h>
#include <sstream>
#include <time.h>
void search (std::vector <unsigned long long> &text,
    std::vector <unsigned long long > &pattern,
       std::vector <unsigned long long > &res)
       {
        int M = pattern.size();
    int N = text.size();
 
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        int j;
 
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
        {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        {
            res.push_back(j);
        }
    }
       }




int main()
{
long start = clock();
    std::vector <unsigned long long> text;
    std::vector <unsigned long long > pattern;
    unsigned long long piece;
     std::string string;
    std::getline(std::cin, string);
    std::istringstream iss(string);
    while (iss >> piece) {
        pattern.push_back(piece);
    }
     while(std::getline(std::cin, string)) {
        std::istringstream iss(string);
        while (iss >> piece) {
            text.push_back(piece);
        }
      }
      std::vector <unsigned long long > res;
    search(text, pattern, res);       
    long end = clock();
    std::cout << "time = " << (end - start) / (CLOCKS_PER_SEC/1000)<< std::endl;
}
