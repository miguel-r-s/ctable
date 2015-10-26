CC=gcc
CFLAGS=-O3 -Wall
TARGET=main
TEST=test

vpath %.o src/
vpath %.c src/
vpath %.h src/

default: main

main: table.o main.o shunting-yard.o stack.o
		$(CC) $(CFLAGS) src/*.o -o $(TARGET).exe -lm

test_files/%: table.o
		$(CC) $(CFLAGS) src/table.o $@.c -o $@.exe

main.o: main.c
		$(CC) $(CFLAGS) -c src/main.c \
			-o src/main.o
		
table.o: table.c table.h
		$(CC) $(CFLAGS) -c src/table.c \
			-o src/table.o
		
shunting-yard.o: shunting-yard/shunting-yard.c shunting-yard/shunting-yard.h
		$(CC) $(CFLAGS) -c src/shunting-yard/shunting-yard.c \
			-o src/shunting-yard.o
		
stack.o: shunting-yard/stack.c shunting-yard/stack.h
		$(CC) $(CFLAGS) -c src/shunting-yard/stack.c  \
			-o src/stack.o
		
clean:
		rm -rf *.o src/*.o
		rm -rf *.exe src/test_files/*.exe 
