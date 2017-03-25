gcc -std=c11 -o tlist.o -c TList.c -fPIC
gcc -shared -o mylist.so tlist.o 
gcc -rdynamic -std=c11 dlist.c -o dlist2 -ldl

