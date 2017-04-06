# Makefile
#   A simple Makefile for our basic C project

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
test: ./AlintTest
    ./AlintTest

# Our tests
AlintTest: AlintTest.o Alint.h
    $(CC) $(.IMPSRC) $(LDLIBS) -o $(.TARGET)

# +-------------------------+----------------------------------------
# | Additional Dependencies |
# +-------------------------+

*.o: mathlib.h
