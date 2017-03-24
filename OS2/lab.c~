#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include<sys/types.h>
#include<sys/wait.h>
#include "stdbool.h"
int main(int argc, char* argv[])
{
    char filename [255];

    printf("Enter filename: ");
    scanf("%s", &filename);
    printf("Enter number of child processes: ");
    int n, m;
    scanf("%d", &n);
    pid_t childProcess[n];
    pid_t pid;
    printf("Enter m: ");
    scanf("%d", &m);

    for (int i = 0; i < n; i++) {
        int parToChild[2];
        pipe(parToChild);

        int childToPar [2];
        pipe(childToPar);

        pid = fork();
        if (! pid) {
            close(parToChild[1]);
            close(childToPar[0]);


            read(parToChild[0], filename, 255 * sizeof(char));

            FILE * oFile;
            if ( ! (oFile = fopen(filename, "a")) ) {
                printf("Couldn't open file\n");
                exit(1);
            }

            bool cnt = true;
            write(childToPar[1], &cnt, sizeof(bool));
            int arraySize;

            read(parToChild[0], &arraySize, sizeof(int));
            int buff [arraySize];

            write(childToPar[1], &cnt, sizeof(bool));
            for (int j = 1; j <= arraySize; j++) {
                read(parToChild[0], &buff[j], sizeof(int));
            }

            for (int k = 1; k <= m; k++) {
                fprintf(oFile, "%d ", buff[k]);
            }
            fprintf(oFile, "\n");
            fclose(oFile);

            exit(0);
        }
        else if (pid < 0) {
            printf("Error with creating child process\n");
            return 0;
        }
        else {
            childProcess[i] = pid;
            close(parToChild[0]);
            close(childToPar[1]);

            write(parToChild[1], filename, strlen(filename) * sizeof(char));

            bool cnt = true;
            read(childToPar[0], &cnt, sizeof(bool));

            write(parToChild[1], &m, sizeof(int));
            read(childToPar[0], &cnt, sizeof(bool));

            for (int i = 1; i <= m; i++) {
                write(parToChild[1], &i, sizeof(int));
            }
            waitpid(pid, NULL, 0);
        }
    }
}
