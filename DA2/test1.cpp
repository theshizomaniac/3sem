#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>


void gen_random(char *s, const int len) {
    static const char alphanum[] =
            "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = '\0';
}

int main(int argc, char* argv[])
{
    std::ofstream fileInput;
    fileInput.open("testdataminus.txt");
    std::ofstream fileRead;
    fileRead.open("testdataplus.txt");
    std::ofstream fileCheck;
    fileCheck.open("testdatacheck.txt");
    char string[256];
    unsigned long long n = atoi(argv[1]);
    for (int i = 0; i < n; i ++) {
        gen_random(string, 1+ rand() % 255);
        fileInput << "+ " << string << " " << rand() << '\n';
        fileRead << "-" << string << '\n';
        fileCheck << string << '\n';
    }
}
