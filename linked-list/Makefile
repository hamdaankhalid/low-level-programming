CC = gcc
CFLAGS = -std=c11 -Wall
LD = gcc

all: main

main: main.o linked_list.o
	$(CC) $(CFLAGS) -o main main.o linked_list.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c -I .

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) -c -o linked_list.o linked_list.c -I .

clean:
	rm -f main.o main linked_list.o
