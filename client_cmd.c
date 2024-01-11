#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "networking.h"
#include "client_cmd.h"

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
        int l = 1;
        while(n > 0) { // read from server line by line
            read(server_socket, buffer, MAX);
            printf("\t%d| %s", l++, buffer);
            n--;
        }
    }
    return 0;
}

// update database in the server
// operations: add, update, delete
// options: col col_num, row row_num, cel col_num row_num (cel only for update)
// entries: separated by comma (no entry for delete)
void cedit_data(int server_socket, char* input) {
    char buffer[MAX];
    char cmd[MAX];
    cmd[0] = '\0';
    rm_newline(input);
    strcat(cmd, input);
    strcat(cmd, " ");

    // user prompt
    printf("Enter the edit you would like to make: ");
    fgets(buffer, MAX, stdin);

    //making data struct to send
    struct pop_entry *data = malloc(sizeof(struct data) * 1);
    // strcpy(data->col, strsep(&buffer, " "));
    // strcpy(data->row, strsep(&buffer, " "));

    rm_newline(buffer);
    strcat(cmd, buffer);
    if (buffer[0] != 'd') { // add or update
        printf("Enter entries: ");
        fgets(buffer, MAX, stdin);
        strcat(cmd, " ");
        rm_newline(buffer);
        strcat(cmd, buffer);
        //strcpy(data->entry, strsep(&buffer, " "));
    }
    // edit database_name operation -option col row a,b,c,d
    printf("%s\n", cmd);
    write(server_socket, cmd, sizeof(cmd));
    
    // server returns "Edit successful!"
    read(server_socket, buffer, sizeof(buffer));
    printf("%s\n", buffer);
}
// helper functions
void rm_newline(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
        }
    }
}
//______________________________FILE_MANIPULATION______________________________