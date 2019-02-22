CC=gcc
CFLAGS=-I.
DEPS = prog.h

%.o: %.c %(DEPS)
	$(CC) -c -o -wall -g $@ $< $(CFLAGS)

prog: prog.o
	$(CC) -o prog prog.o

