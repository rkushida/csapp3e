CC = gcc
CFLAGS = -Wall -Wextra

all:
	@:

5.14 5.15: %: %.o vec.o
	$(CC) $(CFLAGS) -o $@ $^
