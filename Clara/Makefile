# alint/Makefile
#   The Makefile for the arbitrarily large integer project

# +----------+-------------------------------------------------------
# | Settings |
# +----------+

# +------------------+-----------------------------------------------
# | Standard Targets |
# +------------------+

alint.o: alint.c
	cc -g -Wall  -c -o alint.o alint.c
alint: alint.o
	cc -o alint alint.o
test: test.c alint.c
	cc -o test test.c -lm

# +--------------------+---------------------------------------------
# | Additional Targets |
# +--------------------+

alint.test: alint.c test.c
	cc -g -Wall -o alint.test alint.c test.c -lm
