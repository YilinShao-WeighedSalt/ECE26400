##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex11 ex12 ex13 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex11: ex11.o 
	$(CC) $(CFLAGS) ex11.o -o ex11

ex12: ex12.o 
	$(CC) $(CFLAGS) ex12.o -o ex12

ex13: ex13.o
	$(CC) $(CFLAGS) ex13.o -o ex13

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
