#include "networking.h"

void clientLogic(int server_socket){
  char buffer[BUFFER_SIZE];
  
  char msgToSend[64];
  printf("Enter a string to send: \n"); 
  fgets(msgToSend,sizeof(msgToSend),stdin);
  write(server_socket, msgToSend, strlen(msgToSend)+1);

  read(server_socket,buffer,sizeof(buffer));
  printf("Read from server: %s",buffer);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  char* labIP = "149.89.161.100";
  if(argc>1){
    IP=argv[1];
  }

  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);

  int semd;
  int r;
  int v;
  int *data;
  int shmid;
  char buffer[128];

  shmid = shmget(SHMKEY, 0, 0);//Gets shared memory
  semd = semget(KEY, 1, 0);//Gets semaphore
  if (semd == -1) { //Error in semaphore
    printf("No semaphore exists!\n");
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(KEY, 1, 0);
    v = semctl(semd, 0, GETVAL, 0); 
    printf("Semctl returned: %d\n", v); //Semaphore id will be 1
  }

  printf("Attempting to open semaphore.\n");

  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1; //Using the semaphore by downing value of semaphore
  semop(semd, &sb, 1); //Setting sempahore value to 1 so others can't use it

  data = shmat(shmid, 0, 0); //Attaching shmid to data
  char lastLine[*data]; //Trying to get the last line of the story by using amount of bytes of shared memory from the last line
  printf("Semaphore accessed!\n");
  int w_file = open("story.txt", O_RDWR | O_APPEND); //Opening a file for story
  lseek(w_file, *data * -1, SEEK_END);//Seeking to start of the last line
  int bytes = read(w_file,lastLine,*data); //Reading into the last line using the size of shared memory
  lastLine[*data] = 0;
  printf("Previous Line: %s", lastLine);
  printf("Enter the next line of the story: ");
  fgets(buffer,sizeof(buffer),stdin); //Copying stdin to buffer
  int len = strlen(buffer);
  write(w_file, buffer, len); //Writing buffer to the file
  *data = len;
  shmdt(data);

  sb.sem_op = 1; //Upping value of semaphore to indicate another program can use it
  semop(semd, &sb, 1);

  // while (1){
    // int server_socket = client_tcp_handshake(IP);
    // printf("client connected.\n");
    // clientLogic(server_socket);
  //}
}
