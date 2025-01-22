##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex2

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex2: ex2.o add.o ltostr.o
	$(CC) $(CFLAGS) ex2.o add.o ltostr.o -o ex2

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
