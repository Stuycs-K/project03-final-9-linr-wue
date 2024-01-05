#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "server_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
void sread_data(int client_socket, char* database_name) {
    FILE* db = fopen(database_name, 'r');
    // if database does not exit, write to client error message
    char* buffer[MAX];
    while (fgets(buffer, MAX, db) != NULL) {
        write(client_socket, buffer, MAX);
    }
}
void sedit_data(int client_socket, char* database_name) {
}
//______________________________FILE_MANIPULATION______________________________