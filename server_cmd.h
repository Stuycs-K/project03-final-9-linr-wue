#ifndef SERVER_CMD_H
#define SERVER_CMD_H
void sread_data(int client_socket, char* database_name);
void sedit_data(int client_socket, char* database_name);
#endif