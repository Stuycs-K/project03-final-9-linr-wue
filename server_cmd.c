#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "server_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// read database to client
void sread_data(int client_socket, char* cmd) {
    FILE* Fd = fopen(cmd[1], 'r');
    if (Fd == NULL) { // database does not exist
        char* temp[40] = "[Error] database does not exist";
        write(client_socket, temp, 40); // write error to client
    }
    else { // database exists
        char* buffer[MAX];
        while (fgets(buffer, MAX, Fd) != NULL) {
            write(client_socket, buffer, MAX); // write to client line by line 
        }
    }
    write(client_socket, buffer, 0); // end
    fclose(Fd);
}

// edit database for client
void sedit_data(int client_socket, char* cmd) {
    sread_data(client_socket, database_name);

    // edit database_name operation -option 0 0 a b c d
    char* buffer[MAX];
    int fd = open(cmd[1], O_WRONLY, 0744);
    FILE* Fd = fopen(cmd[1], 'w');
    if (strcmp(cmd[2], "add") == 0) {

    }
    else if (strcmp(cmd[2], "update") == 0) {

    }
    else if (strcmp(cmd[2], "delete") == 0) {

    }


}
// helper functions
void add() {

}
void update() {

}
void delete() {
    
}
//______________________________FILE_MANIPULATION______________________________