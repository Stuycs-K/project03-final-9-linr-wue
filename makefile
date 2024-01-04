.PHONY: clean run compile control
compile: clientComp serverComp 
clientComp: client.o networking.o
	@gcc -o client client.o networking.o
serverComp: server.o networking.o
	@gcc -o server server.o networking.o
server.o: server.c 
	@gcc -c server.c 
client.o: client.c 
	@gcc -c client.c 
networking.o: networking.c networking.h
	@gcc -c networking.c 

commands.o: commands.c commands.h
	@gcc -c commands.c 
selectserver.o: selectserver.c
	@gcc -c selectserver.c 
sem.o: sem.c
	@gcc -c sem.c
clean:
	@rm -f *.o server client 2> /dev/null || true
