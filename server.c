#include "networking.h"

void rot13(char * string){
  for (int i = 0; i < strlen(string); ++i) {
    if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z')) {
      if (string[i] > 'm' || (string[i] > 'M' && string[i] <= 'Z')) {
        string[i] -= 13;
      } 
      else {
        string[i] += 13;
      }
    }
  }
}

void subserver_logic(int client_socket){
  printf("Listening to the client\n");
  char msgRead[BUFFER_SIZE];
  read(client_socket,msgRead,sizeof(msgRead));
  //printf("Read: %s",msgRead);
  char rot13Msg[BUFFER_SIZE];
  rot13(msgRead);
  strcpy(rot13Msg,msgRead);
  write(client_socket,msgRead,sizeof(msgRead));
  //printf("Wrote: %s",rot13Msg);
}

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup(); 
  int client_socket = server_tcp_handshake(listen_socket);
  subserver_logic(client_socket);

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
