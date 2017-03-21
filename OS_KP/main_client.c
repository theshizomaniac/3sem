#include <string.h>
#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#define MAX_MESSAGE_SIZE 1000
#define MAX_CMD_SIZE 20
#define NAME_SIZE 10

typedef struct MessageData {
    double userId;
    char name[20];
    char command[MAX_CMD_SIZE];
    char message[MAX_MESSAGE_SIZE];
} MessageData;



int main(int argc, char * argv[])
{

    void* context = zmq_ctx_new();
    void* sub_context = zmq_ctx_new();
    
    void* senderSocket = zmq_socket(context, ZMQ_REQ);
    void* recvSocket = zmq_socket(sub_context, ZMQ_SUB);
    
    char* addres = (char*)malloc(sizeof(char) * 14);
    char* recv_addres = (char*)malloc(sizeof(char) * 14);
    
    memcpy(addres, "tcp://localhost:", 16);
    memcpy(addres + 16, argv[1], strlen(argv[1]) + 1);
    
    memcpy(recv_addres, "tcp://localhost:", 16);
    memcpy(recv_addres + 16, argv[2], strlen(argv[2]) + 1);
    
    zmq_connect(senderSocket, addres);
    
    zmq_connect(recvSocket,recv_addres);
    zmq_setsockopt(recvSocket, ZMQ_SUBSCRIBE,"",0);
    
    int i = 10;
    char answer[MAX_MESSAGE_SIZE];
    char name[NAME_SIZE];
    printf("Enter your name: ");
    MessageData * md = (MessageData*) malloc(sizeof(MessageData));

    scanf("%s", name);
    printf("ssssss\n");
    //MessageData md;
    //memcpy(md.name, name, sizeof(name));
    //memcpy(md.message, "hello", sizeof("hello"));
    //md.userId = 1.;
    //printf("> ");
    strcpy(md->name,name);
    strcpy(md->message, "ddd"); 
    while(i-->0) {
        char * a = NULL;
        size_t size;
        printf("----\n");
        //getline(&a,&size,stdin);
        
        //printf("sending -- %s\n", a);
        //printf("\033[A");
        //printf("\33[2K\r");
        //printf("> ");
        //memcpy(md->message,a,strlen(a));
        scanf("%s", md->message);
        zmq_msg_t zmqMessage;
        zmq_msg_init_size(&zmqMessage, sizeof(MessageData));
        memcpy(zmq_msg_data(&zmqMessage), md, sizeof(MessageData));
        zmq_msg_send(&zmqMessage, senderSocket, 0);
        //printf("chck:: %s: %s\n", md->name, md->message);
        /*zmq_msg_t check_message;
        zmq_msg_init(&check_message);
        zmq_msg_recv(&check_message, senderSocket, 0);*/
        /*MessageData * recv = (MessageData*)zmq_msg_data(&message);
        printf("%s: %s", recv->name, recv->message);*/
       
        //printf("server answer:::: %s\n", (char*)zmq_msg_data(&check_message));
        
        
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, recvSocket, 0);
        /*MessageData * recv = (MessageData*)zmq_msg_data(&message);
        printf("%s: %s", recv->name, recv->message);*/
        printf("%s\n", (char*)zmq_msg_data(&message));
         zmq_msg_close(&zmqMessage);
                zmq_msg_close(&message);
               //zmq_msg_close(&check_message);

    } 
        
}
