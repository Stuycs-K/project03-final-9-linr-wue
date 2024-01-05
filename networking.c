#include "networking.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char * server_address) {
  char* IP = "127.0.0.1";
  //getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  getaddrinfo(IP, PORT, hints, &results);  //Server sets node to NULL
  
  int serverd;
  //create the socket
  serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  //connect to the server
  connect(serverd, results->ai_addr, results->ai_addrlen);
  
  free(hints);
  freeaddrinfo(results);

  return serverd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);

    //accept the client connection
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
  
    return client_socket;
}

/*Create and bind a socket.
* Place the socket in a listening state.
* Creates semaphore
*/
int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo(NULL, PORT, hints, &results);  //Server sets node to NULL
  
  //create the socket
  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt  error");
  
  //bind the socket to address and port
  bind(clientd, results->ai_addr, results->ai_addrlen);
  //set socket to listen state
  listen(clientd, 10);
  
  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  //Server creates semaphore
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

  //int w_file = open("story.txt", O_RDWR | O_TRUNC | O_CREAT, 0666); //Opening a file for story
  
  printf("Semaphore created\n");
  
  return clientd;
}

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}
