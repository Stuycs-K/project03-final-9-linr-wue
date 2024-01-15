.PHONY: clean run compile control
compile: clientComp serverComp selectserver selectclient

# main client and server
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

# select test
selectserver: selectserver.o networking.o  server_cmd.o
	@gcc -o select selectserver.o networking.o server_cmd.o
selectserver.o: selectserver.c
	@gcc -c selectserver.c 
selectclient: selectclient.o networking.o client_cmd.o
	@gcc -o selectclient1 selectclient.o networking.o client_cmd.o
selectclient.o: selectclient.c 
	@gcc -c selectclient.c 

clean:
	@rm -f *.o server client select selectclient1 2> /dev/null || true
