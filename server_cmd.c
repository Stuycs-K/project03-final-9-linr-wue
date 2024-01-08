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
    FILE* fp = fopen(cmd[1], "r");
    if (fp == NULL) { // database does not exist
        char temp[4] = "-1";
        write(client_socket, temp, strlen(temp) + 1); // write -1 to client
        return -1;
    }
    else { // database exists
        char buffer[MAX];
        int n = count_line(cmd[1]);
        sprintf(buffer, "%d", n);
        write(client_socket, buffer, strlen(buffer) + 1); // write to client number of lines
        usleep(250);
        while (fgets(buffer, MAX, fp) != NULL) {
            write(client_socket, buffer, strlen(buffer) + 1); // write to client line by line 
            usleep(250);
        }
        fclose(fp);
        return 0;
    }
}
// helper function
int count_line(char* database_name) {
    FILE* fp = fopen(database_name, "r");
    int n = 0;
    for (char c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            n++;
        }
    }
    fclose(fp);
    return n;
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
    // edit database_name operation -option col row a,b,c,d
    char buffer[MAX];
    int fd = open(cmd[1], O_WRONLY, 0744);
    FILE* fp = fopen(cmd[1], "r+");

    if (strcmp(cmd[3], "-col") == 0) {
    
    }
    else if (strcmp(cmd[3], "-row") == 0) {
        int row = cmd[4];
        while(int l = 0; l < row; l++) { // skips the lines before target
            char temp[MAX];
            fgets(temp, MAX, fp);
        }
        fputs(cmd[6], fp); // insert line
        
    }

}
void update_(char** cmd) {
    // edit database_name operation -option col row a,b,c,d
    if (strcmp(cmd[3], "-col") == 0) {

    }
    else if (strcmp(cmd[3], "-row") == 0) {
        
    }
    else if (strcmp(cmd[3], "-cel") == 0) {

    }
}
void delete_(char** cmd) {
    // edit database_name operation -option col row a,b,c,d
    if (strcmp(cmd[3], "-col") == 0) {

    }
    else if (strcmp(cmd[3], "-row") == 0) {
        
    }
}
void remove_entry(FILE* fp, char* new) {
}
//______________________________FILE_MANIPULATION______________________________