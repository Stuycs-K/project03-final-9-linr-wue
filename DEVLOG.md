# Dev Log:

## Ruize Lin

### 2024-01-04 - Working on read and edit command for client
25 min - discussing and setting up the files we will need for the project.

15 min - working on read command.

45 min - working on write command.

### 2024-01-05 - Working on read and edit for server
20 min - continued discussing necessary files and functions. Modified read so that the database is sent line by line.

40 min - working on file not exist error handling for read for client and server.

30 min - working on edit for client and server.

### 2024-01-06 - Integrating command selections into client and server
30 min - implementing command response in client and server.

50 min - fixing read function.

### 2024-01-08 - Working on update cell function
40 min - modifying update cell function for server.

30 min - fixing bug and writing tests.

### 2024-01-09 - Working on update cell function
30 min - fixing problems with sending command to server.

45 min - modifying and testing update cell function.

### 2024-01-10 - Working on read output formatting
25 min - discussing other commands for database.

15 min - formatting outputto include row and column number.

45 min - making the columns line up.

### 2024-01-11 - Working on delete row function
30 min - working on delete row function

25 min - working on clearing a cell ('~' represents a blank cell) if no entry is entered. 

### 2024-01-12 - Working on update row function
10 min - discussing implementation of sort function.

35 min - working on update row.

### 2024-01-14 - Working on sort data function
45 min - working on sort data function.

30 min - modify sort data to be able to sort by column.

30 min - modify sort data to be able to compare numbers and account for carriage return.

## Eric Wu

### 2024-01-04 - Setting up project; reviewing code
25 min in class - discussing and setting up the files we will need for the project. I also added previous code just to start off with the project. 

20 min at home - reviewing semaphore/shared memory code and editing makefile to test them; planning how to use with network

### 2024-01-05 - Working on the networking and semaphore

1 hr (40 min in class; 20 min at home) - cleaned up unneccessary code; set up basic network with server and client without any subserver; edited the files to have server set up semaphore and shared memory, and the server correctly creates semaphore; tried having client access the semaphore but there is a segfault; bug in the if statement of comparing the stdin buffer and a string

### 2024-01-06 - Didn't work on project today

### 2024-01-07 - Working on subserver and semaphore

1 hr - fixed subserver so it works properly; cleaned up code; added sighandler to server to close semaphore; implemented semaphore usage into client but cannot test it because of unresolved bug

15 min - trying to run select server but unsuccessful although the client strcmp seems to work when using select server

### 2024-01-08 - Fixing semaphore, testing select server

40 min - fixing semaphore/shared memory code; unsure if we will use shm; worked on some documentation; started testing select server

35 min - messing around with select server, got the code to compile but will test tomorrow

### 2024-01-09 - Fixing semaphore, testing select server, working on structs

40 min - found a few errors with select server code since I didn't have the right includes and such but I was able to fix it; we are unsure if we want to use select server still; was reading about sending a struct through the network using serialization but turns out that is not needed; discussed more info on what we need for project

30 min - created helper functions to place semaphores in; working on structs - one to hold the command and database name for easy readability in code and the other to send entry updates to the server

### 2024-01-10 - Discussing usage of structs, adding rows

40 min - discussed the use of structs in our code, it works for the holding using it for command and database name but it would be hard to use it in database manipulation because I would have to refactor a lot of the code, so we are pushing it off a day or two to further decide; discussed ways to implement some of the code for database manipulation

30 min - worked on the adding row function but got confused on how to implement the feature because of the way database manipulation is coded

### 2024-01-11 - Finished adding rows, adding timestamps, editing documentation

40 min - worked on debugging the add row function and cleared up any confusion I had with the syntax and using the code

40 min - tested the add row function and finally fixed it; added local timestamps to server requests; worked on documentation, specifically the instructions on how the syntax for commands such as adding/deleting/updating data

### 2024-01-12 - Worked on sorting data

40 min - started working on the sort data function, currently getting error with placing all of the data from data file into an array of strings to do selection sort; discussed our next and final steps: finishing sort, adding restrictions to number of entries user can add, being able to create a data file

### 2024-01-13 - Didn't work on project
