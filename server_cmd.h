#ifndef SERVER_CMD_H
#define SERVER_CMD_H
int sread_data(int client_socket, char* database_name);
void sedit_data(int client_socket, char* database_name);
#endif