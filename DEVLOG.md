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
