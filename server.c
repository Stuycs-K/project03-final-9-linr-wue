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
#define KEY 24602
#define SHMKEY 24605

void subserver_logic(int client_socket){
  printf("Listening to the client commands\n");
  char msgRead[BUFFER_SIZE];
  read(client_socket,msgRead,sizeof(msgRead));
  if (strcmp(msgRead,"write")){
    printf("1");
  }
  //printf("Read: %s",msgRead);
  // char rot13Msg[BUFFER_SIZE];
  // strcpy(rot13Msg,msgRead);
  // write(client_socket,msgRead,sizeof(msgRead));
  //printf("Wrote: %s",rot13Msg);
}

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup(); 
  int client_socket = server_tcp_handshake(listen_socket);
  subserver_logic(client_socket);

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
