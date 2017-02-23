//
// Created by mrhacker on 1/13/17.
//


#include <string.h>
#include <stdio.h>
#include "zmq.h"
#include "czmq.h"
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


static void server_worker (void *arg);

void *server_task (void *args)
{
    printf("zzzzz\n");
    //  Frontend socket talks to clients over TCP
    void *context = zmq_ctx_new();
    if(!context) {
        printf("sssssss\n");
    }
    printf("wtfdffff\n");
    void*frontend = zmq_socket(context, ZMQ_ROUTER);
    zmq_bind(frontend, "tcp://*:5570");
    //zctx_t *ctx = zctx_new ();
    //void *frontend = zsocket_new (ctx, ZMQ_ROUTER);
    //zsocket_bind (frontend, "tcp://*:5570");
    printf("ryaaaaaa\n");
    //  Backend socket talks to workers over inproc

    void *backend = zmq_socket(context, ZMQ_DEALER);
    zmq_bind(backend, "inproc://backend");
    //void *backend = zsocket_new (ctx, ZMQ_DEALER);
    //zsocket_bind (backend, "inproc://backend");

    printf("wtfdffff\n");

    //  Launch pool of worker threads, precise number is not critical
    int thread_nbr;
    pthread_t workers[5];
    for (thread_nbr = 0; thread_nbr < 5; thread_nbr++) {
        //zthread_fork (ctx, server_worker, NULL);
        pthread_create(&workers[thread_nbr], NULL, server_worker, &context);
    }

    //  Connect backend to frontend via a proxy
    zmq_proxy (frontend, backend, NULL);

    zmq_ctx_destroy(context);
    return NULL;
}

//  Each worker task works on one request at a time and sends a random number
//  of replies back, with random delays between replies:

static void
server_worker (void *arg)
{
    void * worker = zmq_socket(arg, ZMQ_DEALER);
    //void *worker = zsocket_new (arg, ZMQ_DEALER);
    zmq_connect(worker, "inproc://backend");

    while (true) {
        //  The DEALER socket gives us the reply envelope and message
        zmq_msg_t message;
        zmq_msg_init(&message);

        zmq_msg_recv(&message, worker, 0);
        MessageData *m = (MessageData *) zmq_msg_data(&message);

        printf("------------------\n");
        printf("Message from client: %d  messageId: %d message: %s\n", m->clientId, m->messageNumber, m->message);
        zmq_msg_close(&message);

        //  Send 0..4 replies back
        int reply, replies = randof (5);
        for (reply = 0; reply < replies; reply++) {
            //  Sleep for some fraction of a second
            zclock_sleep (randof (1000) + 1);
            zmq_msg_t reply;
            zmq_msg_init_size(&reply, strlen("ok") + 1);
            memcpy(zmq_msg_data(&reply), "ok\0", 3);
            zmq_msg_send(&reply, worker, 0);
            zmq_msg_close(&reply);
        }
    }
}



int main()
{
    pthread_t thread;
    int res = pthread_create(&thread, NULL, server_task, NULL);
    if (res ) {
        printf("no thread lul(\n");
    }
        return 0;
}