# alint/Makefile
#   The Makefile for the arbitrarily large integer project

# +----------+-------------------------------------------------------
# | Settings |
# +----------+

# +------------------+-----------------------------------------------
# | Standard Targets |
# +------------------+

alint.o: alint.c
	cc -g -Wall  -c -o alint.o alint.c -lm
alint: alint.o
	cc -o alint alint.o -lm
test: test.c alint.c
	cc -g -o test test.c -lm

# +--------------------+---------------------------------------------
# | Additional Targets |
# +--------------------+

alint.test: alint.c test.c
	cc -g -Wall -o alint.test alint.c test.c -lm
