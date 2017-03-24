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
    
    void* sub_context = zmq_ctx_new();
    void* recvSocket = zmq_socket(sub_context, ZMQ_SUB);
    char* recv_addres = (char*)malloc(sizeof(char) * 14);
    
    memcpy(recv_addres, "tcp://localhost:", 16);
    memcpy(recv_addres + 16, argv[1], strlen(argv[1]) + 1); 
    
    zmq_connect(recvSocket,recv_addres);
    zmq_setsockopt(recvSocket, ZMQ_SUBSCRIBE,"",0);
    int i = 10;
    while(1) {
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, recvSocket, 0);
        if (!strcmp((char*)zmq_msg_data(&message), "/exit")) {
                exit(0);
        }
        printf("%s", (char*)zmq_msg_data(&message));
        zmq_msg_close(&message);
        zmq_msg_close(&message);
    } 
        
}
