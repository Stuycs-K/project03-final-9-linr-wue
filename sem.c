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
#define KEY 24602
#define SHMKEY 24605

union semun { 
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };

void create(){
  int v, r;
  int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644); //Creating the semaphore
  //union semun us;
  //us.val = 1;
  // r = semctl(semd, 0, SETVAL, us);
  // v = semctl(semd, 0, GETVAL, 0);
  if (semd == -1) { //Error in semaphore
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(KEY, 1, 0);
    v = semctl(semd, 0, GETVAL, 0); 
    printf("semctl returned: %d\n", v); //Semaphore id will be 1
  }
  else { //No error in semaphore
    union semun us;
    us.val = 1;
    r = semctl(semd, 0, SETVAL, us);
    printf("semctl returned: %d\n", r); //setting semaphore value to 1
  }
  int shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0640); //Creating the shared memory

  int w_file = open("story.txt", O_RDWR | O_TRUNC | O_CREAT, 0666); //Opening a file for story
  
  printf("Semaphore created\n");
}

void removeSem(){
  char data[128];
  int bytes; 
  int semd = semget(KEY, 1, 0); //Getting value of semaphore
  int shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0640); //Getting value of shared memory
  shmctl(shmid, IPC_RMID, 0); //Removing the shared memory
  // char input[3];
  // printf("Would you like to remove the semaphore?(y/n) ");
  // fgets(input, 3, stdin);

  // if (input[0] == 'y') {
    semctl(semd, IPC_RMID, 0); //Removing the semaphore
    printf("segment deleted\n");
  //}
  int r_file = open("story.txt", O_RDONLY);
  bytes = read(r_file,data,128);
  while (bytes){
    printf("%s\n",data);
    bytes = read(r_file,data,128);
  }
}

void view(){
  char data[128];
  int bytes; 
  int r_file = open("story.txt", O_RDONLY);
  bytes = read(r_file,data,128);
  while (bytes){
    printf("%s\n",data);
    bytes = read(r_file,data,128);
  }
}

int main(int argc, char *argv[]) {
  if(strcmp(argv[1],"create") == 0){
    create();
  }
  else if (strcmp(argv[1],"remove") == 0){
    removeSem();
  }
  else if (strcmp(argv[1],"view") == 0){
    view();
  }
  return 0;
}
