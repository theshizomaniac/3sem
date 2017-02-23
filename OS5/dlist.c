//
// Created by mrhacker on 1/5/17.
//

#include <dlfcn.h>
#include <memory.h>
#include "stdio.h"
#include <string.h>
#include <event.h>
#include "malloc.h"

#define MAX_STRING 255

typedef struct TList {
    struct TNode * head;
    int size;
} TList;

typedef struct TNode {
    struct TNode * next;
    struct TNode * prev;
    uint32_t data;
} TNode;

void invoke_method(char *lib, char *method, float argument )
{
  void *dl_handle;
  float (*func)(float);
  char *error;

  /* Open the shared object */
  dl_handle = dlopen( lib, RTLD_LOCAL |RTLD_LAZY );
  if (!dl_handle) {
    printf( "!!! %s\n", dlerror() );
    return;
  }

  /* Resolve the symbol (method) from the object */

  if (!strcmp(method, "Init")) {
      TList(*list)();
      list = dlsym( dl_handle, method );
      error = dlerror();
      if (error != NULL) {
          printf( "!!! %s\n", error );
          return;
      }
      /* Call the resolved method and print the result */
      (*list)();
      return;
  }
  func = dlsym( dl_handle, method );
  error = dlerror();
  if (error != NULL) {
    printf( "!!! %s\n", error );
    return;
  }

  /* Call the resolved method and print the result */
  printf("  %f\n", (*func)(argument) );

  /* Close the object */
  dlclose( dl_handle );

  return;
}

void LoadList()
{
    void *dl_handle;
    char *error;

    /* Open the shared object */
    dl_handle = dlopen("./mylist.so", RTLD_LOCAL | RTLD_LAZY );
    if (!dl_handle) {
        printf( "!!! %s\n", dlerror() );
        return;
    }
    char method [50];
    char arg1[50],arg2[50],arg3[50];

    TList * w_list;
    while (1) {

        printf("> ");

        scanf("%s", method);
        if (!strcmp(method, "exit")) {
            void (*func)(TList*);
            func = dlsym( dl_handle, "FreeList");
            error = dlerror();
            if (error != NULL) {
                printf( "!!! %s\n", error );
                return;
            }
            (*func)(w_list);
            free(w_list);
            dlclose( dl_handle );
            return;
        }
        else if (!strcmp(method,"Init")) {
            TList *(*list)();
            list = dlsym( dl_handle, method );
            error = dlerror();
            if (error != NULL) {
                printf( "!!! %s\n", error );
                return;
            }
            /* Call the resolved method and print the result */
            w_list = (*list)();
        }
        else if (!strcmp(method,"Print")){
            void (*func)(TList*);
            func = dlsym( dl_handle, method );
            error = dlerror();
            if (error != NULL) {
                printf( "!!! %s\n", error );
                return;
            }
            (*func)(w_list);

        }
        else if (!strcmp(method,"Insert")){
            uint32_t data;
            int in_index;
            scanf("%d %d", &data, &in_index);
            void (*func)(TList*,uint32_t,int);
            func = dlsym( dl_handle, method );
            error = dlerror();
            if (error != NULL) {
                printf( "!!! %s\n", error );
                return;
            }
            (*func)(w_list,data,in_index);

        }
        else if (!strcmp(method, "Remove")) {
            int rm_index;
            scanf("%d", &rm_index);
            void (*func)(TList*,int);
            func = dlsym( dl_handle, method );
            error = dlerror();
            if (error != NULL) {
                printf( "!!! %s\n", error );
                return;
            }
            (*func)(w_list,rm_index);
        }


    }


}


int main(int argc, char * argv[])
{
    char line[MAX_STRING+1];
    char lib[MAX_STRING+1];
    char method[MAX_STRING+1];
    float argument;
    LoadList();
    return 0;
    while (1) {

        printf("> ");

        line[0]=0;
        fgets( line, MAX_STRING, stdin);

        if (!strcmp(line, "bye")) break;

        sscanf( line, "%s %s %f", lib, method, &argument);

        invoke_method( lib, method, argument );

    }
}