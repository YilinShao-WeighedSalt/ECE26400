##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex19 ex25 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex19: ex19.o 
	$(CC) $(CFLAGS) ex19.o -o ex19

ex25: ex25.o 
	$(CC) $(CFLAGS) ex25.o -o ex25

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
