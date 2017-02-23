//
// Created by mrhacker on 1/14/17.
//

#include <stdlib.h>
#include <string.h>
#include "zmq.h"
int main (int argc, char const *argv[])
{
	void* context = zmq_ctx_new();
	void* receiver = zmq_socket(context, ZMQ_PULL);
	zmq_bind(receiver, "tcp://*:5050");
	// We receive the first message and discard it since it's the
	// signal start of batch which is -1.
	zmq_msg_t reply;
	zmq_msg_init(&reply);
	zmq_msg_recv(&reply, receiver, 0);
	int length = zmq_msg_size(&reply);
	char* msg = malloc(length + 1);
	memcpy(msg, zmq_msg_data(&reply), length);
    printf("%s = %s\n", "first msg", msg);
	zmq_msg_close(&reply);
	free(msg);
	int count;
    printf("%s\n", "Collector!");
	for(;;)
	{
		zmq_msg_t reply;
		zmq_msg_init(&reply);
		zmq_msg_recv(&reply, receiver, 0);
		int length = zmq_msg_size(&reply);
		char* value = malloc(length + 1);
		memcpy(value, zmq_msg_data(&reply), length);
		zmq_msg_close(&reply);
        printf("val = %s\n", value);
		free(value);
		if(count / 10 == 0)
			printf("10 Tasks have been processed.");
		fflush(stdout);
	}
    /* ------------*/
    /*printf("sending back...\n");
    void* sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:2020");
    char * string = "hello\n";
    zmq_msg_init_size(&message, strlen(string));
    memcpy(zmq_msg_data(&message), string, strlen(string));
    zmq_msg_send(&message, sender, 0);
    zmq_msg_close(&message);*/
	zmq_close(receiver);
	zmq_ctx_destroy(context);
	return 0;
}