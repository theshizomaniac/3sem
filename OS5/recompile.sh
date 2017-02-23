gcc -o tlist.o -c TList.c -fPIC
gcc -shared -o mylist.so tlist.o 
gcc -rdynamic dlist.c -o dlist -ldl

