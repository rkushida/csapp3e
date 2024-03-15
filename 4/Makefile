CC = gcc
CFLAGS = -Wall -Wextra

CURDIR = $(shell pwd)
SIMDIR = $(shell dirname `pwd`)/sim

all:
	@:

%.yo: %.ys
	$(SIMDIR)/misc/yas $^

4.52:
	patch -d $(SIMDIR)/seq -N -r - < $(CURDIR)/$@.patch

4.53 4.54 4.55 4.56 4.57:
	patch -d $(SIMDIR)/pipe -N -r - < $(CURDIR)/$@.patch

clean:
	find -type f -executable -delete
	rm -f *.o *.s *.yo
