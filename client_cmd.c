#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "client_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// read from server and print out the content in the the database
void cread_data(int server_socket, char* database_name) {
    char buffer[MAX];
    buffer[0] = '\0';
    strcat(buffer, "read ");
    strcat(buffer, database_name);
    // buffer: read database_name
    write(server_socket, buffer, MAX);

    read(server_socket, buffer, MAX); // temp
    printf("%s\n", buffer);
}

// update database in the server with user prompt
void cedit_data(int server_socket, char* database_name) {
    char buffer[MAX];
    buffer[0] = '\0';
    strcat(buffer, "edit ");
    strcat(buffer, database_name);
    strcat(buffer, " ");

    read_data(server_socket); // print database
    printf("For the list of possible edit commands, enter: help\n");
    int n = -1;
    while(n = -1) {
        // user prompt
        printf("Enter the edit you would like to make in the format [operation options entries]\n: ");
        fgets(buffer, MAX, stdin);

        if(strcmp(buffer, "help\n") == 0) { // help
            printf("OPERATIONS\n");
            printf("\tadd\n\tupdate\n\tdelete\n");
            printf("OPTIONS\n");
            printf("\t-col\t: followed by column number in the format [0 col_num].\n");
            printf("\t-row\t: followed by row number in the format [row_num 0].\n");
            printf("\t-cel\t: followed by row and column number in the format [row_num col_num]. *used in combination with update only\n");
            printf("ENTRIES\n");
            printf("\teach entry is separated by single space\n");
        }
        else {
            n = 0;
        }
    }
    // buffer: edit database_name operation -option 0 0 a b c d\n
    buffer[strlen(buffer) - 1] = '\0';
    // buffer: edit database_name operation -option 0 0 a b c d
    write(server_socket, buffer, MAX);
    
    //server writes "1" to client if success, "0" if fail
    read(server_socket, buffer, MAX);
    if (strcmp(buffer, "1")) printf("Edit sucessful!\n");
    else printf("Edit unsucessful.\n");
}


//______________________________FILE_MANIPULATION______________________________