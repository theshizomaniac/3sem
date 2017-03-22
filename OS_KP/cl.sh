gcc -std=c11 -lzmq -pthread -g -pg main_client.c -o user
gcc -std=c11 -lzmq -pthread -g -pg sub_client.c -o sub_chat

