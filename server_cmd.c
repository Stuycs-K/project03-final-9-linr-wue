#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "server_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
void sread_data(int client_socket, char* cmd) {
    FILE* Fd = fopen(cmd[1], 'r');
    if (Fd == NULL) { // database does not exist
        char* temp[4] = "-1";
        write(client_socket, temp, 4); // write -1 (error) to client
    }
    else { // database exists
        char* buffer[MAX];
        while (fgets(buffer, MAX, Fd) != NULL) {
            write(client_socket, buffer, MAX); // write to client line by line 
        }
    }
    fclose(Fd);
}

void sedit_data(int client_socket, char* cmd) {
    sread_data(client_socket, database_name);

    // edit database_name operation -option 0 0 a b c d
    char* buffer[MAX];
    int fd = open(cmd[1], O_WRONLY, 0744);
    FILE* Fd = fopen(cmd[1], 'w');
    if (strcmp())


}
// helper functions
void add() {

}
void update() {

}
void delete() {
    
}
//______________________________FILE_MANIPULATION______________________________