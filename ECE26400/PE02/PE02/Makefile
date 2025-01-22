##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Werror -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## if you want to compile with the -O3 flag, comment the preceding CFLAGS and 
## uncomment the following CFLAGS

# CFLAGS	= -std=c99 -Wall -Wshadow -Werror -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

pe02: pe02.o answer02.o 
	$(CC) $(CFLAGS) pe02.o answer02.o -o pe02

## rule to test with argument option 0

# test1: pe02
# 	./pe01 0 inputfile

## rule to test with argument option 1

# test2: pe01
# 	./pe01 1 inputfile

test1: pe02
	./pe02

## rule to test all

## test_all: test3 test1 test2

## rule to run valgrind

memory: pe02
	valgrind --log-file=log0.txt ./pe02
#	valgrind --log-file=log1.txt ./pe02 1 inputfile

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f pe02.o answer02.o pe02

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
