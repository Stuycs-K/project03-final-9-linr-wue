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
        printf("[Error] Database does not exist.\n");
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
// options: col -1 col_num, row row_num -1, cel row_num col_num (cel only for update)
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

    //making data struct to send
    //struct data *data = malloc(sizeof(struct data) * 1);
    // strcpy(data->col, strsep(&buffer, " "));
    // strcpy(data->row, strsep(&buffer, " "));

    rm_newline(buffer);
    strcat(cmd, buffer);
    if (buffer[0] != 'd') { // add or update
        printf("Enter entries: ");
        fgets(buffer, MAX, stdin);
        strcat(cmd, " ");
        strcat(cmd, buffer);
        //strcpy(data->entry, strsep(&buffer, " "));
    }
    // edit database_name operation -option 0 0 a,b,c,d
    write(server_socket, cmd, strlen(cmd) + 1);
    //write(server_socket, data, sizeof(struct data));
    
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