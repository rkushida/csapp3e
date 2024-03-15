CC = gcc
CFLAGS = -Wall -Wextra

all:
	@:

3.73 3.74: %: %.o find_range.o float.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	find -type f -executable -delete
	rm -f *.o *.s
