CC = gcc
CFLAGS = -std=c11 -Wall
LD = gcc

all: main

main: main.o mem.o
	$(CC) $(CFLAGS) -o main main.o mem.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c -I .

mem.o: mem.c
	$(CC) $(CFLAGS) -c -o mem.o mem.c -I .

clean:
	rm -f main.o main mem.o
