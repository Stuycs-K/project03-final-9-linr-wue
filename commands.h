#ifndef COMMANDS_H
#define COMMANDS_H
struct command{
    char command[16];
    char operation[16];
    char argument[256];
};
int read(int server_socket);
int edit(int server_socket);
#endif