CC = gcc
CFLAGS = -Wall -Wextra

all:
	@:

5.14 5.15: %: %.o vec.o
	$(CC) $(CFLAGS) -o $@ $^

mountain: mountain.o fcyc2.o clock.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	find -type f -executable -delete
	rm -f *.o *.s
