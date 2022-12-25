CC = gcc
CFLAG = -Wall -O3

filcpy: filcpy.c
	$(CC) $(CFLAG) -o filcpy filcpy.c

pipcpy: pipcpy.c
	$(CC) $(CFLAG) -o pipcpy pipcpy.c

fifo: proc1.c proc2.c
	$(CC) $(CFLAG) -o proc1 proc1.c
	$(CC) $(CFLAG) -o proc2 proc2.c

rm:
	rm filcpy
	rm pipcpy