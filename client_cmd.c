#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "networking.h"
#include "client_cmd.h"
#define COL_LEN -16

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
        int r = 1;
        int is_first = 1;
        while(n > 0) { // read from server line by line
            read(server_socket, buffer, MAX);
            char* cell;
            char* s;
            int c = 0;
            if (is_first) { // print column index
                char temp[MAX];
                strcpy(temp, buffer);
                s = temp;
                while ((cell = strsep(&s, ",")) != NULL) {
                    c++;
                }
                printf("\t    ");
                for (int i = 1; i <= c; i++) {
                    if (i == c) {
                        printf(" %-1d", i);
                    }
                    else {
                        printf(" %*d", COL_LEN, i);
                    }
                }
                printf("\n\t");
                int length = strlen(buffer) + 1;
                for (int i = 0; i < 3 * length; i++) {
                    printf("-");
                }
                printf("\n");
                is_first--;
            }
            printf("\t%-3d|", r++); // print row index
            s = buffer;
            int i = 1;
            while ((cell = strsep(&s, ",")) != NULL) {
                if (i == c) {
                    rm_newline(cell);
                    int width = strlen(cell) + 1;
                    printf(" %*s", -1 * width, cell);
                }
                else {
                    printf(" %*s", COL_LEN, cell);
                }
            }
            printf("\n");
            n--;
        }
    }
    return 0;
}
// helper functions

// update database in the server
// operations: add, update, delete
// options: col col_num, row row_num, cel col_num row_num (cel only for update)
// entries: separated by comma (~ for empty cell)
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
    //struct data *data = malloc(sizeof(struct data) * 1);
    // strcpy(data->col, strsep(&buffer, " "));
    // strcpy(data->row, strsep(&buffer, " "));

    rm_newline(buffer);
    strcat(cmd, buffer);
    if (buffer[0] != 'd') { // add or update
        printf("Enter entries: ");
        fgets(buffer, MAX, stdin);
        rm_newline(buffer);
        strcat(cmd, " ");
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
        if (s[i] == '\n' || s[i] == '\r') {
            s[i] = '\0';
        }
    }
}

// sort data in the server by the column entered
// <: smallest to largest
// >: largest to smallest
void csort_data(int server_socket, char* input) {
    // sort database_name order
    // sort database_name order
    char cmd[MAX];
    cmd[0] = '\0';
    rm_newline(input);
    strcat(cmd, input);

    // user prompt
    char buffer[MAX];
    printf("Enter the column you would like to sort the data by: ");
    fgets(buffer, MAX, stdin);
    rm_newline(buffer);
    strcat(cmd, " ");
    strcat(cmd, buffer);

    // sort database_name order col_num
    printf("%s\n", cmd);
    write(server_socket, cmd, sizeof(cmd));

    read(server_socket, buffer, sizeof(buffer));
    printf("%s\n", buffer);
}
//______________________________FILE_MANIPULATION______________________________
// create database in server
void ccreate(int server_socket, char* input) {
    rm_newline(input);
    // create database_name
    printf("%s\n", input);
    write(server_socket, input, strlen(input) + 1);

    char buffer[MAX];
    read(server_socket, buffer, sizeof(buffer));
    printf("%s\n", buffer);
}

// remove database in server
void cremove(int server_socket, char* input) {
    rm_newline(input);
    // remove database_name
    printf("%s\n", input);
    write(server_socket, input, strlen(input) + 1);

    char buffer[MAX];
    read(server_socket, buffer, sizeof(buffer));
    printf("%s\n", buffer);
}

// list all database in server
// order: > or <
void clist(int server_socket, char* input) {
    // list order
    // list -l order
    // list moddate order
    // list -l moddate order
    // list size order
    // list -l size order
    rm_newline(input);
    char* input_ary[8];
    char* s = input;
    int i = 0;
    while(input_ary[i++] = strsep(&s, " "));
    i -= 2;

    char cmd[MAX];
    cmd[0] = '\0';
    strcat(cmd, "ls");
    if (strcmp(input_ary[1], "moddate") == 0 
        || i == 3 && strcmp(input_ary[2], "moddate") == 0) {
        strcat(cmd, " -t");
    }
    else if (strcmp(input_ary[1], "size") == 0
        || i == 3 && strcmp(input_ary[2], "size") == 0) {
        strcat(cmd, " -S");
    }
    if (strcmp(input_ary[1],"-l") == 0) {
        strcat(cmd, " -l");
    }
    if (strcmp(input_ary[i], "<") == 0) {
        strcat(cmd, " -r");
    }
    // list order -> ls (-r)
    // list -l order ->  ls -l (-r)
    // list moddate order -> ls -t (-r)
    // list -l moddate order -> ls -l (-r)
    // list size order -> ls -S (-r)
    // list -l size order -> ls -S -l (-r)
    printf("%s\n", cmd);
    write(server_socket, cmd, sizeof(cmd));

    char buffer[MAX];
    read(server_socket, buffer, MAX); // read from server number of lines
    int n = atoi(buffer);
    while (n > 0) {
        read(server_socket, buffer, sizeof(buffer));
        printf("\t%s", buffer);
        n--;
    }
}
//______________________________OTHER______________________________
