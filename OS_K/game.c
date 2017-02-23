#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>

typedef struct TBet{
    char colour;
    int number;
    int sum;
} TBet;

typedef struct TPlayer {
    int balance;
    char name[50];
    bool winner;
    TBet bet;
} TPlayer;

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }
    char myName[256];
    printf("Hello!\nEnter your name: ");
    scanf("%s", myName);
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    int someNum;
    TPlayer thisPlayer;
    printf("%s\n", myName);
    /*//n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    if(fputs(recvBuff, stdout) == EOF)
    {
        printf("\n Error : Fputs error\n");
    }*/
    TBet myBet;

    printf("Make bet: \n  color (red, black, or none): ");
    scanf("%s", &myBet.colour);
    printf("number (0 - 36) or -1 if no number: ");
    scanf("%d", &myBet.number);
    printf("Sum:  ");
    scanf("%d", &myBet.sum);

    strcpy(thisPlayer.name, myName);
    thisPlayer.winner = false;
    thisPlayer.balance = 0;
    thisPlayer.bet = myBet;
    //write(sockfd, myName, sizeof(myName));
    write(sockfd, &thisPlayer, sizeof(TPlayer));
    n = read(sockfd, &someNum, sizeof(int));
    if (n < 0) {
        printf("error receiving!\n");
    }
    printf("Your start balance is %d\n", someNum);
    /*while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0 && (n = read(sockfd, &someNum, sizeof(int)))> 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
        printf("connection number = %d\n", someNum);
    } */
    printf("After read\n");
    if(n < 0)
    {
        printf("\n Read error \n");
    }

    return 0;
}

