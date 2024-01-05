#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// read from server and print out the content in the the database
void read(int server_socket) {
    char buffer[MAX];
    read(server_socket, buffer, MAX);
    printf("%s\n", buffer);
}

// update database in the server with user prompt
void edit(int server_socket) {
    char buffer[MAX];
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
            printf("\t-col\n\t-row\n\t-cel\t*used in combination with update only\n");
            printf("ENTRIES\n");
            printf("\teach entry is separated by single space\n");
        }
        else {
            n = 0;
        }
    }
    write(server_socket, buffer, MAX);
}

//______________________________FILE_MANIPULATION______________________________