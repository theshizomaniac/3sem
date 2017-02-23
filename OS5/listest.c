//
// Created by mrhacker on 1/4/17.
//

#include "stdio.h"
#include "event.h"
#include "TList.h"




int main()
{
    TList * list = Init();
    for (uint32_t i = 0; i < 10; ++i) {
        Insert(list,i,-1);
    }
    Print(list);
    for (int j = 0; j < 10; ++j) {
        Remove(list,j);
    }
    Print(list);
    return 0;
}