##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## if you want to compile with the -O3 flag, comment the preceding CFLAGS and 
## uncomment the following CFLAGS

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

pa04: pa04.o answer04.o 
	$(CC) $(CFLAGS) pa04.o answer04.o  -o pa04

test1: pa04
	./pa04
## rule to run valgrind

memory: pa04
	valgrind --log-file=log0.txt ./pa04
## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f pa04.o answer04.o pa04

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
