#!/bin/bash

CC = gcc --std=c11
CFLAGS = -g -Wall
LDLIBS = -L. -lapi -larray_operations

# main method
main: api

# *.o files
*.o: api.h array_operations.h


# libraries
libarray_operations.a: array_operations_addLast.o array_operations_free.o \
	array_operations_init.o
	rm -f $@
	ar rv $@ $^

libapi.a: api_int_trans.o api_free.o  api_str_trans.o api_operands.o
	rm -f $@
	ar rv $@ $^

api: api.c libapi.a libarray_operations.a
	$(CC) $(CCFLAGS) $< $(LDLIBS) -o $@
# clean up
clean:
	rm -f *.o *.c~ api
