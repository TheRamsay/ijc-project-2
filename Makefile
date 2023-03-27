CC=gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra

all: tail 

tail.o: tail.c

tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.out *.zip tail tail-o