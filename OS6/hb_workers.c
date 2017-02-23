//
// Created by mrhacker on 1/14/17.
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "zmq.h"
#include <sys/stat.h>
#include "semaphore.h"
#define SNAME "/mysem"
#define SHMSIZE 100


double square(double x)
{
    return x * x;
}
double average(double x, double y)
{
    return (x + y) / 2.0;
}
double good_enough(double guess, double x)
{
    return abs(square(guess) - x) < 0.000001;
}
double improve(double guess, double x)
{
    return average(guess, x / guess);
}
double sqrt_inner(double guess, double x)
{
    if(good_enough(guess, x))
        return guess;
    else
        return sqrt_inner(improve(guess, x), x);
}
double newton_sqrt(double x)
{
    return sqrt_inner(1.0, x);
}

write_to_array(int x, sem_t * sem, char * array)
{
    printf("hit the block\n");
    sem_wait(sem);
    printf("writing...\n");
    array[array[0]] = x;
    sem_post(sem);

}

int main (int argc, char const *argv[])
{

    //printf("---|||| worker\n");
    int shmid;
    char *shm;
    shmid = shmget(2009, SHMSIZE * sizeof(char),  IPC_EXCL);
    shm = shmat(shmid, 0, 0);
    //printf ("Child reads <%s>\n",shm) ;
    shmdt(shm);
    //shmctl(shmid, IPC_RMID, NULL);


    sem_t *sem = sem_open(SNAME, 0); /* Open a preexisting semaphore. */

    void* context = zmq_ctx_new();
    // Let's initialize a socket to receive messages.
    void* receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:4040");
    // Let's initialize a socket to send the messages.
    void* sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:5050");
    for(;;)
    {
        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, receiver, 0);
        int length = zmq_msg_size(&reply);
        char* msg = malloc(length + 1);
        memcpy(msg, zmq_msg_data(&reply), length);
        zmq_msg_close(&reply);
        fflush(stdout);
        double val = atof(msg);
        printf("%.1f: %.1f\n", val, newton_sqrt(val));
        write_to_array(val, sem,shm);
        sleep(1);
        free(msg);
        zmq_msg_t message;
        char* ssend = "T";
        int t_length = strlen(ssend);
        zmq_msg_init_size(&message, t_length);
        memcpy(zmq_msg_data(&message), ssend, t_length);
        zmq_msg_send(&message, sender, 0);
        zmq_msg_close(&message);
    }
    zmq_close(receiver);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0;
}