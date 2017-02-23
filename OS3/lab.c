#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include "stdbool.h"

typedef struct {
    int firstPlayer;
    int secondPlayer;
    int k;
    int currentTour;
} TData;

TData thisData;

void * Experiment (void * arg)
{
    int firstPoints = 0;
    int secondPoints = 0;

    long exitVal;

    for (int i = 0; i < thisData.k; ++i) {
        firstPoints += 2 + rand() % 11;
        secondPoints += 2 + rand() % 11;
    }
    if ( (firstPoints + thisData.firstPlayer) > (secondPoints + thisData.secondPlayer) ) {
        exitVal = 1;
    }
    else  if ((firstPoints + thisData.firstPlayer) < (secondPoints + thisData.secondPlayer)){
        exitVal = 2;
    }
    else {
        exitVal = 0;
    }
    pthread_exit((void*)exitVal);

}


int main(int argc, char * argv[])
{


    int firstSum, secondSum, k, expNum, currentTour;
    TData data;


    printf("Players' points: ");
    scanf("%d %d", &data.firstPlayer, &data.secondPlayer);

    printf("Enter number of tours: ");
    scanf("%d", &data.k);
    printf("Enter current tour: ");
    scanf("%d", &data.currentTour);
    printf("Enter number of experiments: ");
    scanf("%d", &expNum);

    int threadsNum = 0;
    if (argc > 1) {
        if (atoi(argv[1]) > expNum) {
            threadsNum = expNum;
        }
        else {
            threadsNum = atoi(argv[1]);
        }
    }
    else {
        printf("\n// Using max number of threads\n");
        threadsNum = expNum;
    }


    data.k -= data.currentTour;

    pthread_t threads[threadsNum];
    thisData = data;
    int firstWins = 0, secondWins = 0;
    double chanceToWin;

    for (int j = 0; j < (expNum / threadsNum); ++j) {

        for (int i = 0; i < threadsNum; ++i) {
            int res = pthread_create(&threads[i], NULL, Experiment, NULL);
            if (res) {
                printf("Error with creating thread\n");
                return -1;
            }
        }

        for (int i = 0; i < threadsNum; ++i) {
            int res;
            pthread_join(threads[i], (void **) &res);
            if (res == 1) {
                ++firstWins;
            }
            else if (res == 2) {
                ++secondWins;
            }
            else {
                ++firstWins;
                ++secondWins;
            }
        }
    }

    /*remaining exp*/


    for (int i = 0; i < (expNum % threadsNum); ++i) {
        int res = pthread_create(&threads[i], NULL, Experiment, NULL);
        if (res) {
            printf("Error with creating thread\n");
            return -1;
        }
    }

    for (int i = 0; i < (expNum % threadsNum); ++i) {
        int res;
        pthread_join(threads[i], (void **) &res);
        if (res == 1) {
            ++firstWins;
        } else if (res == 2) {
            ++secondWins;
        } else {
            ++firstWins;
            ++secondWins;
        }
    }

    /* result*/

    chanceToWin = ((double)firstWins / (expNum)) * 100;
    printf("Chances to win: %.2f / %.2f\n",
           chanceToWin, 100 - chanceToWin);
    return 0;
}