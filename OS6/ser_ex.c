//
// Created by mrhacker on 1/13/17.
//

#include <string.h>
#include <stdio.h>
#include "zmq.h"
#include <unistd.h>
#include "TVector.h"
#include <errno.h>
#include <pthread.h>
#include "stdbool.h"


typedef struct MD
{
	int clientId;
	int messageNumber;
	char message[128];
} MessageData;

typedef struct {
    void* context;
    void* serverSocket;
} server_data;

int thread_num =0;


void * working_with_client (void * arg)
{
    server_data * server = arg;
    void * serverSocket = server->serverSocket;
    void * context = server->context;
    zmq_bind(serverSocket, "tcp://*:4040");
    int i = 20;
    while (i-->0) {

        zmq_msg_t message;
        zmq_msg_init(&message);

        zmq_msg_recv(&message, serverSocket, 0);
        MessageData *m = (MessageData *) zmq_msg_data(&message);

        printf("------------------\n");
        printf("Message from client: %d  messageId: %d message: %s\n", m->clientId, m->messageNumber, m->message);
        zmq_msg_close(&message);
        sleep(5);
        zmq_msg_t reply;
        zmq_msg_init_size(&reply, strlen("ok") + 1);
        memcpy(zmq_msg_data(&reply), "ok\0", 3);
        zmq_msg_send(&reply, serverSocket, 0);
        zmq_msg_close(&reply);
        printf("in da thread %d\n", ++thread_num);
    }
    pthread_exit((void*)arg);

}

int main(int argc, char const *argv[])
{
    server_data server;
	server.context = zmq_ctx_new();
	server.serverSocket = zmq_socket(server.context, ZMQ_REP);
	zmq_bind(server.serverSocket, "tcp://*:4040");
	printf("Starting...\n");
    TVector * vector = Init();
    int threadsNum = 10;
    pthread_t threads[threadsNum];
	for (int i = 0; i < threadsNum; ++i)
	{
		/*zmq_msg_t message;
		zmq_msg_init(&message);
		zmq_msg_recv(&message, server.serverSocket, 0);
		MessageData *m = (MessageData *)zmq_msg_data(&message);
		printf("Message from client: %d  messageId: %d message: %s\n", m->clientId, m->messageNumber, m->message);
		zmq_msg_close(&message);*/

        /*zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, server.serverSocket, 0);
        bool new_connection = (bool) zmq_msg_data(&message);
        printf("New client!");
        zmq_msg_close(&message);
        zmq_msg_t reply;
        zmq_msg_init_size(&reply, strlen("od")+1);
        memcpy(zmq_msg_data(&reply), "od\0", 3);
        zmq_msg_send(&reply, server.serverSocket, 0);
        zmq_msg_close(&reply);*/

        int res = pthread_create(&threads[i], NULL, working_with_client, &server);
        if (res) {
            printf("Error with creating thread\n");
            return -1;
        }
        //pthread_join(thread, (void **) &res);


		/*zmq_msg_t reply;
		zmq_msg_init_size(&reply, strlen("ok")+1);
		memcpy(zmq_msg_data(&reply), "ok\0", 3);
		zmq_msg_send(&reply, server.serverSocket, 0);
		zmq_msg_close(&reply);*/
	}
	zmq_close(server.serverSocket);
	zmq_ctx_destroy(server.context);

	return 0;
}