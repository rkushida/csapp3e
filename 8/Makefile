CC = gcc
CFLAGS = -Wall -Wextra

all:
	@:

8.22: %: %.o csapp.o pause exit
	$(CC) $(CFLAGS) -o $@ $< csapp.o

csapp.o: csapp.c
	$(CC) -c -o $@ $^

8.20 8.24 8.25 8.26 pause exit foo: %: %.o csapp.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	find -type f -executable -delete
	rm -f *.o *.s
