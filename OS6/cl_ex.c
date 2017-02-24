//
// Created by mrhacker on 1/13/17.
//

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "zmq.h"
#include "stdbool.h"

#include "time.h"
#include <unistd.h>

typedef struct MD
{
	int clientId;
	int messageNumber;
	char message[128];
} MessageData;

int main(int argc, char const *argv[])
{
	void* context = zmq_ctx_new();
	srand(time(0));
	int clientId = rand();
	printf("Client %d Starting...\n", clientId);

	void* senderSocket = zmq_socket(context, ZMQ_PUSH);
	zmq_connect(senderSocket, "tcp://localhost:2222");
	//zmq_bind(senderSocket, "tcp://*:2222");
    int count = 0;

    /*bool zzz;
    zmq_msg_t new_c;
    zmq_msg_init_size(&new_c, sizeof(bool));
    memcpy(zmq_msg_data(&new_c), &zzz, sizeof(bool));
    printf("Sending signal: - %d\n", count);
    int con = zmq_msg_send(&new_c, senderSocket, 0);
    zmq_msg_close(&new_c);


    zmq_msg_t r;
    zmq_msg_init(&r);
    zmq_msg_recv(&r, senderSocket, 0);
    size_t repSize = zmq_msg_size(&r);
    printf("Received: - %d %s\n", repSize, zmq_msg_data(&r));
    zmq_msg_close(&r);*/


	for (int i = 0; i < 20; ++i)
	{
		//MessageData md;
		//md.clientId = clientId;
		//md.messageNumber = count;
		//memcpy(md.message, "Hello world\0", strlen("Hello world\0")+1);

        int md = 1 + rand() % 100;

        char string[10];
        sprintf(string, "%d", md);
        printf("string = %s\n", string);
		zmq_msg_t zmqMessage;
		zmq_msg_init_size(&zmqMessage, strlen(string) * sizeof(char));
		memcpy(zmq_msg_data(&zmqMessage), &md, strlen(string)*sizeof(char));

		//printf("Sending: - %d num = %s\n", count, md);

		int send = zmq_msg_send(&zmqMessage, senderSocket, 0);
        if (send == -1) {
            perror("send failed");
            return -1;
        }
		else {
            printf("success\n");
        }
		zmq_msg_close(&zmqMessage);

		zmq_msg_t reply;
		zmq_msg_init(&reply);
		zmq_msg_recv(&reply, senderSocket, 0);
		size_t  repSize = zmq_msg_size(&reply);
		printf("Received: - %d %s\n", repSize, zmq_msg_data(&reply));
		zmq_msg_close(&reply);

		usleep(1000);
		count++;
	}
	// We never get here though.
	zmq_close(senderSocket);
	zmq_ctx_destroy(context);

	return 0;
}

