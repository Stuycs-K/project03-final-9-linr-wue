#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "client_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// read from server and print the database
void cread_data(int server_socket, char* input) {
    rm_newline(input);
    // read database_name
    write(server_socket, input, MAX);

    char buffer[MAX];
    while(read(server_socket, buffer, MAX) != 0) { // read from server line by line
        printf("%s\n", buffer);
    }
}

// update database in the server
// operations: add, update, delete
// options: col 0 col_num, row row_num 0, cel row_num col_num (cel only for update)
// entries (no entry for delete)
void cedit_data(int server_socket, char* input) {
    char buffer[MAX];
    char cmd[MAX];
    cmd[0] = '\0';
    rm_newline(input);
    strcat(cmd, input);
    strcat(cmd, " ");

    cread_data(server_socket, input); // read and print database

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