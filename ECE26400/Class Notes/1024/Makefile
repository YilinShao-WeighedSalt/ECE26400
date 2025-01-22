##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex24 ex27 ex28 ex29 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex29: ex29.o
	$(CC) $(CFLAGS) ex29.o -o ex29

ex28: ex28.o
	$(CC) $(CFLAGS) ex28.o -o ex28

ex27: ex27.o
	$(CC) $(CFLAGS) ex27.o -o ex27

ex24: ex24.o
	$(CC) $(CFLAGS) ex24.o -o ex24

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
