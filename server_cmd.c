#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "server_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// char** cmd: array of arguments from the client command

// read database to client
int sread_data(int client_socket, char** cmd) {
    FILE* Fd = fopen(cmd[1], "r");
    if (Fd == NULL) { // database does not exist
        char temp[4] = "-1";
        write(client_socket, temp, strlen(temp) + 1); // write -1 to client
        fclose(Fd);
        return -1;
    }
    else { // database exists
        char buffer[MAX];
        while (fgets(buffer, MAX, Fd) != NULL) {
            printf("%s", buffer);
            write(client_socket, buffer, strlen(buffer) + 1); // write to client line by line 
        }
        write(client_socket, buffer, 0); // end
        fclose(Fd);
        return 0;
    }
}

// edit database for client
void sedit_data(int client_socket, char** cmd) {
    if (sread_data(client_socket, cmd) == -1) // read database to client
        return;

    // edit database_name operation -option 0 0 a,b,c,d
    if (strcmp(cmd[2], "add") == 0) {
        add_(cmd);
    }
    else if (strcmp(cmd[2], "update") == 0) {
        update_(cmd);
    }
    else if (strcmp(cmd[2], "delete") == 0) {
        delete_(cmd);
    }
    char msg[20] = "Edit successful!";
    write(client_socket, msg, 20);


}
// helper functions
void add_(char** cmd) {
    // edit database_name operation -option 0 0 a,b,c,d
    char buffer[MAX];
    int fd = open(cmd[1], O_WRONLY, 0744);
    FILE* Fd = fopen(cmd[1], "w");

    if (strcmp(cmd[3], "-col") == 0) {

    }
    else if (strcmp(cmd[3], "-row") == 0) {

    }

}
void update_(char** cmd) {
    // edit database_name operation -option 0 0 a,b,c,d
    if (strcmp(cmd[3], "-col") == 0) {

    }
    else if (strcmp(cmd[3], "-row") == 0) {
        
    }
    else if (strcmp(cmd[3], "-cel") == 0) {

    }
}
void delete_(char** cmd) {
    // edit database_name operation -option 0 0 a,b,c,d
    if (strcmp(cmd[3], "-col") == 0) {

    }
    else if (strcmp(cmd[3], "-row") == 0) {
        
    }
}
//______________________________FILE_MANIPULATION______________________________