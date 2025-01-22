##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex2 ex3 ex4

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex2: ex2.o add.o ltostr.o bit_pattern.o
	$(CC) $(CFLAGS) ex2.o add.o ltostr.o bit_pattern.o -o ex2

ex3: ex3.o bit_pattern.o
	$(CC) $(CFLAGS) ex3.o bit_pattern.o -o ex3

ex4: ex4.o 
	$(CC) $(CFLAGS) ex4.o -o ex4

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
