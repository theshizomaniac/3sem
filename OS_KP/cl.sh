gcc -std=c11 -lzmq -pthread main_client.c -o user
gcc -std=c11 -lzmq -pthread sub_client.c -o sub_chat

