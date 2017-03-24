#include <string.h>
#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "TVector.h"
#include <stdbool.h>
#include <stddef.h>
#define _GNU_SOURCE

#define MAX_STRING_SIZE 255
#define MAX_CMD_SIZE 10
#define MAX_NUM_OF_DIALOGS 10
typedef struct MessageData {
    double userId;
    char name[10];
    char command[MAX_CMD_SIZE];
    char message[MAX_STRING_SIZE];
} MessageData;

typedef struct WaitingRoom {
    char reqId[12];
    char sleepingId[12];
    //char port[5];
    int port;
    bool is_online;
} WaitingRoom;

typedef struct PortUsage {
    char port[6];
    bool used;
} PortUsage;

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
                
                strcat(answer,md->name);
                printf("msg = %s\n", md->message);                
                if(!strcmp(md->message, "/dis")) {
                printf("ddd");
                    strcat(answer, "disconnected.");
                    zmq_msg_t reply;
                    zmq_msg_init_size(&reply, strlen(answer) + 1);
                    memcpy(zmq_msg_data(&reply), answer, strlen(answer) + 1);
                    zmq_msg_send(&reply, chatSocket, 0);
                    
                    zmq_msg_t check_reply;
                    zmq_msg_init_size(&check_reply, strlen("dc") + 1);
                    memcpy(zmq_msg_data(&check_reply), "dc", strlen("dc") + 1);
                    zmq_msg_send(&check_reply, recvSocket, 0);
                    zmq_msg_close(&check_reply);
                    pthread_exit(NULL);
                }  
                strcat(answer, ": ");      
                strcat(answer, md->message);                
                 
                zmq_msg_t check_reply;
                zmq_msg_init_size(&check_reply, strlen("ok") + 1);
                memcpy(zmq_msg_data(&check_reply), "ok", strlen("ok") + 1);
                zmq_msg_send(&check_reply, recvSocket, 0);
                zmq_msg_close(&check_reply);
                
                     
                
                
                /* SUB REPLY*/
                zmq_msg_t reply;
                zmq_msg_init_size(&reply, strlen(answer) + 1);
                memcpy(zmq_msg_data(&reply), answer, strlen(answer) + 1);
                //printf("size = %d\n", sizeof(reply));
                zmq_msg_send(&reply, chatSocket, 0);
                //zmq_send(chatSocket, &reply,strlen(answer),0);
                zmq_msg_close(&reply);
                zmq_msg_close(&message);
                memset(answer, '\0', MAX_STRING_SIZE);
                
        }
        zmq_close(recvSocket);
        zmq_ctx_destroy(context);
        zmq_close(chatSocket);
        zmq_ctx_destroy(pub_context);
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
    
    WaitingRoom * starting_chats = (WaitingRoom*) malloc(sizeof(WaitingRoom) * MAX_NUM_OF_DIALOGS);
    starting_chats[0].port = port;
    for (int i = 1; i < MAX_NUM_OF_DIALOGS; ++i) {
        starting_chats[i].port = starting_chats[i - 1].port;
        starting_chats[i].port += 2;
        //printf("port %d = %d\n", i, starting_chats[i].port);
    }
    TVector* clients = Load(argv[1]);
    int current_free_chat = 0;
    char answer[MAX_STRING_SIZE];
    while(1) {
        Save(clients, argv[1]);
        printf(":: new msg\n");
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, serverSocket, 0);
        MessageData* md = (MessageData*)zmq_msg_data(&message);
        zmq_msg_t reply;
    
        if (!strcmp(md->command, "/reg")) {
                    //char buf[] ="abc/qwe/ccd";
                    //int i = 0;
                    TElem* elem = NewElem(md->name, 0);
                    
                    memcpy(elem->login, strtok (md->message, " "), 12);
                    memcpy(elem->pass, strtok (NULL, " "), 12);
                    memcpy(elem->name, strtok (NULL, " "), 20);
                    memcpy(elem->sex, strtok (NULL, " "), 1);
                    memcpy(elem->age, strtok (NULL, " "), 2);
                    memcpy(elem->country, strtok (NULL, " "), 2);
                    Push(clients, elem);
                    printf("== %s == %s\n", elem->login, elem->pass);  
                    
                    memcpy(answer,"Profile created!\0",17);
                }
                
         else {
            printf("md name %s\n", md->name);
            TElem* client = FindId(clients, md->name);
            if (client) {
                if (!strcmp(md->command, "/check")) {
                    memcpy(answer, "no", 2);
	            for (int i = 0; i < MAX_NUM_OF_DIALOGS; i++) {
	                if(!strcmp(md->name, starting_chats[i].sleepingId)) {
	                    char char_port[6];
                            snprintf(char_port, sizeof(char_port), "%d", starting_chats[i].port);
		            memcpy(answer, char_port, strlen(char_port)+1); 
		        }
		    }
                }
                else if (!strcmp(md->command, "/sign")) {
                    printf("msg = %s\n", md->message);
                    char s_login[12];
                    char s_pass[12];
                    int i = 0;
                    memcpy(s_login, strtok (md->message, " "), 12);
                    memcpy(s_pass, strtok (NULL, " "), 12);
                    /*while(md->message[i] != ' ') {
                        login[i] = md->message[i];
                        i++;
                    }  
                    int j = ++i;
                    while(md->message[i] != '\0') {
                        pass[i - j] = md->message[i];
                        i++;
                    }*/
                    printf("login = %s, pass = %s\n", s_login, s_pass);
                    if (!strcmp(s_login, client->login) && !strcmp(s_pass, client->pass)) {
                        memcpy(answer, "Success!\0", 9);
                    }
                    else {
                        memcpy(answer, "Try again!\0", 11);
                    }
                }
                
                else if (!strcmp("/chat", md->command)) {
                     printf("starting chat\n");
                     //chat_number++;
                     current_free_chat++;
                     char char_port[6];
                     snprintf(char_port, sizeof(char_port), "%d", starting_chats[current_free_chat].port);
                     memcpy(starting_chats[current_free_chat].reqId, md->name,12);
                     memcpy(starting_chats[current_free_chat].sleepingId, md->message,12);
                     printf("name = %s slep = %s\n", starting_chats[current_free_chat].reqId,starting_chats[current_free_chat].sleepingId);
                     starting_chats[current_free_chat].is_online = true;
                     //memcpy(starting_chats[chat_number].port, x.port ,strlen(x.port) + 1);
                     //memcpy(answer, x.port, 5);            //, strlen(x->port));
                     memcpy(answer, char_port, 6);
                     
                     char * d_address = (char*)malloc(sizeof(char) * 14);      // CHAT ADDR CHAR
                     memcpy(d_address, "tcp://*:", 8);                           // CHAT ADDR
                     memcpy(d_address + 8, char_port, strlen(char_port) + 1);           // CHAT PORT
                     
                     int res = pthread_create(&chat_thread, NULL, new_dialog, (void*)d_address);
                     if (res) {
                        printf("Error with creating thread\n");
                        return -1;
                     }
                     
                }
                else if (!strcmp("/exit", md->command)) {
                    client->online = false;
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
