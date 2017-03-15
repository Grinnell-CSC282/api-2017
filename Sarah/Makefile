# Makefile
#   Makefile for a library handling abitrarily long integers 

# +-----------+------------------------------------------------------
# | Variables |
# +-----------+

CC = gcc
CFLAGS = -Wall -g
LDLIBS = -L. -lalilib

# More readable versions of the automatic variables
.TARGET = $@
.IMPSRC = $<
.ALLSRC = $^

# +---------+--------------------------------------------------------
# | Targets |
# +---------+

# Our tests
test: ./test-ali
	./test-ali

# The library
libalilib.a: alilib-operations.o alilib-2ali.o alilib-ali2.o alilib-helpers.o alilib-standard.o
	ar -rv $(.TARGET) $(.ALLSRC)

# Our application
ali: ali.o libalilib.a
	$(CC) $(.IMPSRC) $(LDLIBS) -o $(.TARGET)

# Our tests
test-ali: test-ali.o libalilib.a
	$(CC) $(.IMPSRC) $(LDLIBS) -o $(.TARGET)

# Clean up
clean:
	rm -f *.o

distclean: clean
	rm -f libalilib.a
	rm -f ali
	rm -f test-ali

# +-------------------------+----------------------------------------
# | Additional Dependencies |
# +-------------------------+

*.o: alilib.h