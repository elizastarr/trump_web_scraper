CC=gcc
CFLAGS=-c -Wall -g 

all: hw4

hw4: web.o hw4.o
	$(CC) web.o hw4.o -o hw4 -lpthread -lcurl

web.o: web.c
	$(CC) $(CFLAGS) web.c

hw4.o: hw4.c
	$(CC) $(CFLAGS) hw4.c

clean:
	/bin/rm -f hw4 *.o *.gz

run:
	./hw4 url.txt

tarball:
	tar -cvzf <your last name>.tar.gz *

