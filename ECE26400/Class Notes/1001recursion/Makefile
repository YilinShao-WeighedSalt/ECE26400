##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -Werror -g -pedantic -fstack-protector-strong --param ssp-buffer-size=1

# CFLAGS	= -std=c99 -Wall -Wshadow -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

EXEC	= ex16 ex16b ex17 ex18 ex19

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

## Build rule

all:	$(EXEC)

## executables

ex16: ex16.o
	$(CC) $(CFLAGS) ex16.o -o ex16

ex16b: ex16b.o
	$(CC) $(CFLAGS) ex16b.o -o ex16b

ex17: ex17.o
	$(CC) $(CFLAGS) ex17.o -o ex17

ex18: ex18.o
	$(CC) $(CFLAGS) ex18.o -o ex18

ex19: ex19.o
	$(CC) $(CFLAGS) ex19.o -o ex19

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f $(EXEC) *.o

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
