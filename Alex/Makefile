CC := clang
CFLAGS ?= -g --std=c11 

test: test-alint.o alint.o
	@$(CC) $(CFLAGS) -MMD -MP -o test-alint test-alint.o alint.o

clean:
	rm -f *.o

test-alint.o: test-alint.c alint.h
	cc -g -Wall -c -o test-alint.o test-alint.c

alint.o: alint.c alint.h
	cc -g -Wall -c -o alint.o alint.c
