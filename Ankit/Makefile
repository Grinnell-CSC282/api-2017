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
clean:
	-rm -r *.o *.a test-ali

# +--------------------+---------------------------------------------
# | Additional Targets |
# +--------------------+

libali.a: ali.o
	ar -rv $(.TARGET) $(.ALLSRC)

test-ali: test-ali.o libali.a
	$(CC) $(.IMPSRC) $(LDLIBS) -o $(.TARGET)

test: ./test-ali
	./test-ali
