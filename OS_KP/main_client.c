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

void Help() 
{
    printf("Useful commands (type /help)\n");
    printf("    /chat [user login]  -- start chat with [user]\n");
}

void SendCommand(MessageData* md, void* senderSocket, char * answer) {
    memset(answer, '\0', MAX_MESSAGE_SIZE);
    zmq_msg_t reply;
    zmq_msg_init(&reply);

    zmq_msg_t zmqMessage;
    zmq_msg_init_size(&zmqMessage, sizeof(MessageData));

    memcpy(zmq_msg_data(&zmqMessage), md, sizeof(MessageData));
    zmq_msg_send(&zmqMessage, senderSocket, 0);
    zmq_msg_recv(&reply, senderSocket, 0);
    memcpy(answer, (char*)zmq_msg_data(&reply), MAX_MESSAGE_SIZE);
    zmq_msg_close(&zmqMessage);
    zmq_msg_close(&reply);
}


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
    memcpy(main_addres, "tcp://localhost:", 16);
    memcpy(main_addres + 16, argv[1], strlen(argv[1]) + 1);
   
    zmq_connect(mainSocket, main_addres);
    
    int i = 10;
    char answer[MAX_MESSAGE_SIZE];
    char name[NAME_SIZE];
    //printf("Enter your name: ");
    MessageData * md = (MessageData*) malloc(sizeof(MessageData));

     //scanf("%s", name);
     //md->userId = atof(argv[3]);
     //strcpy(md->name,name);
     //strcpy(md->command, "/init"); 
    
    /* INIT PART*/
     
     char * c_answer = (char*) malloc(sizeof(char) * MAX_MESSAGE_SIZE);
     //SendCommand(md, mainSocket, c_answer);
     //printf("%s\n", c_answer);
     while (1) {
     printf("1) Sign In\n2) Sign up\n3) Exit\n");
     int choice;
     scanf("%d", &choice);
     if (2 == choice) {
        memset(md->message, '\0', MAX_MESSAGE_SIZE);
        printf("|--Creating new profile--|\n");
        char field[20];
        strcpy(md->command, "/reg"); 
        
        printf("Login (12): ");
        scanf("%s", name);
        strcpy(md->name,name); 
        printf("md--- %s\n", md->name);
       
        strcat(md->message, name);
        strcat(md->message, " ");
        
        printf("Pass (12): ");
        scanf("%s", field);
        
        strcat(md->message, field);
        strcat(md->message, " ");
        
        printf("Name (20): ");
        scanf("%s", field);
        
        strcat(md->message, field);
        strcat(md->message, " ");
        
        printf("Sex (M/F): ");
        scanf("%s", field);
        
        strcat(md->message, field);
        strcat(md->message, " ");
        
        printf("Age: ");
        scanf("%s", field);
        
        strcat(md->message, field);
        strcat(md->message, " ");
        
        printf("Country (2): "); 
        scanf("%s", field);
        
        strcat(md->message, field);
        
        strcpy(md->name,name);       
        
        printf("reg test: %s\n", md->message);
        SendCommand(md, mainSocket, c_answer);
        printf("%s\n", c_answer);
        if(!strcmp(c_answer, "Profile created!")) {
            break;
        }
     }
     else if (1 == choice) {
        memset(md->message, '\0', MAX_MESSAGE_SIZE);
        //memset(md->name, '\0', MAX_MESSAGE_SIZE);
        char login[12];
        char pass[12];
        
        strcpy(md->command, "/sign"); 
        printf("Login (12): ");
        scanf("%s", name);
        printf("%s\n", name);
        strcpy(md->name,name); 
        printf("Pass (12) : ");
        scanf("%s", pass);
        strcat(md->message, name);
        strcat(md->message, " ");
        strcat(md->message, pass);
        SendCommand(md, mainSocket, c_answer);
        printf("%s\n", c_answer);
        if(!strcmp(c_answer, "Success!")) {
            break;
        }
        else {
            
        }
     }
     else if (3 == choice) {
        return 0;
     }
     }
    Help();
    printf("zzz %s\n", name);
    strcpy(md->name, name);
    printf("zzz %s\n", md->name);
    while (1) {
        printf("> ");
        scanf("%s", md->command);
        if (!strcmp(md->command,"/chat")) {
            //fgets(md->message, MAX_MESSAGE_SIZE, stdin);
            scanf("%s", md->message);
        }
        else if (!strcmp(md->command,"/exit")) {
            return 0;
        }
        SendCommand(md,mainSocket, c_answer);
        
        printf(":: %s\n", c_answer); 
        if ((!strcmp(md->command, "/chat") || !strcmp(md->command, "/check")) && strcmp(c_answer, "no")) {
                char sub_chat[20]= "./sub_chat ";
                strcat(sub_chat, c_answer);
                printf("arg adress: %s\n", sub_chat);
                c_answer[strlen(c_answer)-1]++;
                memcpy(addres + 16, c_answer, strlen(c_answer) + 1);
                zmq_connect(senderSocket, addres);
                pid_t chat;
                chat = fork();
                if (chat == 0) {
                        //sleep(5);   
                        execl("/usr/bin/xterm", "xterm", "-e", sub_chat, NULL);
                }
                /* STARTING DIALOG */
                while(1) {
                        memset(md->message, '\0', MAX_MESSAGE_SIZE);
                        printf(">> ");
                        fgets(md->message, MAX_MESSAGE_SIZE, stdin);
                        SendCommand(md, senderSocket, c_answer);
                        if (!strcmp("dc", c_answer)) {
                            break;
                        }
                               
               }
        }
    } 
        
}
