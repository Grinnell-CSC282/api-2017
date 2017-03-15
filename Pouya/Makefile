#!/bin/bash

CC = gcc
CFLAGS = -g -Wall
LDLIBS = -L. -larray_operations #-lapi

# main method
main: api

# *.o files
*.o: api.h array_operations.h


# libraries
libarray_operations.a: array_operations_addLast.o array_operations_free.o \
	array_operations_init.o api_int2api.o api_free.o api_api2int.o
	ar -rv $@ $^

#libapi.a: api_int2api.o api_free.o api_api2int.o api.h
#	ar -rv $@ $^ $(LDLIBS)

api: api.c libarray_operations.a #libapi.a
	$(CC) $(CCFLAGS) $< $(LDLIBS) -o $@
# clean up
clean:
	rm -f *.o
