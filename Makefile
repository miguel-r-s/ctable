CC=gcc
CFLAGS=-O3 -Wall
TARGET=main
TEST=test

default: main

main: table.o main.o shunting-yard.o stack.o
		$(CC) $(CFLAGS) *.o -o $(TARGET).exe -lm

test_files/%: table.o
		$(CC) $(CFLAGS) table.o $@.c -o $@.exe

main.o: main.c
		$(CC) $(CFLAGS) -c main.c
		
table.o: table.c table.h
		$(CC) $(CFLAGS) -c table.c
		
shunting-yard.o: shunting-yard/shunting-yard.c shunting-yard/shunting-yard.h
		$(CC) $(CFLAGS) -c shunting-yard/shunting-yard.c
		
stack.o: shunting-yard/stack.c shunting-yard/stack.h
		$(CC) $(CFLAGS) -c shunting-yard/stack.c 
		
clean:
		rm -rf *.o shunting-yard/*.o
		rm -rf *.exe test_files/*.exe 
