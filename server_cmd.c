#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h> 

#include "server_cmd.h"
#define MAX 256

//______________________________DATABASE_MANIPULATION______________________________
// char** cmd: array of arguments from the client command
// read database to client
void sread_data(int client_socket, char** cmd) {
    FILE* fp = fopen(cmd[1], "r");
    if (fp == NULL) { // database does not exist
        char temp[4] = "-1";
        write(client_socket, temp, sizeof(temp)); // write -1 to client
        return;
    }
    // database exists
    char buffer[MAX];
    int n = count_line(cmd[1]);
    sprintf(buffer, "%d", n);
    write(client_socket, buffer, sizeof(buffer)); // write to client number of lines
    usleep(250);
    while (fgets(buffer, MAX, fp) != NULL) {
        write(client_socket, buffer, sizeof(buffer)); // write to client line by line 
        usleep(250);
    }
    fclose(fp);
}
// helper function
int count_line(char* database_name) {
    FILE* fp = fopen(database_name, "r");
    int n = 0;
    for (char c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            n++;
        }
    }
    fclose(fp);
    return n;
}

// edit database for client
void sedit_data(int client_socket, char** cmd) {
    FILE* fp = fopen(cmd[1], "r");
    char msg[64];
    msg[0] = '\0';
    if (fp == NULL) { // database does not exist
        strcat(msg, "[Error] Database does not exist");
        write(client_socket, msg, sizeof(msg)); // write error to client
        return;
    }

    if (strcmp(cmd[2], "add") == 0) {
        if (strcmp(cmd[3], "-col") == 0) {
            // edit database_name add -col col_num a,b,c,d
            // add_col(cmd);
        }
        else if (strcmp(cmd[3], "-row") == 0) {
            // edit database_name add -row row_num a,b,c,d
            add_row(cmd);
        }
    }
    else if (strcmp(cmd[2], "update") == 0) {
        if (strcmp(cmd[3], "-col") == 0) {
            // edit database_name update -col col_num a,b,c,d
            // update_col(cmd);
        }
        else if (strcmp(cmd[3], "-row") == 0) {
            // edit database_name update -row row_num a,b,c,d
            update_row(cmd);
        }
        else if (strcmp(cmd[3], "-cel") == 0) {
            // edit database_name update -cel col_num row_num a
            update_cel(cmd);
        }
    }
    else if (strcmp(cmd[2], "delete") == 0) {
        if (strcmp(cmd[3], "-col") == 0) {
            // edit database_name delete -col col_num
            // delete_col(cmd);
        }
        else if (strcmp(cmd[3], "-row") == 0) {
            // edit database_name delete -row row_num
            delete_row(cmd);
        }
    }
    strcat(msg, "Database successfully modified!");
    write(client_socket, msg, sizeof(msg)); // write message to client
}
void add_row(char** cmd) {
    // edit database_name operation -row row a,b,c,d
    char buffer[MAX];
    FILE* fp = fopen(cmd[1], "r+");
    int row = atoi(cmd[4]);
    // open databases
    FILE* old = fopen(cmd[1], "r");
    char temp_name[20];
    temp_name[0] = '\0';
    strcat(temp_name, "temp_");
    strcat(temp_name, cmd[1]);
    FILE* new = fopen(temp_name, "w");
    // copy rows before target
    char temp[MAX];
    for (int r = 1; r < row; r++) { // skips the rows before target
        fgets(temp, MAX, old);
        printf("\t%s", temp);
        fputs(temp, new);
    }
    // adding new row
    char * newRow = cmd[5];
    strcat(newRow,"\n");
    fputs(newRow,new);
    //copy rows after target
    while (fgets(temp, MAX, old) != NULL) {
        fputs(temp, new);
    }
    fclose(old);
    remove(cmd[1]);
    rename(temp_name, cmd[1]);
    fclose(new);
}
void update_row(char** cmd) {
    // edit database_name operation -option row a,b,c,d
    int row = atoi(cmd[4]);
    // open databases
    FILE* old = fopen(cmd[1], "r");
    char temp_name[20];
    temp_name[0] = '\0';
    strcat(temp_name, "temp_");
    strcat(temp_name, cmd[1]);
    FILE* new = fopen(temp_name, "w");
    // copy rows before and after target
    char temp[MAX];
    for (int r = 1; fgets(temp, MAX, old) != NULL; r++) { // skips the rows before target
        if (r != row) {
            fputs(temp, new);
        }
        else {
            fputs(cmd[5], new);
            fputs("\n", new);
        }
    }
    remove(cmd[1]);
    rename(temp_name, cmd[1]);
    fclose(old);
    fclose(new);
}
void update_cel(char** cmd) {
    // edit database_name operation -option col row a,b,c,d
    int col = atoi(cmd[4]);
    int row = atoi(cmd[5]);
    // open databases
    FILE* old = fopen(cmd[1], "r");
    char temp_name[20];
    temp_name[0] = '\0';
    strcat(temp_name, "temp_");
    strcat(temp_name, cmd[1]);
    FILE* new = fopen(temp_name, "w");
    // copy rows before target
    char temp[MAX];
    for (int r = 1; r < row; r++) { // skips the rows before target
        fgets(temp, MAX, old);
        fputs(temp, new);
    }
    // copy cells before target
    fgets(temp, MAX, old);
    char* cell;
    char* sp = temp;
    for (int c = 1; c < col; c++) {
        cell = strsep(&sp, ",");
        fputs(cell, new);
        fputs(",", new);
    }
    // replace cell on target column
    cell = strsep(&sp, ",");
    fputs(cmd[6], new);
    // copy remaining cells after target
    cell = strsep(&sp, ",");
    if (cell == NULL) {
        fputs("\n", new);
    }
    else { // updated cell is not the last cell of the row
        while (cell != NULL) {
            fputs(",", new);
            fputs(cell, new);
            cell = strsep(&sp, ",");
        }
    }
    // copy rows after target
    while (fgets(temp, MAX, old) != NULL) {
        fputs(temp, new);
    }
    remove(cmd[1]);
    rename(temp_name, cmd[1]);
    fclose(old);
    fclose(new);
}
void delete_row(char** cmd) {
    // edit database_name operation -option row
    int row = atoi(cmd[4]);
    // open databases
    FILE* old = fopen(cmd[1], "r");
    char temp_name[20];
    temp_name[0] = '\0';
    strcat(temp_name, "temp_");
    strcat(temp_name, cmd[1]);
    FILE* new = fopen(temp_name, "w");
    // copy rows before and after target
    char temp[MAX];
    for (int r = 1; fgets(temp, MAX, old) != NULL; r++) { // skips the rows before target
        if (r != row) {
            fputs(temp, new);
        }
    }
    remove(cmd[1]);
    rename(temp_name, cmd[1]);
    fclose(old);
    fclose(new);
}

// sort database for client
void ssort_data(int client_socket, char** cmd) {
    int col = atoi(cmd[3]);
    // sort database_name order col_num
    FILE* old = fopen(cmd[1], "r");
    char msg[64];
    msg[0] = '\0';
    if (old == NULL) { // database does not exist
        strcat(msg, "[Error] Database does not exist");
        write(client_socket, msg, sizeof(msg)); // write error to client
        return;
    }
    char temp_name[20];
    temp_name[0] = '\0';
    strcat(temp_name, "stemp_");
    strcat(temp_name, cmd[1]);
    FILE* new = fopen(temp_name, "w");

    char min[MAX];
    int min_row = 0;
    if (count_line(cmd[1]) <= 1) { // do nothing if database is empty
        strcat(msg, "Database successfully modified!");
        write(client_socket, msg, sizeof(msg));
        return;
    }
    // write categories into new
    fgets(min, MAX, old);
    fputs(min, new);
    fclose(old);
    sort_delete_row(cmd[1], 1);
    old = fopen(cmd[1], "r");
    // sort rows
    while (fgets(min, MAX, old) != NULL) { // set min to first row
        min_row = 1;
        char min_cell[MAX];
        strcpy(min_cell, find_cell(min, col)); // set minimum cell for the first row
        char cur_row[MAX];
        for (int r = 2; fgets(cur_row, MAX, old) != NULL; r++) { // compare min to rest of the rows
            char cur_cell[MAX];
            strcpy(cur_cell, find_cell(cur_row, col)); // set current cell
            // compare cells
            if (is_number(min_cell) && is_number(cur_cell)) { // numerical cells
                double min_val, cur_val;
                if (strcmp(min_cell, "~") == 0) min_val = 0.0;
                else min_val = atof(min_cell);
                if (strcmp(cur_cell, "~") == 0) cur_val = 0.0;
                else cur_val = atof(cur_cell);

                if (strcmp(cmd[2], "<") == 0 && min_val > cur_val) { // smallest to largest
                strcpy(min, cur_row);
                strcpy(min_cell, find_cell(min, col));
                min_row = r;
                }
                else if (strcmp(cmd[2], ">") == 0 && min_val < cur_val) { // largest to smallest
                    strcpy(min, cur_row);
                    strcpy(min_cell, find_cell(min, col));
                    min_row = r;
                }
            }
            else { // string cells
                if (strcmp(cmd[2], "<") == 0 && strcmp(min_cell, cur_cell) > 0) { // smallest to largest
                strcpy(min, cur_row);
                strcpy(min_cell, find_cell(min, col));
                min_row = r;
                }
                else if (strcmp(cmd[2], ">") == 0 && strcmp(min_cell, cur_cell) < 0) { // largest to smallest
                    strcpy(min, cur_row);
                    strcpy(min_cell, find_cell(min, col));
                    min_row = r;
                }
            }
        }
        fputs(min, new); // write min row into new database
        fclose(old);
        sort_delete_row(cmd[1], min_row); // remove min row from old database
        old = fopen(cmd[1], "r");
    }
    remove(cmd[1]);
    rename(temp_name, cmd[1]);
    fclose(old);
    fclose(new);
    strcat(msg, "Database successfully modified!");
    write(client_socket, msg, sizeof(msg));
}
// helper function
void sort_delete_row(char* database_name, int min_row) {
    char* delete_cmd[20];
    delete_cmd[1] = database_name;
    char row_num[8];
    sprintf(row_num, "%d", min_row);
    delete_cmd[4] = row_num;
    delete_row(delete_cmd);
}
char* find_cell(char* row, int col) {
    char temp[MAX];
    strcpy(temp, row);
    char* cell;
    char* sp = temp;
    for (int c = 1; c <= col; c++) {
        cell = strsep(&sp, ",\n\r");
    }
    return cell;
}
int is_number(char* cell) {
    for(int i = 0; cell[i] != '\0' && cell[i] != '\n'; i++) {
        if (isdigit(cell[i]) == 0 && cell[i] != '~' && cell[i] != '.') {
            return 0; // false
        }
    }
    return 1; // true
}
//______________________________FILE_MANIPULATION______________________________
// create database
void screate(int client_socket, char** cmd) {
    // create name
    char msg[64];
    msg[0] = '\0';
    int fd = open(cmd[1], O_CREAT | O_EXCL, 0744);
    if (errno == EEXIST) {
        strcat(msg, "[Error] Database with the same name already exists");
    }
    else if (fd == -1) {
        strcat(msg, "[Error] Creating database unsuccessful");
    }
    else {
        strcat(msg, "Database successfully created!");
    }
    write(client_socket, msg, sizeof(msg));
}

// remove database
void sremove(int client_socket, char** cmd) {
    // remove name
    char msg[64];
    msg[0] = '\0';
    int n = remove(cmd[1]);
    if (errno == EBUSY) {
        strcat(msg, "[Error] Database is currently in use");
    }
    else if (errno == ENOENT) {
        strcat(msg, "[Error] Invalid database name")
    }
    else if (n == -1) {
        strcat(msg, "[Error] Removing database unsuccessful");
    }
    else {
        strcat(msg, "Database successfully removed!");
    }
    write(client_socket, msg, sizeof(msg));
}

// list all database
void slist(int client_socket, char** cmd) {
    
}