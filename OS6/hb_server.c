//
// Created by mrhacker on 1/14/17.
//
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <time.h>

#include "semaphore.h"
#include "zmq.h"
//#include "unpipc.h"
#define SNAME "/mysem"
#define SHMSIZE 100
#define WORKERS_NUM 2

int main (int argc, char const *argv[])
{

    int shmid;
    char *shm = NULL;

    shmid = shmget(2009, SHMSIZE * sizeof(char), IPC_CREAT|0666);
    if (shmid == -1) {
        printf("error\n");
    }
    shm = shmat(shmid, (char*)0, 0);
    if (shm == (void *)-1)
    {
        perror("shmat : Failed");
        return 3;
    }
    char * s = NULL;// = (char *) shm;
    int i;
    sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 3); /* Initial value is 3. */
    for(i=0; i<5; i++) {
        char n;  // Variable to get the number into
        printf("Enter number<%i>: ", i);
        n = getchar();
        //shm[i] = n;
        shm[i] = n;
        //sprintf(s, "%s%d", *s, n);  // Append number to string
    }
    //strcat(s, "\n");  // Append newline */
    printf("aaa\n");
    printf ("Server wrote <%s>\n",shm);
    //shmdt(shm);


	void* context = zmq_ctx_new();
    void * ttt = zmq_ctx_new();
	// This is the socket that we send messages.
	void* socket = zmq_socket(context, ZMQ_PUSH);
	zmq_bind(socket, "tcp://*:4040");
	// This is the socket that we send batch message.
	void* connector = zmq_socket(context, ZMQ_PUSH);
	zmq_connect(connector, "tcp://localhost:5050");
    void* receiver = zmq_socket(ttt, ZMQ_PULL);
    //zmq_connect(receiver, "tcp://localhost:2222");
    zmq_bind(receiver, "tcp://*:2222");


	//printf("Please press enter when workers are ready...");
	pid_t workers[WORKERS_NUM];
    for (int i = 0; i < WORKERS_NUM; ++i) {
        workers[i] = fork();
        if (workers[i] == 0) {
            execv("./hbw", NULL);
        }
        else {
        }
    }
    getchar();

	//printf("Sending tasks to workers...\n");
	// The first message. It's also the signal start of batch.
	int length = strlen("-1");
	zmq_msg_t message;
	zmq_msg_init_size(&message, length);
	memcpy(zmq_msg_data(&message), "-1", length);
	zmq_msg_send(&message, connector, 0);
	zmq_msg_close(&message);
	// Generate some random numbers.
	srandom((unsigned) time(NULL));
	// Send the tasks.
	int count;
	int msec = 0;
	for(;;)
	{
        printf("one tick\n");

        /*Receiving message*/
        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, receiver, 0);
        printf("message received\n");
        zmq_msg_recv(&reply, socket, 0);
        int length = zmq_msg_size(&reply);
        char* msg = malloc(length + 1);
        memcpy(msg, zmq_msg_data(&reply), length);
        zmq_msg_close(&reply);
        /*----------------------*/

        /* sending to workers*/
		int load = atoi(msg);
		msec += load;
		char string[10];
		sprintf(string, "%d", load);
        printf("string = %s\n", string);
        zmq_msg_init_size(&message, strlen(string));
        memcpy(zmq_msg_data(&message), string, strlen(string));
        zmq_msg_send(&message, socket, 0);
        zmq_msg_close(&message);
        /*----------------------*/

        /*sending answer to client*/
        char * answer = "ok!\n";
        zmq_msg_init_size(&message, strlen(answer));
        memcpy(zmq_msg_data(&message), string, strlen(answer));
        zmq_msg_send(&message, receiver, 0);
        zmq_msg_close(&message);
        /*----------------------*/

	}
	printf("Total: %d msec\n", msec);

    /*-----*/
    //sleep(10);
	zmq_close(connector);
	zmq_close(socket);
	zmq_ctx_destroy(context);
    //waitpid(workers[0]);
	return 0;
}