#include <string.h>
#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <math.h>
#define MAX_STRING_SIZE 128
#define EPS 0.000001

typedef struct MessageData {
    //double clientId;
    //double transId;
    char clientId[20];
    char transId[20];
    int ammount;
    char command[MAX_STRING_SIZE];
} MessageData;

void PrintHelp() {
    printf("Usage:\n\
help                        -- print help\n\
check                       -- check balance\n\
transfer [ammount] [id]     -- send the money to the client id\n\
cr_check                    -- check credit acc balance\n\
deposit [ammount]           -- put money on the account\n\
withdraw [ammount]          -- get money from the account\n\
cr_deposit [ammount]        -- put money on credit account\n\
cr_withdraw [ammount]       -- get money from credit account\n\
exit                        -- exit program\n");
}

void SendCommand(MessageData* md, void* senderSocket) {
    zmq_msg_t reply;
    zmq_msg_init(&reply);

    zmq_msg_t zmqMessage;
    zmq_msg_init_size(&zmqMessage, sizeof(MessageData));

    memcpy(zmq_msg_data(&zmqMessage), md, sizeof(MessageData));
    zmq_msg_send(&zmqMessage, senderSocket, 0);
    zmq_msg_recv(&reply, senderSocket, 0);
    printf("%s\n", (char*)zmq_msg_data(&reply));
    zmq_msg_close(&zmqMessage);
    zmq_msg_close(&reply);
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [port] [client id]", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    //double id = atof(argv[2]);
    char id[20];
    memcpy(id, argv[2], strlen (argv[2]) + 1);
    printf("Init id = %s\n", id);
    if (!port || port > 49151) {
        printf("Error: invalid port!\n");
        return 2;
    }

    void* context = zmq_ctx_new();
    void* senderSocket = zmq_socket(context, ZMQ_REQ);
    char* addres = (char*)malloc(sizeof(char) * 24);
    memcpy(addres, "tcp://localhost:", 16);
    memcpy(addres + 16, argv[1], strlen(argv[1]) + 1);
    zmq_connect(senderSocket, addres);

    MessageData init;
    //init.clientId = id;
    memset(init.clientId, '\0', 20);
    memcpy(init.clientId, id, 20);
    memcpy(init.command, "init\0", 5);

    zmq_msg_t initMessage;
    zmq_msg_init_size(&initMessage, sizeof(MessageData));
    memcpy(zmq_msg_data(&initMessage), &init, sizeof(MessageData));
    zmq_msg_send(&initMessage, senderSocket, 0);
    zmq_msg_close(&initMessage);

    zmq_msg_t reply;
    zmq_msg_init(&reply);
    zmq_msg_recv(&reply, senderSocket, 0);
    if(!strcmp((char*)zmq_msg_data(&reply), "ok"))
        printf("The client (%s) is initialized on the bank(%d)\n", id, port);
    else 
        printf("%s\n", (char*)zmq_msg_data(&reply));
    zmq_msg_close(&reply);

    char command[MAX_STRING_SIZE];
    int active = 1, stat;
    PrintHelp();
    while (active) {
        printf("Enter the command: ");
        //stat = scanf_s("%s", command, (unsigned)_countof(command));
        stat = scanf("%s", command);
	if (!stat) {
            //scanf_s("%*s");
            continue;
        }
        MessageData md;
        memset(md.clientId, '\0', 20);
        //md.clientId = id;
        memcpy(md.clientId, id, 20);
        if (!strcmp(command, "help"))
            PrintHelp();
        else if (!strcmp(command, "check")) {
            memcpy(md.command, command, strlen(command) + 1);
            SendCommand(&md, senderSocket);
        }
        else if (!strcmp(command, "cr_check")) {
            memcpy(md.command, command, strlen(command) + 1);
            SendCommand(&md, senderSocket);
        }
        else if (!strcmp(command, "deposit")) {
            scanf("%d", &md.ammount);
            if (md.ammount < 0) {
                printf("Error: invalid ammount!\n");
                continue;
            }
            memcpy(md.command, command, strlen(command) + 1);
            SendCommand(&md, senderSocket);
        }
        else if (!strcmp(command, "withdraw")) {
            scanf("%d", &md.ammount);
            if (md.ammount < 0) {
                printf("Error: invalid ammount!\n");
                continue;
            }
            memcpy(md.command, command, strlen(command) + 1);
            SendCommand(&md, senderSocket);
        }
        else if (!strcmp(command, "cr_deposit")) {
            scanf("%d", &md.ammount);
            if (md.ammount < 0) {
                printf("Error: invalid ammount!\n");
                continue;
            }
            memcpy(md.command, command, strlen(command) + 1);
            SendCommand(&md, senderSocket);
          
        }
        else if (!strcmp(command, "cr_withdraw")) {
            scanf("%d", &md.ammount);
            if (md.ammount < 0) {
                printf("Error: invalid ammount!\n");
                continue;
            }
            memcpy(md.command, command, strlen(command) + 1);
            SendCommand(&md, senderSocket);
           }
           else if (!strcmp(command, "transfer")) {
             scanf("%d", &md.ammount);
             if (md.ammount < 0) {
                 printf("Error: invalid ammount!\n");
                 continue;
             }
             //scanf("%lf", &md.transId);
             scanf("%s", md.transId);
             /*if (md.transId < 0 || fabs(md.transId - md.clientId) < EPS) {
                 printf("Error: invalid id!\n");
                 continue;
             }*/
             memcpy(md.command, command, strlen(command) + 1);
             SendCommand(&md, senderSocket);
        }
        else if (!strcmp(command, "exit")) {
            memcpy(md.command, command, strlen(command) + 1);
            SendCommand(&md, senderSocket);
            active = 0;
        }
        else
            printf("Error: invalid command!\n");
    }
    zmq_close(senderSocket);
    zmq_ctx_destroy(context);
    return 0;
}
