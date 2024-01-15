#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sem.h>

#include "networking.h"
#include "client_cmd.h"
#define COL_LEN -20

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
        // strcat(cmd, " ");
        // strcat(cmd, buffer);
        // //checking if there are more entries than col
        // char * cmdCopy;
        // strcpy(cmdCopy,cmd);
        // char * database;
        // database = strsep(&cmdCopy," ");
        // database = strsep(&cmdCopy," ");
        // char * entryCheck;
        // strcpy(entryCheck,buffer);
        // int entryNum = 0; 
        // FILE* fp = fopen(database, "r");
        // if (fp == NULL) { // database does not exist
        //     printf("[Error] Database does not exist");
        //     return;
        // }  
        // char * column;
        // fgets(column,sizeof(column),fp);
        // while (strsep(&column,",") != NULL){
        //     entryNum++;
        // }
        // printf("%d",entryNum);


        //strcpy(data->entry, strsep(&buffer, " "));
    }
    // edit database_name operation -option col row a,b,c,d
    printf("%s\n", cmd);
    write(server_socket, cmd, sizeof(cmd));
    
    // server returns "Edit successful!"
    read(server_socket, buffer, sizeof(buffer));
    int semd;
    struct sembuf sb;
    semd = semget(KEY, 1, 0);//Gets semaphore
    sb.sem_op = 1; //Upping value of semaphore to indicate another program can use it
    semop(semd, &sb, 1);
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