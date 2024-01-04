# Final Project Proposal

## Group Members:

Ruize Lin and Eric Wu
       
# Intentions:

Writing a simple database program.
    
# Intended usage:

The project will be used to send data to a database program and also retrieve the data. This will be done in the terminal that will have a server and client connection and the client can perform commands.
  
# Technical Details:

First, we will be using a client and server using sockets that will be the medium of communicating to the database. The client can write out different commands to access the database and retrieve information or add information to it. A subserver that is forked will be handling all the logic with the database and client and we will use a semaphore so that only one client can access the server at a time.
For now, Ruize will be responsible for accessing the database and setting up the commands, and Eric will be responsible for setting up the network and semaphore.
We aren't sure what data structures or algorithms we will be using yet. 
    
# Intended pacing:

A timeline with expected completion dates of parts of the project.

Makefile and all files set up by Thursday 1/3/24.

Basic network and semaphore set up by Monday 1/8/24.

Basic database commands to be done by Monday 1/8/24.

Subserver to be set up by Tuesday 1/9/24. 
