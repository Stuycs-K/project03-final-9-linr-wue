[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# A Simple Database

### project03-final-9-linr-wue

Ruize Lin, Eric Wu
       
### Project Description:

This project utilizes the C programming language to create a simple database that uses networking, semaphores, processes, and editing files. In our database, users will be able to access their data file, and use a multitude of commands such as adding, updating, deleting, and sorting to play around with their data.
  
### Instructions:

## Compiling and running the program

To run the program, you must first compile the program by typing **"make compile"** in the terminal.

After compiling all of the files, run **"./server"** in the terminal to start the server. To access the network as a client, type "./client" from a different terminal 
or computer. To access from another computer, run **"./client"** in the terminal with the IP address of the computer e.g "./client 149.89.161.100".

## Interacting with the program

# Running the program

To start off, the user must have a data file that they would like to access.

Then, the user must start the server by running "./server" in the terminal. The user will have to turn on a client by running "./client" in the terminal. 

The client will connect to the server and will ask for a command.

# Creating a data file

If the user wants to create a data file, they should type "read (file_name)" in the terminal. 

# Deleting a data file

If the user wants to delete a data file, they should type "read (file_name)" in the terminal. 

# Reading the data file

If the user wants to view the data file, they should type "read (file_name)" in the terminal. 

# Sorting the data

If the user wants to sort the data file, they should type "sort (file_name) (>/<)" in the terminal. 
Then, the user will be prompted to type the column they want to sort the data by.

# Editing the data file

If the user wants to edit the data file, they should type "edit (file_name)" in the terminal. 
Then, the user will be prompted to enter the change they want to make. 

# The edit commands

The three main edit commands are: adding a row, deleting a row/column or cell, and updating a row/column/cell. 

# Syntax

The general syntax for rows/col would be **"(operation) -(row/col) (row/col #)"**.

The general syntax for a cell would be **"(operation) -cel (col #) (row #)"**.

*Note*: When editing rows/columns/cells, the columns and rows start at 1, not 0.

# Adding a row

To add a row: the syntax would be **"add -row (row #)"**. 
The user will then be prompted to add the entries for the row and fill out an entire row for the data. 
They should then type in the entries with commas in between and no spaces. 
For example, if there are 5 columns, the entries to be added would be "a,b,c,d,e". 

# Deleting a row/column/cell

To delete a row/column: the syntax would be **"delete -(row/col) (row/col #)"**. This will delete the row or column.

To delete a cell, just apply the syntax for a cell.

# Updating a row/column/cell

To update a row/column: the syntax would be **"update -(row/col) (row/col #)"**. The user will then be prompted to add the entries for the row. The user will have to fill out an entire row for the data. 
They should then type in the entries with commas in between and no spaces. 

To update a cell, just apply the syntax for a cell and only type one entry.

## Example code usage

Command: edit text.data

Specific edit command: update -row 4

Entries to update row: 

```
Client connected.
Enter a command: edit text.data
Waiting to edit file.
You can now edit the file!
Enter the edit you would like to make: update -row 4
Enter entries: hi,a,y    
edit text.data update -row 4 hi,a,y
Database successfully modified!
```

### Bugs