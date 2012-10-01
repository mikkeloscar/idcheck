# VERSION = $(shell git describe --tags)
VERSION=0.1

CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -ggdb

NAME = idcheck
OBJS = idcheck.o main.o

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

idcheck.o: idcheck.c
	$(CC) $(CFLAGS) -c idcheck.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *o
	rm -f $(NAME)

.PHONY: clean
