##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex8 ex9 ex10 ex11 

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex8: ex8.o 
	$(CC) $(CFLAGS) ex8.o -o ex8

ex9: ex9.o 
	$(CC) $(CFLAGS) ex9.o -o ex9

ex10: ex10.o 
	$(CC) $(CFLAGS) ex10.o -o ex10

ex11: ex11.o 
	$(CC) $(CFLAGS) ex11.o -o ex11

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
