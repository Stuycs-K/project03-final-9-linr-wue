#ifndef SERVER_CMD_H
#define SERVER_CMD_H
int sread_data(int client_socket, char** cmd);
int count_line(char* database_name);
void sedit_data(int client_socket, char** cmd);
void add_(char** cmd);
void update_(char** cmd);
void delete_(char** cmd);
void update_cell(char** cmd);
#endif