CC = gcc
CFLAG = -Wall -O3

procfork: procfork.c utils.h
	$(CC) $(CFLAG) -o procfork procfork.c

client: client.c utils.h
	$(CC) $(CFLAG) -o client client.c

server: server.c utils.h
	$(CC) $(CFLAG) -o server server.c

procshm: procshm.c utils.h
	$(CC) $(CFLAG) -o procshm procshm.c

clean:
	rm procfork client server procshm