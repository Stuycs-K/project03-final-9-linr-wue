#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 2000

//______________________________DATABASE_MANIPULATION______________________________
// read from server and print out the content in the the database
int read(int server_socket) {
    char buffer[MAX];
    read(server_socket, buffer, MAX);
    printf("%s\n", buffer);
    return 0;
}

// update database in the server with user prompt
int update(int server_socket) {
    char buffer[MAX];
    printf("Enter");
    fgets(buffer, MAX, stdin);
    write(server_socket, buffer, MAX);
    return 0;
}

//______________________________FILE_MANIPULATION______________________________