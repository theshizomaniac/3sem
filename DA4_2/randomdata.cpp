#include <iostream>
#include <random>
#include <ctime>
#include <climits>
int main()
{
        int n;
        std::cin >> n;
         int m;
        std::cin >> m;
        int c = 0;
        std::random_device rd;
        std::uniform_int_distribution<unsigned long long> uid(0, ULLONG_MAX);
        while (c != m) {
            std::cout << uid(rd) << " ";
            c++;


         }
         std::cout << std::endl;
         c = 0;
        while (c != n) {
            std::cout << uid(rd) << " ";
            c++;


         }
}
