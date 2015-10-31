CC=gcc
CFLAGS=-O3 -Wall
TARGET=main
TEST=test
BINDIR=build

vpath %.o $(BINDIR)
vpath %.c src:tests
vpath %.h src

default:
	@echo "No target selected!"

tests: tests.o ctable.o shunting-yard.o stack.o
		$(CC) $(CFLAGS) $(BINDIR)/*.o -o tests/tests.exe -lm -I src/

tests.o: tests.c
		$(CC) $(CFLAGS) -c tests/tests.c \
			-o $(BINDIR)/tests.o -I src/
		
ctable.o: ctable.c ctable.h
		$(CC) $(CFLAGS) -c src/ctable.c \
			-o $(BINDIR)/ctable.o
		
shunting-yard.o: shunting-yard/shunting-yard.c shunting-yard/shunting-yard.h
		$(CC) $(CFLAGS) -c src/shunting-yard/shunting-yard.c \
			-o $(BINDIR)/shunting-yard.o
		
stack.o: shunting-yard/stack.c shunting-yard/stack.h
		$(CC) $(CFLAGS) -c src/shunting-yard/stack.c  \
			-o $(BINDIR)/stack.o
		
clean:
		rm -rf $(BINDIR)/*.o
		rm -rf *.exe *.exe 
		
