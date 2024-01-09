#include "networking.h"

void clientLogic(int server_socket){
  char buffer[BUFFER_SIZE];
  
  char msgToSend[64];
  printf("Enter a string to send: \n"); 
  fgets(msgToSend,sizeof(msgToSend),stdin);
  write(server_socket, msgToSend, strlen(msgToSend)+1);

  // read(server_socket,buffer,sizeof(buffer));
  // printf("Read from server: %s",buffer);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  char* labIP = "149.89.161.100";
  if(argc>1){
    IP=argv[1];
  }
  while (1){
    int server_socket = client_tcp_handshake(IP);
    printf("client connected.\n");
    clientLogic(server_socket);
  }
}
