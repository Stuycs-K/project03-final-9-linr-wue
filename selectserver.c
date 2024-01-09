#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/shm.h> 
#include <signal.h>
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
      printf("Segment Deleted\n");
      exit(0);
    }
}

int main(){
    signal(SIGINT, sighandler);
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    //char* PORT = "19230";
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    getaddrinfo(NULL, PORT , hints, &results);  //NULL is localhost or 127.0.0.1
    //create socket
    int listen_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);\
    //this code allows the port to be freed after program exit.  (otherwise wait a few minutes)
    int yes = 1;
    if ( setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1 ) {
        printf("sockopt  error\n");
        printf("%s\n",strerror(errno));
        exit(-1);
    }
    int err = bind(listen_socket, results->ai_addr, results->ai_addrlen);
    if(err == -1){
        printf("Error binding: %s",strerror(errno));
        exit(1);
    }
    listen(listen_socket, 3);//3 clients can wait to be processed
    printf("Listening on port %s\n",PORT);
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    fd_set read_fds;
    char buff[1025]="";

    //making semaphore
    int v, r;
    int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644); //Creating the semaphore
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
  
  printf("Semaphore created\n");

    while(1){

        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(listen_socket,&read_fds);
        int i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);

        //if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            printf("Recieved from terminal: '%s'\n",buff);
        }

        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            //accept the connection
            int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
            printf("Connected, waiting for data.\n");

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

            // //read the whole buff
            // read(client_socket,buff, sizeof(buff));
            // //trim the string
            // buff[strlen(buff)-1]=0; //clear newline
            // if(buff[strlen(buff)-1]==13){
            //     //clear windows line ending
            //     buff[strlen(buff)-1]=0;
            // }

            // printf("\nRecieved from client '%s'\n",buff);
            // close(client_socket);
        }
        else{
            close(listen_socket);
        }
    }

    free(hints);
    freeaddrinfo(results);
    return 0;
}