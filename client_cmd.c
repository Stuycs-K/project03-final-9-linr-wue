#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "client_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// read from server and print the database
int cread_data(int server_socket, char* input) {
    rm_newline(input);
    // read database_name
    write(server_socket, input, MAX);

    char buffer[MAX];
    while(read(server_socket, buffer, MAX) != 0) { // read from server line by line
        if (atoi(buffer) = -1) {
            printf("[Error] Database does not exist\n");
            return -1;
        }
        printf("%s\n", buffer);
    }
    return 0;
}

// update database in the server
// operations: add, update, delete
// options: col -1 col_num, row row_num -1, cel row_num col_num (cel only for update)
// entries (no entry for delete)
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
    printf("Enter the edit you would like to make\n: ");
    fgets(buffer, MAX, stdin);
    rm_newline(buffer);
    strcat(cmd, buffer);
    if (buffer[0] != 'd') { // add or update
        printf("Enter the entries: \n: ");
        fgets(buffer, MAX, stdin);
        rm_newline(buffer);
        strcat(cmd, " ");
        strcat(cmd, buffer);
    }
    // edit database_name operation -option 0 0 a b c d
    write(server_socket, buffer, MAX);
    
    //server returns 1 if successful
    read(server_socket, buffer, MAX);
    prin
    if (strcmp(buffer, "1")) printf("Edit sucessful!\n");
    else printf("Edit unsucessful.\n");
}

// --------------------Helper-Functions--------------------
// replace newline at the end of user input with null
void rm_newline(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        if (strcmp(s[i], '\n') == 0) {
            s[i] = '\0';
        }
    }
}
//______________________________FILE_MANIPULATION______________________________