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
#include "client_cmd.h"

void accessSem(){
  int semd;
  int r;
  int v;
  int *data;
  int shmid;
  char buffer[128];
  shmid = shmget(SHMKEY, 0, 0);//Gets shared memory
  semd = semget(KEY, 1, 0);//Gets semaphore
  if (semd == -1) { //Error in semaphore
    printf("[Error] No semaphore exists\n");
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(KEY, 1, 0);
    v = semctl(semd, 0, GETVAL, 0); 
    printf("Semctl returned: %d\n", v); //Semaphore id will be 1
  }
  printf("Waiting to edit file.\n");
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1; //Using the semaphore by downing value of semaphore
  semop(semd, &sb, 1); //Setting sempahore value to 1 so others can't use it
  printf("You can now edit the file!\n");
}

void upSem(){
  int semd;
  struct sembuf sb;
  semd = semget(KEY, 1, 0);//Gets semaphore
  sb.sem_num = 0;
  sb.sem_op = 1; //Upping value of semaphore to indicate another program can use it
  semop(semd, &sb, 1);
}

void clientLogic(int server_socket){
  char buffer[BUFFER_SIZE];
  char msgToSend[64];
  printf("Enter a command: "); 
  fgets(msgToSend,sizeof(msgToSend),stdin);
  // Find command
  char temp[MAX];
  char* c = temp;
  strcpy(temp, msgToSend);
  char* first_cmd = strsep(&c, " \n");

  //Making a struct
  // struct pop_entry *clientStruct = malloc(sizeof(struct pop_entry) * 1);
  // strcpy(clientStruct->command, strsep(&c, " "));
  // strcpy(clientStruct->database, strsep(&c, " "));
  // write(server_socket,clientStruct,sizeof(struct pop_entry));

  // Commands selections
  if (strcmp(first_cmd, "read") == 0) {
  // if (strcmp(clientStruct->command, "read") == 0) {
    cread_data(server_socket, msgToSend);
  }
  else if (strcmp(first_cmd, "edit") == 0) {
  // else if (strcmp(clientStruct->command, "edit") == 0) { 
    accessSem(); //Accessing semaphore
    cedit_data(server_socket, msgToSend); //Thing to do inside semaphore
    upSem(); //Upping semaphore so other clients can use
  }
  else if (strcmp(first_cmd, "sort") == 0) {
    accessSem();
    csort_data(server_socket, msgToSend);
    upSem();
  }
  else if (strcmp(first_cmd, "create") == 0) {
    ccreate(server_socket, msgToSend);
  }
  else if (strcmp(first_cmd, "remove") == 0) {
    cremove(server_socket, msgToSend);
  }
  else if (strcmp(first_cmd, "list") == 0) {
    clist(server_socket, msgToSend);
  }
  else{
    printf("[Error] Command not found\n");
  }
  printf("\n");
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  //char* labIP = "149.89.161.100";
  if(argc>1){
    IP=argv[1];
  }
  while (1) {
    int server_socket = client_tcp_handshake(IP);
    printf("Client connected.\n");
    clientLogic(server_socket);
  }
}