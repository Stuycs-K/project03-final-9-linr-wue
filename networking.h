#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h>

#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "19230"
#define MAX 256
#define BUFFER_SIZE 1024
#define KEY 24602
#define SHMKEY 24605
struct pop_entry {
  char database[20];
  char command[15];
};
void err(int i, char*message);
int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);
#endif
