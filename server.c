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
#include <signal.h>
#include <time.h>
#include "networking.h"
#include "server_cmd.h"

union semun { 
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
};

static void sighandler(int signo) {
    if (signo == SIGINT){
      char data[128];
      int bytes; 
      int semd = semget(KEY, 1, 0); //Getting value of semaphore
      int shmid = shmget(SHMKEY, 0, 0); //Getting value of shared memory
      shmctl(shmid, IPC_RMID, 0); //Removing the shared memory
      semctl(semd, IPC_RMID, 0); //Removing the semaphore
      //printf("Segment Deleted\n");
      exit(0);
    }
}

void subserver_logic(int client_socket){
  time_t localTime = time(NULL);
  char * timeStr = ctime(&localTime);
  timeStr[strlen(timeStr)-1] = '\0';
  printf("[%s] Listening to the client commands.\n",timeStr);
  char msgRead[MAX];
  read(client_socket,msgRead,sizeof(msgRead));
  char cmd_line[MAX];
  strcpy(cmd_line, msgRead); // save a copy of command for list

  // command from client into array of arguments
  char* cmd[20];
  char* c = msgRead;
  int i = 0;
  while(cmd[i++] = strsep(&c, " ")) {
    // printf("%d: |%s|\n", i - 1, cmd[i - 1]);
  };
  // command selection
  if (strcmp(cmd[0], "read") == 0) {
    sread_data(client_socket, cmd);
  }
  else if (strcmp(cmd[0], "edit") == 0) {
    sedit_data(client_socket, cmd);
  }
  else if (strcmp(cmd[0], "sort") == 0) {
    ssort_data(client_socket, cmd);
  }
  else if (strcmp(cmd[0], "create") == 0) {
    screate(client_socket, cmd);
  }
  else if (strcmp(cmd[0], "remove") == 0) {
    sremove(client_socket, cmd);
  }
  else if (strcmp(cmd[0], "ls") == 0) {
    slist(client_socket, cmd_line);
  }
}

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup(); 
  signal(SIGINT, sighandler);
  while(1) {
    int client_socket = server_tcp_handshake(listen_socket);
    pid_t p = fork();
    if (p == 0){
      subserver_logic(client_socket);
    }
    else{
      close(client_socket);
    }
  }
}