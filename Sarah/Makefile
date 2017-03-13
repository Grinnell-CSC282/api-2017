# Makefile
#   Makefile for a library handling abitrarily long integers 

# +-----------+------------------------------------------------------
# | Variables |
# +-----------+

CC = gcc
CFLAGS = -Wall -g
LDLIBS = -L. -lmathlib

# More readable versions of the automatic variables
.TARGET = $@
.IMPSRC = $<
.ALLSRC = $^

# +---------+--------------------------------------------------------
# | Targets |
# +---------+

# Our tests
test: ./test-lib
    ./test-lib

# The library
ali-lib.a: mathlib-gcd.o mathlib-str2long.o
    ar -rv $(.TARGET) $(.ALLSRC)

# Our application
ali: ali.o ali-lib.a
    $(CC) $(.IMPSRC) $(LDLIBS) -o $(.TARGET)

# Our tests
test-ali: test-ali.o ali-lib.a
    $(CC) $(.IMPSRC) $(LDLIBS) -o $(.TARGET)

# +-------------------------+----------------------------------------
# | Additional Dependencies |
# +-------------------------+

*.o: mathlib.h