##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex26 ex27 ex28 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex26: ex26.o 
	$(CC) $(CFLAGS) ex26.o -o ex26

ex27: ex27.o 
	$(CC) $(CFLAGS) ex27.o -o ex27

ex28: ex28.o 
	$(CC) $(CFLAGS) ex28.o -o ex28

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
