#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

#define TCP_USER_TIMEOUT 18  // how long for loss retry before timeout [ms]
int main(int argc, char *argv[])
{
    int listenfd = 0, connfd[10];// = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    int connectionNumber = 0;
    while(1)
    {
        printf("Waiting...\n");
        connfd[connectionNumber] = accept(listenfd, (struct sockaddr*)NULL, NULL);
        printf("connection number = %d\n", connectionNumber+1);
        //ticks = time(NULL);
        //snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        char username[256];
        int userBalance = 1000;
        read(connfd[connectionNumber], username, sizeof(username));
        printf("%s\n", username);
        if(!strcmp(username,"crash")) {
            break;
        }
        //write(connfd, sendBuff, strlen(sendBuff));
        //sleep(1);
        write(connfd[connectionNumber], &userBalance, sizeof(int));
        close(connfd[connectionNumber]);
        ++connectionNumber;
        sleep(1);

     }
    printf("done\n");
    exit(0);
     return 0;
}

