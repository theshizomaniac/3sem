#include <string.h>
#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#define MAX_MESSAGE_SIZE 255
#define MAX_CMD_SIZE 10
#define NAME_SIZE 10

typedef struct MessageData {
    double userId;
    char name[10];
    char command[MAX_CMD_SIZE];
    char message[MAX_MESSAGE_SIZE];
} MessageData;



int main(int argc, char * argv[])
{
    /*if (argc == 0) {
        printf("Enter port: ");
        scanf("%s", argv[1]);
    }*/
    //void* context = zmq_ctx_new();
    void* sub_context = zmq_ctx_new();
    
    //void* senderSocket = zmq_socket(context, ZMQ_REQ);
    void* recvSocket = zmq_socket(sub_context, ZMQ_SUB);
    
    //char* addres = (char*)malloc(sizeof(char) * 14);
    char* recv_addres = (char*)malloc(sizeof(char) * 14);
    
    //memcpy(addres, "tcp://localhost:", 16);
    //memcpy(addres + 16, argv[1], strlen(argv[1]) + 1);
    
    memcpy(recv_addres, "tcp://localhost:", 16);
    memcpy(recv_addres + 16, argv[1], strlen(argv[1]) + 1);
    printf("addr %s\n", recv_addres);
    //zmq_connect(senderSocket, addres);
    
    zmq_connect(recvSocket,recv_addres);
    zmq_setsockopt(recvSocket, ZMQ_SUBSCRIBE,"",0);
    int i = 10;
    while(i-->0) {
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, recvSocket, 0);
        printf("%s\n", (char*)zmq_msg_data(&message));
        zmq_msg_close(&message);
        zmq_msg_close(&message);
    } 
        
}