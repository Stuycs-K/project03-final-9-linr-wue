#ifndef SERVER_CMD_H
#define SERVER_CMD_H
void sread_data(int client_socket, char** cmd);
int count_line(char* database_name);
void sedit_data(int client_socket, char** cmd);
void add_row(char** cmd);
void update_row(char** cmd);
void update_cel(char** cmd);
void delete_row(char** cmd);
#endif