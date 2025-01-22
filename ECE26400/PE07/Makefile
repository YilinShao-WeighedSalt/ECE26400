##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## if you want to compile with the -O3 flag, comment the preceding CFLAGS and 
## uncomment the following CFLAGS

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

pe07: pe07.o answer07.o 
	$(CC) $(CFLAGS) pe07.o answer07.o  -o pe07

test1: pe07
	./pe07
## rule to run valgrind

memory: pe07
	valgrind --log-file=log0.txt ./pe07
## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f pe07.o answer07.o pe07

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
