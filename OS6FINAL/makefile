all: client server

client:
	gcc -std=c11 -lzmq main_client.c -o client

server:
	gcc -std=c11 -lzmq main_server.c TVector.c -o server

