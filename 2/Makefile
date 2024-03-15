CC = gcc
CFLAGS = -Wall -Wextra

all:
	@:

2.55 2.56: %: %.o show_bytes.o
	$(CC) $(CFLAGS) -o $@ $^

2.90 2.92 2.93 2.94 2.95 2.96 2.97: %: %.o float.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	find -type f -executable -delete
	rm -f *.o *.s
