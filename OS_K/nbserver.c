#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#define PORT    5000
#define MAXMSG  512

typedef struct TBet{
    char colour;
    int number;
    int sum;
} TBet;

typedef struct TPlayer {
    int balance;
    char name[50];
    bool winner;
    TBet bet;
} TPlayer;

TPlayer players[10];
int i = 0;

int make_socket (uint16_t port)
{
  int sock;
  struct sockaddr_in name;
  memset(&name, '0', sizeof(name));
  /* Create the socket. */
  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  /* Give the socket a name. */
  name.sin_family = AF_INET;
  name.sin_port = htons (port);
  name.sin_addr.s_addr = htonl (INADDR_ANY);
  if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    }

  return sock;
}

int read_from_client (int filedes)
{
  char buffer[MAXMSG];
  int nbytes;
  int balance = 1000;
  //nbytes = read (filedes, buffer, sizeof(buffer));
    nbytes = read (filedes, &players[i], sizeof(TPlayer));
  if (nbytes < 0)
    {
      /* Read error. */
      perror ("read");
      exit (EXIT_FAILURE);
    }
  else if (nbytes == 0)
    /* End-of-file. */
    return -1;
  else
    {
      /* Data read. */
      printf ("| player `%s' connected\n", players[i].name);
        printf("|| bet: %c %d %d", players[i].bet.colour, players[i].bet.number, players[i].bet.sum);
      if (!strcmp(players[i].name,"crash")) {
        return 1;
      }
      write(filedes, &balance, sizeof(int));
      return 0;
    }
    ++i;
}

int main (void)
{
  int sock;
  fd_set active_fd_set, read_fd_set;
  int i;
  struct sockaddr_in clientname;
    unsigned int size;

  /* Create the socket and set it up to accept connections. */
  sock = make_socket (PORT);
  if (listen (sock, 1) < 0)
    {
      perror ("listen");
      exit (EXIT_FAILURE);
    }
    printf("\nmade socket\n");
  /* Initialize the set of active sockets. */
  FD_ZERO (&active_fd_set);
  FD_SET (sock, &active_fd_set);

  while (1)
    {
      /* Block until input arrives on one or more active sockets. */
      read_fd_set = active_fd_set;
      struct timeval time;
      time.tv_usec = 0;
      time.tv_sec = 10;
      if (select (FD_SETSIZE, &read_fd_set, NULL,NULL, &time) < 0)
        {
          perror ("select");
          exit (EXIT_FAILURE);
        }
    printf("\nsocket active....\n");
      /* Service all the sockets with input pending. */
      for (i = 0; i < FD_SETSIZE; ++i)
        if (FD_ISSET (i, &read_fd_set))
          {
            if (i == sock)
              {
                /* Connection request on original socket. */
                int new;
                  printf("FD_SETSIZE = %d\n", FD_SETSIZE);
                size = sizeof (clientname);
                new = accept (sock, (struct sockaddr *)&clientname, &size);//NULL, NULL);//&clientname, size);
                if (new < 0)
                  {
                    perror ("accept");
                    exit (EXIT_FAILURE);
                  }
                fprintf (stderr,
                         "Server: connect from host %s, port %hd.\n",
                         inet_ntoa (clientname.sin_addr),
                         ntohs (clientname.sin_port));
                FD_SET (new, &active_fd_set);
              }
            else
              {
                int n = 0;
                /* Data arriving on an already-connected socket. */
                n = read_from_client (i);
                if (n  < 0)
                  {
                    close (i);
                    FD_CLR (i, &active_fd_set);
                  }
                else if (n == 1) {
                  printf("Stop jobs\n");
                  close (i);
                  FD_CLR (i, &active_fd_set);
                  exit(0);
                }
              }
          }
    }
}
