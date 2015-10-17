CC=gcc
CFLAGS=-O3 -Wall -ansi -pedantic
TARGET=main
TEST=test

default: main

main: table.o main.o
		$(CC) $(CFLAGS) *.o -o $(TARGET).exe

test_files/%: table.o
		$(CC) $(CFLAGS) table.o $@.c -o $@.exe

main.o: main.c
		$(CC) $(CFLAGS) -c main.c
		
table.o: table.c table.h
		$(CC) $(CFLAGS) -c table.c

clean:
		rm -rf *.o *.exe test_files/*.exe
