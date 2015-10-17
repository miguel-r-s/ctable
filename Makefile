CC=gcc
CFLAGS=-O3 -Wall -ansi -pedantic
TARGET=main
TEST=test

default: main

main: table.o main.o
		$(CC) $(CFLAGS) *.o -o $(TARGET)

tests/%: *.o
		$(CC) $(CFLAGS) *.o $@.c -o $(TEST)
		
main.o: main.c
		$(CC) $(CFLAGS) -c main.c
		
table.o: table.c table.h
		$(CC) $(CFLAGS) -c table.c

clean:
		rm -rf *.o $(TARGET) $(TEST)
