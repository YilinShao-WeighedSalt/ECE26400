##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex36 ex37 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex36: ex36.o tree.o tree_1.o
	$(CC) $(CFLAGS) ex36.o tree.o tree_1.o -o ex36

ex37: ex37.o tree.o tree_1.o tree_2.o stack.o
	$(CC) $(CFLAGS) ex37.o tree.o tree_1.o tree_2.o stack.o -o ex37

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
