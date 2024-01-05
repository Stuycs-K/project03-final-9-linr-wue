.PHONY: clean run compile control
compile: clientComp serverComp semControl semWrite

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
	@rm -f *.o server client semControl semWrite 2> /dev/null || true
