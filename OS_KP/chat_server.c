#include <string.h>
#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "TVector.h"
#define MAX_STRING_SIZE 255
#define MAX_CMD_SIZE 10
#define BALANCE_WORD_SIZE strlen("Balance: ")
typedef struct MessageData {
    double userId;
    char name[10];
    char command[MAX_CMD_SIZE];
    char message[MAX_STRING_SIZE];
} MessageData;


void * new_dialog(void * arg)
{
        char * adress = (char*) arg;
        printf("sizeof message %d\n", sizeof(MessageData));
        printf("SENDING ADDR: %s\n", adress);
        void* context = zmq_ctx_new();
        void* pub_context= zmq_ctx_new();
        void* chatSocket = zmq_socket(pub_context, ZMQ_PUB);   // SENDING CHAT MESSAGES TO USERS
        void* recvSocket = zmq_socket(context, ZMQ_REP);   // RECEIVING CHAT MESSAGES FROM USERS
        zmq_bind(chatSocket, adress);
        adress[strlen(adress)-1]++;
        zmq_bind(recvSocket, adress);
        printf("RECEVING ADDR: %s\n", adress);
        char answer[MAX_STRING_SIZE];
        int i= 10;
        while(1) {
                zmq_msg_t message;
                zmq_msg_init(&message);
                zmq_msg_recv(&message, recvSocket, 0);
                MessageData* md = (MessageData*)zmq_msg_data(&message);
                
                //memcpy(md->name, "Name", 4);
                //memcpy(md->message, "message", 7);
                printf("RECEIVED: %s: %s\n", md->name, md->message);
                strcat(answer,md->name);
                strcat(answer, ":");
                strcat(answer, md->message);
                //memcpy(answer, md->name, sizeof(md->name));
                //memcpy(answer + sizeof(md->name),
                printf("sending back::::: %s\n",answer);
                
                zmq_msg_t check_reply;
                zmq_msg_init_size(&check_reply, strlen("ok") + 1);
                memcpy(zmq_msg_data(&check_reply), "ok", strlen(answer) + 1);
                zmq_msg_send(&check_reply, recvSocket, 0);
                zmq_msg_close(&check_reply);
                                
                /* SUB REPLY*/
                zmq_msg_t reply;
                zmq_msg_init_size(&reply, strlen(answer) + 1);
                memcpy(zmq_msg_data(&reply), answer, strlen(answer) + 1);

                zmq_msg_send(&reply, chatSocket, 0);
                zmq_msg_close(&reply);
                zmq_msg_close(&message);
                memset(answer, '\0', MAX_STRING_SIZE);
                usleep(1000);
        }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [port]", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);
    if (!port || port > 49151) {
        printf("Error: invalid port!\n");
        return 2;
    }

    void* context = zmq_ctx_new();
    void* serverSocket = zmq_socket(context, ZMQ_REP);
    char* addres = (char*)malloc(sizeof(char) * 14);
    memcpy(addres, "tcp://*:", 8);
    memcpy(addres + 8, argv[1], strlen(argv[1]) + 1);
    zmq_bind(serverSocket, addres);
    printf("Char server %d starting\n", port);
    
    pthread_t chat_thread;
    char * d_address = (char*)malloc(sizeof(char) * 14);
    memcpy(d_address, "tcp://*:", 8);
    memcpy(d_address + 8, argv[2], strlen(argv[2]) + 1);
    //int res = pthread_create(&chat_thread, NULL, new_dialog, (void*)d_address);
    //if (res) {
    //            printf("Error with creating thread\n");
    //            return -1;
   // }
    //pthread_join(chat_thread, (void **) &res);
    //return 0;
    
    TVector* clients = Load(argv[1]);
    char answer[MAX_STRING_SIZE];
    while(1) {
        Save(clients, argv[1]);
        printf("::::\n");
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, serverSocket, 0);
        MessageData* md = (MessageData*)zmq_msg_data(&message);
        zmq_msg_t reply;
    
        if (!strcmp(md->command, "init")) {
            if (!FindId(clients, md->userId)) {
                TElem* elem = NewElem(md->userId, 0);
                Push(clients, elem);
                printf("User %.2lf added\n", md->userId);
                memcpy(answer, "Please sign up!\0", 22);
            }
            else 
                memcpy(answer, "Please sign in\0", 42);
        }
        else {
            TElem* client = FindId(clients, md->userId);
            if (client) {
                if (!strcmp(md->command, "check")) {
		    //char balance[15];
		    //snprintf(balance, sizeof(balance), "%d", client->amount);
                   // memcpy(answer, "Balance: ", 9);
		   // printf("client amount: %d char = %s\n", client->amount, balance);
		    //memcpy(answer + BALANCE_WORD_SIZE, balance, strlen(balance));
		    
                    //_itoa_s(client->amount, answer + 9, MAX_STRING_SIZE - 9, 10);
                 }
                 else if (!strcmp(md->command, "reg")) {
                        memcpy(answer,"testing\0",8);
                }
                else if (!strcmp(md->command, "sign")) {
                    char login[12];
                    char pass[12];
                    int i = 0;
                    while(md->message[i] != ' ') {
                        login[i] = md->message[i];
                    }  
                    int j = i;
                    while(md->message[i] != '\0') {
                    pass[i - j] = md->message[i];
                    }
                    if (!strcmp(login, client->login) && !strcmp(pass, client->pass)) {
                        memcpy(answer, "Success!\0", 9);
                    }
                    else {
                        memcpy(answer, "Try again!\0", 11);
                    }
                }
                else if (!strcmp("chat", md->command)) {
                     printf("starting chat\n");
                     memcpy(answer, "chat", 4);
                     int res = pthread_create(&chat_thread, NULL, new_dialog, (void*)d_address);
                     if (res) {
                        printf("Error with creating thread\n");
                        return -1;
                     }
                     
                }
            }
            else 
                memcpy(answer, "Error: user not found in the database!\0", 41);
        }
        zmq_msg_init_size(&reply, strlen(answer) + 1);
        memcpy(zmq_msg_data(&reply), answer, strlen(answer) + 1);

        zmq_msg_send(&reply, serverSocket, 0);
        zmq_msg_close(&reply);
        zmq_msg_close(&message);
        memset(answer, '\0', MAX_STRING_SIZE);
    }
    CloseHandle(exit);
    zmq_close(serverSocket);
    zmq_ctx_destroy(context);
    Delete(clients);

    return 0;
}
