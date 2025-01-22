##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex20 ex21 ex22 ex26 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex26: ex26.o
	$(CC) $(CFLAGS) ex26.o -o ex26

ex22: ex22.o
	$(CC) $(CFLAGS) ex22.o -o ex22

ex20: ex20.o
	$(CC) $(CFLAGS) ex20.o -o ex20

ex21: ex21.o
	$(CC) $(CFLAGS) ex21.o -o ex21 

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
