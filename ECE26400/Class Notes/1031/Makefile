##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex30 ex31 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex31: ex31.o list.o list_1.o
	$(CC) $(CFLAGS) ex31.o list.o list_1.o -o ex31

ex30: ex30.o list.o
	$(CC) $(CFLAGS) ex30.o list.o -o ex30


## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
