#ifndef CLIENT_CMD_H
#define CLIENT_CMD_H
int cread_data(int server_socket, char* input);
void cedit_data(int server_socket, char* input);
void rm_newline(char* s);
void csort_data(int server_socket, char* input);
void ccreate(int server_socket, char* input);
void cremove(int server_socket, char* input);
void clist(int server_socket, char* input);
#endif