#include <stdio.h>
#include <stdlib.h>
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
        write(client_socket, temp, sizeof(temp)); // write -1 to client
        return -1;
    }
    else { // database exists
        char buffer[MAX];
        int n = count_line(cmd[1]);
        sprintf(buffer, "%d", n);
        write(client_socket, buffer, sizeof(buffer)); // write to client number of lines
        usleep(250);
        while (fgets(buffer, MAX, fp) != NULL) {
            write(client_socket, buffer, sizeof(buffer)); // write to client line by line 
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
    write(client_socket, msg, sizeof(msg));


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
        int row = atoi(cmd[5]);
        // open databases
        FILE* old = fopen(cmd[1], "r");
        char temp_name[20];
        temp_name[0] = '\0';
        strcat(temp_name, "temp_");
        strcat(temp_name, cmd[1]);
        FILE* new = fopen(temp_name, "w");
        // copy rows before target
        char temp[MAX];
        for (int r = 1; r < row; r++) { // skips the rows before target
            fgets(temp, MAX, old);
            printf("\t%s", temp);
            fputs(temp, new);
        }
        //adding new row
        
        // copy rows after target
        while (fgets(temp, MAX, old) != NULL) {
            fputs(temp, new);
        }
        fclose(old);
        remove(cmd[1]);
        rename(temp_name, cmd[1]);
        fclose(new);
    }

}
int update_(char** cmd) {
    // edit database_name operation -option col row a,b,c,d
    if (strcmp(cmd[3], "-col") == 0) {

    }
    else if (strcmp(cmd[3], "-row") == 0) {
        
    }
    else if (strcmp(cmd[3], "-cel") == 0) {
        update_cell(cmd);
        return 1;
    }
}
void delete_(char** cmd) {
    // edit database_name operation -option col row a,b,c,d
    if (strcmp(cmd[3], "-col") == 0) {

    }
    else if (strcmp(cmd[3], "-row") == 0) {
        
    }
}
void update_cell(char** cmd) {
    // edit database_name operation -option col row a,b,c,d
    int col = atoi(cmd[4]);
    int row = atoi(cmd[5]);
    // open databases
    FILE* old = fopen(cmd[1], "r");
    char temp_name[20];
    temp_name[0] = '\0';
    strcat(temp_name, "temp_");
    strcat(temp_name, cmd[1]);
    FILE* new = fopen(temp_name, "w");
    // copy rows before target
    char temp[MAX];
    for (int r = 1; r < row; r++) { // skips the rows before target
        fgets(temp, MAX, old);
        printf("\t%s", temp);
        fputs(temp, new);
    }
    // copy cells before target
    fgets(temp, MAX, old);
    char* cell;
    char* sp = temp;
    for (int c = 1; c < col; c++) {
        cell = strsep(&sp, ",");
        fputs(cell, new);
        fputs(",", new);
    }
    // replace cell on target column
    cell = strsep(&sp, ",");
    fputs(cmd[6], new);
    // copy remaining cells after target
    cell = strsep(&sp, ",");
    if (cell == NULL) {
        fputs("\n", new);
    }
    else { // updated cell is not the last cell of the row
        while (cell != NULL) {
            fputs(",", new);
            fputs(cell, new);
            cell = strsep(&sp, ",");
        }
    }
    // copy rows after target
    while (fgets(temp, MAX, old) != NULL) {
        fputs(temp, new);
    }
    fclose(old);
    remove(cmd[1]);
    rename(temp_name, cmd[1]);
    fclose(new);
}
//______________________________FILE_MANIPULATION______________________________