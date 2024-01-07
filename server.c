#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h> 
#include <unistd.h>
#include "networking.h"
#include "server_cmd.h"
#define MAX 20
#define KEY 24602
#define SHMKEY 24605

void subserver_logic(int client_socket){
  printf("Listening to the client commands.\n");
  char msgRead[BUFFER_SIZE];
  read(client_socket,msgRead,sizeof(msgRead));

  // command from client into array of arguments
  char* cmd[20];
  char* c = msgRead;
  int i = 0;
  while(cmd[i++] = strsep(&c, " "));
  // command selection
  if (strcmp(cmd[0], "read") == 0) {
    sread_data(client_socket, cmd);
  }
  else if (strcmp(cmd[0], "edit") == 0) {
    sedit_data(client_socket, cmd);
  }

  // if (strcmp(msgRead,"write")){
  //   printf("1");
  // }

  //printf("Read: %s",msgRead);
  // char rot13Msg[BUFFER_SIZE];
  // strcpy(rot13Msg,msgRead);
  // write(client_socket,msgRead,sizeof(msgRead));
  //printf("Wrote: %s",rot13Msg);
}

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup(); 
  int client_socket = server_tcp_handshake(listen_socket);
  while(1) {
    subserver_logic(client_socket);
  }

  // char data[128];
  // int bytes; 
  // int semd = semget(KEY, 1, 0); //Getting value of semaphore
  // int shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0640); //Getting value of shared memory
  // shmctl(shmid, IPC_RMID, 0); //Removing the shared memory
  // semctl(semd, IPC_RMID, 0);

  // char command[BUFFER_SIZE];
  // printf("Enter a command: \n"); 
  // fgets(command,sizeof(command),stdin);


  //while (1){
    //int client_socket = server_tcp_handshake(listen_socket);
    // pid_t p = fork();
    // if (p == 0){
      //subserver_logic(client_socket);
  //   }
  //   else{
  //     close(client_socket);
  //   }
  // }
}
