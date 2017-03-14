#!/bin/bash

CC = gcc
CFLAGS = -g -Wall
LDLIBS = -L. -larray_operations

# main method
main: api

# *.o files
*.o: api.h array_operations.h

# libraries
#api.a:
#	ar -rv $@ $^

libarray_operations.a: array_operations_addLast.o array_operations_free.o array_operations_init.o array_operations_ensure.o
	ar -rv $@ $^

api: api.c libarray_operations.a
	$(CC) $(CCFLAGS) $< $(LDLIBS) -o $@
# clean up
clean:
	rm -f *.o
