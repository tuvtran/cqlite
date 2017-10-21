# Tu Tran - Cloning SQLite for fun
# Created at 3:45 AM October 21st, 2017

CC=gcc
CFLAGS=-g -Wall -std=c99

all: clean cqlite

cqlite: cqlite.c cqlite.h
		$(CC) $(CFLAGS) -o db cqlite.c

clean:
		$(RM) -rf db *.dSYM