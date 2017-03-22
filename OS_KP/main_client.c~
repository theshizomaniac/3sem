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

    void* context = zmq_ctx_new();
    void* main_context = zmq_ctx_new();
    //void* sub_context = zmq_ctx_new();
    
    void* senderSocket = zmq_socket(context, ZMQ_REQ);
    void* mainSocket = zmq_socket(context, ZMQ_REQ);
    //void* recvSocket = zmq_socket(sub_context, ZMQ_SUB);
    
    char* main_addres = (char*)malloc(sizeof(char) * 14);
    char* addres = (char*)malloc(sizeof(char) * 14);
    //char* recv_addres = (char*)malloc(sizeof(char) * 14);
    
    memcpy(addres, "tcp://localhost:", 16);
    //memcpy(addres + 16, argv[2], strlen(argv[2]) + 1);
    memcpy(main_addres, "tcp://localhost:", 16);
    memcpy(main_addres + 16, argv[1], strlen(argv[1]) + 1);
    
    //memcpy(recv_addres, "tcp://localhost:", 16);
    //memcpy(recv_addres + 16, argv[2], strlen(argv[2]) + 1);
    
    //zmq_connect(senderSocket, addres);
    zmq_connect(mainSocket, main_addres);
   // zmq_connect(recvSocket,recv_addres);
    //zmq_setsockopt(recvSocket, ZMQ_SUBSCRIBE,"",0);
    
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
    md->userId = atof(argv[3]);
    strcpy(md->name,name);
    strcpy(md->message, "ddd"); 
    while (1) {
        printf("---\n");
        scanf("%s", md->command);
        scanf("%s", md->message);
        zmq_msg_t message;
        zmq_msg_init_size(&message, sizeof(MessageData));
        memcpy(zmq_msg_data(&message), md, sizeof(MessageData));
        zmq_msg_send(&message, mainSocket, 0);
        
        zmq_msg_t server_answer;
        zmq_msg_init(&server_answer);
        zmq_msg_recv(&server_answer, mainSocket, 0);
        char * m_answer = (char*)zmq_msg_data(&server_answer);
        printf("main answer:: %s\n", m_answer); 
        if ((!strcmp(md->command, "chat") || !strcmp(md->command, "check")) && strcmp(m_answer, "no")) {
                //m_answer[strlen(m_answer)-1]++;
                //memcpy(addres + 16, m_answer, strlen(m_answer) + 1);
                //zmq_connect(senderSocket, addres);
                char sub_chat[20]= "./sub_chat ";
                strcat(sub_chat, m_answer);
                printf("arg adress: %s\n", sub_chat);
                m_answer[strlen(m_answer)-1]++;
                memcpy(addres + 16, m_answer, strlen(m_answer) + 1);
                zmq_connect(senderSocket, addres);
                pid_t chat;
                chat = fork();
                if (chat == 0) {
                        execl("/usr/bin/xterm", "xterm", "-e", sub_chat, NULL);
                }
                /* STARTING DIALOG */
                while(1) {
                        
                        printf("----\n");
                        fgets(md->message, MAX_MESSAGE_SIZE, stdin);
                        zmq_msg_t zmqMessage;
                        zmq_msg_init_size(&zmqMessage, sizeof(MessageData));
                        memcpy(zmq_msg_data(&zmqMessage), md, sizeof(MessageData));
                        zmq_msg_send(&zmqMessage, senderSocket, 0);
                        
                        zmq_msg_t check_message;
                        zmq_msg_init(&check_message);
                        zmq_msg_recv(&check_message, senderSocket, 0);
                        printf("server answer:::: %s\n", (char*)zmq_msg_data(&check_message));
       
               }
        }
    } 
        
}
