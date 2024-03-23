CC = gcc
CFLAGS = -Wall -Wextra

all:
	@:

5.14 5.15 5.16: %: %.o inner4.o vec.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	find -type f -executable -delete
	rm -f *.o *.s
