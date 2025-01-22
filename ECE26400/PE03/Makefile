##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

# CFLAGS	= -std=c99 -Wall -Wshadow -Werror -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## if you want to compile with the -O3 flag, comment the preceding CFLAGS and 
## uncomment the following CFLAGS

CFLAGS	= -std=c99 -Wall -Wshadow -Werror -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

pe03: pe03.o answer03.o 
	$(CC) $(CFLAGS) pe03.o answer03.o aux03.o -o pe03

test1: pe03
	./pe03
## rule to run valgrind

memory: pe03
	valgrind --log-file=log0.txt ./pe03
## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f pe03.o answer03.o pe03

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
