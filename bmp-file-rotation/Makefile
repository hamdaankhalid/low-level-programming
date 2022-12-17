CC = gcc
CFLAGS = -std=c11 -Wall
LD = gcc

all: main

main: bmp_file_rotation.o bmp.o
	$(CC) $(CFLAGS) -o bmpr bmp.o bmp_file_rotation.o

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c -o bmp.o bmp.c -I .

bmp_file_rotation.o: bmp_file_rotation.c
	$(CC) $(CFLAGS) -c -o bmp_file_rotation.o bmp_file_rotation.c -I .

clean:
	rm -f bmp.o bmpr bmp_file_rotation.o
