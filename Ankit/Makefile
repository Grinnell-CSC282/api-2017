# alint/Makefile
#   The Makefile for the arbitrarily large integer project

# +----------+-------------------------------------------------------
# | Settings |
# +----------+
CC = gcc
CFLAGS = -Wall -g
LDLIBS = -L. -lali

# For readability
.TARGET = $@
.IMPSRC = $<
.ALLSRC = $^

# +------------------+-----------------------------------------------
# | Standard Targets |
# +------------------+
all: ; #TODO Target all doesn't exist

clean:
	-rm -r *.o *.a test-ali

# +--------------------+---------------------------------------------
# | Additional Targets |
# +--------------------+

libali.a: ali_core.o ali_arith.o ali_conv.o
	ar -rv $(.TARGET) $(.ALLSRC)

test-ali: test-ali.o libali.a
	$(CC) $(.IMPSRC) $(LDLIBS) -o $(.TARGET)

test: ./test-ali
	./test-ali
