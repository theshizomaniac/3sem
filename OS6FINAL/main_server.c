#include <string.h>
#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include "TVector.h"
#define MAX_STRING_SIZE 128
#define BALANCE_WORD_SIZE strlen("Balance: ")
typedef struct MessageData {
    double clientId;
    double transId;
    int ammount;
    char command[MAX_STRING_SIZE];
} MessageData;

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
    printf("Bank %d starting\n", port);

    TVector* clients = Load(argv[1]);
    char answer[MAX_STRING_SIZE];
    while(1) {
        Save(clients, argv[1]);
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, serverSocket, 0);
        MessageData* md = (MessageData*)zmq_msg_data(&message);
        zmq_msg_t reply;
    
        if (!strcmp(md->command, "init")) {
            if (!FindId(clients, md->clientId)) {
                TElem* elem = NewElem(md->clientId, 0);
                Push(clients, elem);
                printf("Client %.2lf added\n", md->clientId);
                memcpy(answer, "ok\0", 3);
            }
            else 
                memcpy(answer, "Error: client allready exist in the bank!\0", 42);
        }
        else {
            TElem* client = FindId(clients, md->clientId);
            if (client) {
                if (!strcmp(md->command, "check")) {
		    char balance[15];
		    snprintf(balance, sizeof(balance), "%d", client->amount);
                    memcpy(answer, "Balance: ", 9);
		    printf("client amount: %d char = %s\n", client->amount, balance);
		    memcpy(answer + BALANCE_WORD_SIZE, balance, strlen(balance));
		    
                    //_itoa_s(client->amount, answer + 9, MAX_STRING_SIZE - 9, 10);
                }
                if (!strcmp(md->command, "cr_check")) {
		    char balance[15];
		    snprintf(balance, sizeof(balance), "%d", client->credit);
                    memcpy(answer, "Credit account balance: ", strlen("Credit account balance: "));
		    printf("client credit: %d char = %s\n", client->amount, balance);
		    memcpy(answer + strlen("Credit account balance: "), balance, strlen(balance));
		    
                    //_itoa_s(client->amount, answer + 9, MAX_STRING_SIZE - 9, 10);
                }
                else if (!strcmp(md->command, "deposit")) {
                    client->amount += md->ammount;
                    char balance[15];
		    snprintf(balance, sizeof(balance), "%d", client->amount);
                    memcpy(answer, "Balance: ", 9);
		    printf("client amount: %d\n", client->amount);
		    memcpy(answer + BALANCE_WORD_SIZE, balance, strlen(balance));
                    //_itoa_s(client->amount, answer + 9, MAX_STRING_SIZE - 9, 10);
                }
                else if (!strcmp(md->command, "withdraw")) {
                    if (md->ammount > client->amount) {
                        memcpy(answer, "Taking cash from credit account!\n", strlen("Taking cash from credit account!\n"));
                        client->amount -= md->ammount;
                        client->credit += client->amount;
                        client->amount = 0;
                        char balance[15];
                        char credit_balance[50];
                        memcpy(credit_balance, "Credit account balance: ", strlen("Credit account balance: "));
		        snprintf(balance, sizeof(balance), "%d", client->amount);
		        snprintf(credit_balance + sizeof("Credit account balance: "), sizeof(credit_balance), "%d", client->credit);
		  
                        memcpy(answer + strlen("Taking cash from credit account!\n"), balance, strlen(balance));
                        memcpy(answer + strlen("Taking cash from credit account!\n") + sizeof("Credit account balance: ") + sizeof(credit_balance), credit_balance, strlen(credit_balance));
                        }
                    else {
                        client->amount -= md->ammount;
                        char balance[15];
		        snprintf(balance, sizeof(balance), "%d", client->amount);
		        memcpy(answer, "Balance: ", 9);
		        printf("client amount: %d\n", client->amount);
		        memcpy(answer + BALANCE_WORD_SIZE, balance, strlen(balance));
                        //_itoa_s(client->amount, answer + 9, MAX_STRING_SIZE - 9, 10);
                    }
                }
                else if (!strcmp(md->command, "cr_deposit")) {
                    client->credit += md->ammount;
                    char balance[15];
		    snprintf(balance, sizeof(balance), "%d", client->credit);
                    memcpy(answer, "Credit account balance: ", strlen("Credit account balance: "));
		    printf("client amount: %d\n", client->amount);
		    memcpy(answer + strlen("Credit account balance: "), balance, strlen(balance));
                    
                }
                else if (!strcmp(md->command, "cr_withdraw")) {
                        client->credit -= md->ammount;
                       
                        char balance[15];
		        snprintf(balance, sizeof(balance), "%d", client->credit);
		        memcpy(answer, "Credit account balance: ", strlen("Credit account balance"));
		        printf("client amount: %d\n", client->amount);
		        memcpy(answer + strlen("Credit account balance"), balance, strlen(balance));
                }
                else if (!strcmp(md->command, "exit")) {
                    RemoveElem(clients, md->clientId);
                    memcpy(answer, "Good bye!\0", 10);
                    printf("Client %.2lf deleted\n", md->clientId);
                }
            }
            else 
                memcpy(answer, "Error: client not found in the bank!\0", 37);
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
