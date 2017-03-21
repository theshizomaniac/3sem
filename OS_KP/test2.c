#include "stdio.h"

int main()
{
        char * a = NULL;
        int i = 10;
        size_t size;
        while (i-->0) {
        getline(&a,&size,stdin); 
        printf("\033[A");
        printf("\33[2K\r");
        printf("Alex: %s", a);
        printf("> ");
        }
}
