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
    char name[13];
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
        //printf("sizeof message %d\n", sizeof(MessageData));
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
        int users_num = 0;
        int i= 10;
        while(1) {
                zmq_msg_t message;
                zmq_msg_init(&message);
                zmq_msg_recv(&message, recvSocket, 0);
                MessageData* md = (MessageData*)zmq_msg_data(&message);
                
                strcat(answer,md->name);
                //printf("msg = %s\n", md->message);                
                if(!strcmp(md->message, "/dis\n")) {
                    printf("%s disconnected\n", md->name);
                    strcat(answer, " disconnected.\n");
                    zmq_msg_t reply;
                    zmq_msg_init_size(&reply, strlen(answer) + 1);
                    memcpy(zmq_msg_data(&reply), answer, strlen(answer) + 1);
                    zmq_msg_send(&reply, chatSocket, 0);
                    
                    zmq_msg_t check_reply;
                    zmq_msg_init_size(&check_reply, strlen("dc") + 1);
                    memcpy(zmq_msg_data(&check_reply), "dc", strlen("dc") + 1);
                    zmq_msg_send(&check_reply, recvSocket, 0);
                    zmq_msg_close(&check_reply);
                    users_num--;
                    if (users_num == 0) {
                        printf("Closing chat %s\n", adress);
                        pthread_exit(NULL);
                    }
                }  
                else if (!strcmp(md->message,"\n") && users_num != 2) {
                    printf("%s connected\n", md->name);
                    strcat(answer, " connected.\n");
                    users_num++;
                }
                else {
                   strcat(answer, ": ");      
                   strcat(answer, md->message);                
                } 
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
    starting_chats[0].port = port+1;
    starting_chats[0].is_online = false;
    for (int i = 1; i < MAX_NUM_OF_DIALOGS; ++i) {
        starting_chats[i].port = starting_chats[i - 1].port;
        starting_chats[i].port += 2;
        starting_chats[i].is_online = false;
        //printf("port %d = %d\n", i, starting_chats[i].port);
    }
    TVector* clients = Create();//Load(argv[1]);
    //TVector* clients = (TVector*)malloc(sizeof(TVector));
    int current_free_chat = 0;
    char answer[MAX_STRING_SIZE];
    while(1) {
        //Save(clients, argv[1]);
        
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, serverSocket, 0);
        MessageData* md = (MessageData*)zmq_msg_data(&message);
        zmq_msg_t reply;
        printf("COMMAND: %s\n", md->command);
        printf("MSG:     %s\n\n", md->message);
        
        if (!strcmp(md->command, "/reg")) {
                if (!FindId(clients, md->name)) {
                    TElem* elem = NewElem(md->name, 0);                    
                    memcpy(elem->login, md->message, 13);                    
                    memcpy(elem->pass, md->message+13, 13);                     
                    memcpy(elem->name, md->message+26, 21);                    
                    memcpy(elem->sex, md->message+47, 2);                    
                    memcpy(elem->age, md->message+49, 3);                    
                    memcpy(elem->country, md->message+52, 3);                 
                    elem->online = true;
                    Push(clients, elem);                                                            
                    memcpy(answer,"Profile created!\0",17);                    
                }
                else {
                    memcpy(answer,"Sorry, user with this Id already exist\0",strlen("Sorry, user with this Id already exist\0") +1);   
                }
         }
         else {
            //printf("md name %s\n", md->name);
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
                    //printf("msg = %s\n", md->message);
                    char s_login[12];
                    char s_pass[12];
                    int i = 0;
                    memcpy(s_login, strtok (md->message, " "), 12);
                    memcpy(s_pass, strtok (NULL, " "), 12);
                    
                    //printf("login = %s, pass = %s\n", s_login, s_pass);
                    if (!strcmp(s_login, client->login) && !strcmp(s_pass, client->pass)) {
                        memcpy(answer, "Success!\0", 9);
                    }
                    else {
                        memcpy(answer, "Try again!\0", 11);
                    }
                    client->online = true;
                }
                
                else if (!strcmp("/chat", md->command)) {
                     printf("starting chat\n");
                     //chat_number++;
                     current_free_chat = -1;
                     char char_port[6];
                     for (int i = 0; i < MAX_NUM_OF_DIALOGS; ++i) {
                        if(starting_chats[i].is_online == false) {
                            current_free_chat = i;
                            break;
                        }
                     }
                     if (current_free_chat == -1) {
                         memcpy(answer, "no",2);
                         continue; 
                     }
                     else {
                     snprintf(char_port, sizeof(char_port), "%d", starting_chats[current_free_chat].port);
                     memcpy(starting_chats[current_free_chat].reqId, md->name,12);
                     memcpy(starting_chats[current_free_chat].sleepingId, md->message,12);
                     //printf("name = %s slep = %s\n", starting_chats[current_free_chat].reqId,starting_chats[current_free_chat].sleepingId);
                     starting_chats[current_free_chat].is_online = true;
                     memcpy(answer, char_port, 6);
                     
                     char * d_address = (char*)malloc(sizeof(char) * 14);      // CHAT ADDR CHAR
                     memcpy(d_address, "tcp://*:", 8);                           // CHAT ADDR
                     memcpy(d_address + 8, char_port, strlen(char_port) + 1);    // CHAT PORT
                     
                     int res = pthread_create(&chat_thread, NULL, new_dialog, (void*)d_address);
                     if (res) {
                        printf("Error with creating thread\n");
                        memcpy(answer, "Room creation failed!", 14);
                        //return -1;
                     }
                     }
                     
                }
                else if (!strcmp("/dc", md->command)) {
                printf("dc prot: %s\n", md->message);
                    for (int i = 0; i < MAX_NUM_OF_DIALOGS; ++i) {
                        if(starting_chats[i].port == atoi(md->message)) {
                            starting_chats[i].is_online = false;
                            current_free_chat = i;
                            memcpy(answer, "Disconnected", 14);
                            break;
                        }
                    }
                }
                else if (!strcmp("/rooms", md->command)) {
                for (int i = 0; i < MAX_NUM_OF_DIALOGS; ++i) {
                        printf("chat %d ", starting_chats[i].port);
                        if(starting_chats[i].is_online == true) {
                            printf("online\n");
                            
                        }
                        else printf("\n");
                     }
                }
                else if (!strcmp("/exit", md->command)) {
                    client->online = false;
                    memcpy(answer, "Bye!", 4);
                }
                else if (!strcmp("/findage", md->command)) {
                    int *j;
                    int i = 0;
                    j = &i;
                    TElem* res;
                    while (i < clients->size) {
                        res = FindAge(clients, md->message, j);
                        if (res) {
                           strcat(answer,"\nId: ");
                           strcat(answer, res->login);
                           strcat(answer,"\nName: ");
                           strcat(answer, res->name);
                           strcat(answer,"\nAge: ");
                           strcat(answer, res->age);
                           strcat(answer,"\nSex: ");
                           strcat(answer, res->sex);  
                           strcat(answer,"\nCountry: ");
                           strcat(answer, res->country); 
                        }
                    }
                    if (!res) {
                       memcpy(answer, "0 users found.", 15);
                    }
                }
                else if (!strcmp("/findname", md->command)) {
                    int *j;
                    int i = 0;
                    j = &i;
                    TElem* res;
                    while (i < clients->size) {
                        printf("it\n");
                        res = FindName(clients, md->message, j);
                    
                        if (res) {
                           strcat(answer,"\nId: ");
                           strcat(answer, res->login);
                           strcat(answer,"\nName: ");
                           strcat(answer, res->name);
                           strcat(answer,"\nAge: ");
                           strcat(answer, res->age);
                           strcat(answer,"\nSex: ");
                           strcat(answer, res->sex);  
                           strcat(answer,"\nCountry: ");
                           strcat(answer, res->country); 
                        }
                    }
                    if(!res) {
                       memcpy(answer, "0 users found.", 15);
                    }
                }
                else if (!strcmp("/findsex", md->command)) {
                    int *j;
                    int i = 0;
                    j = &i;
                    TElem* res;
                    while (i < clients->size) {
                        res = FindSex(clients, md->message, j);
                        if (res) {
                           strcat(answer,"\nId: ");
                           strcat(answer, res->login);
                           strcat(answer,"\nName: ");
                           strcat(answer, res->name);
                           strcat(answer,"\nAge: ");
                           strcat(answer, res->age);
                           strcat(answer,"\nSex: ");
                           strcat(answer, res->sex);  
                           strcat(answer,"\nCountry: ");
                           strcat(answer, res->country); 
                        }
                    }
                    if (!res) {
                       memcpy(answer, "0 users found.", 15);
                    }
                }
                 else if (!strcmp("/findcn", md->command)) {
                    int *j;
                    int i = 0;
                    j = &i;
                    TElem* res;
                    while (i < clients->size) {
                        res = FindCountry(clients, md->message, j);
                        if (res) {
                           strcat(answer,"\nId: "); strcat(answer, res->login);
                           strcat(answer,"\nName: "); strcat(answer, res->name);
                           strcat(answer,"\nAge: "); strcat(answer, res->age);
                           strcat(answer,"\nSex: "); strcat(answer, res->sex);  
                           strcat(answer,"\nCountry: "); strcat(answer, res->country); 
                        }
                    }
                    if (!res) {
                       memcpy(answer, "0 users found.", 15);
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
