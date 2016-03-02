all: mytest

#compiler
CC = gcc

#debug
CFLAGS = -Wall -O1 -g

#release
#CFLAGS = -Wall -O1

LIBS = -L. -lmy

mytest: mytest.c mylib.h libmy.a foo.h bar.h baz.h
	$(CC) $(CFLAGS) -o mytest mytest.c $(LIBS) 

libmy.a: foo.c bar.c baz.c
	$(CC) $(CFLAGS) -c foo.c bar.c baz.c
	ar crv libmy.a foo.o bar.o baz.o

clean:
	-rm mytest

reset:
	-rm *.o mytest libmy.a
