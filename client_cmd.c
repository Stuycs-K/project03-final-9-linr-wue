#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "client_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// char* input: command line input with newline at the end

// read from server and print the database
int cread_data(int server_socket, char* input) {
    rm_newline(input);
    // read database_name
    write(server_socket, input, strlen(input) + 1);

    char buffer[MAX];
    read(server_socket, buffer, MAX); // read from server number of lines
    int n = atoi(buffer);
    if (n == -1) { // database not exist
        printf("[Error] Database does not exist\n");
        return -1;
    }
    else {
        while(n > 0) { // read from server line by line
            read(server_socket, buffer, MAX);
            printf("\t%s", buffer);
            n--;
        }
    }
    return 0;
}

// update database in the server
// operations: add, update, delete
// options: col col_num -1, row -1 row_num, cel col_num row_num(cel only for update)
// entries: separated by comma (no entry for delete)
void cedit_data(int server_socket, char* input) {
    char buffer[MAX];
    char cmd[MAX];
    cmd[0] = '\0';
    rm_newline(input);
    strcat(cmd, input);
    strcat(cmd, " ");

    if (cread_data(server_socket, input) == -1) // read and print database
        return; 

    // user prompt
    printf("Enter the edit you would like to make: ");
    fgets(buffer, MAX, stdin);
    rm_newline(buffer);
    strcat(cmd, buffer);
    if (buffer[0] != 'd') { // add or update
        printf("Enter entries: ");
        fgets(buffer, MAX, stdin);
        strcat(cmd, " ");
        rm_newline(buffer);
        strcat(cmd, buffer);
    }
    // edit database_name operation -option col row a,b,c,d
    printf("%s\n", cmd);
    write(server_socket, cmd, sizeof(cmd));
    
    // server returns "Edit successful!"
    read(server_socket, buffer, 20);
    printf("%s\n", buffer);
}

// --------------------Helper-Functions--------------------
// replace newline at the end of user input with null
void rm_newline(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
        }
    }
}
//______________________________FILE_MANIPULATION______________________________