.PHONY: clean run compile control
compile: clientComp serverComp semControl semWrite selectserver

clientComp: client.o networking.o client_cmd.o
	@gcc -o client client.o networking.o client_cmd.o
serverComp: server.o networking.o server_cmd.o
	@gcc -o server server.o networking.o server_cmd.o
server.o: server.c 
	@gcc -c server.c 
client.o: client.c 
	@gcc -c client.c 
networking.o: networking.c networking.h
	@gcc -c networking.c 
# client and server commands
client_cmd.o: client_cmd.c client_cmd.h
	@gcc -c client_cmd.c
server_cmd.o: server_cmd.c server_cmd.h
	@gcc -c server_cmd.c
# select
selectserver: selectserver.o 
	@gcc -o select selectserver.o
selectserver.o: selectserver.c
	@gcc -c selectserver.c 
# semaphore
semControl: semControl.o 
	@gcc -o semControl sem.c 
semControl.o: sem.c 
	@gcc -c sem.c
control: semControl
	@./semControl $(ARGS)
semWrite: semWrite.o
	@gcc -o semWrite semusertest.c
semWrite.o: semusertest.c
	@gcc -c semusertest.c
write: semWrite
	@./semWrite
sem.o: sem.c
	@gcc -c sem.c

clean:
	@rm -f *.o server client semControl semWrite select 2> /dev/null || true
