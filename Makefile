CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
PROGRAM = program
PROGRAM_OBJS = program.o
PROGS = $(PROGRAM)

all : $(PROGS)

$(PROGRAM) : $(PROGRAM_OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(PROGRAM_OBJS)

program.o : program.c
	$(CC) $(CFLAGS) -c program.c

clean :
	rm *.o $(PROGS) core
