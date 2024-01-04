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
clean:
	@rm -f *.o server client 2> /dev/null || true
