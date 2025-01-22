##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex33 ex35 ex36

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex36: ex36.o tree.o tree_1.o
	$(CC) $(CFLAGS) ex36.o tree.o tree_1.o -o ex36

ex35: ex35.o tree.o 
	$(CC) $(CFLAGS) ex35.o tree.o -o ex35

ex33: ex33.o list.o list_3.o
	$(CC) $(CFLAGS) ex33.o list.o list_3.o -o ex33


## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
