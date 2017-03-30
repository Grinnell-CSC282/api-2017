/** 
 * alint.c
 *   A library for storing and manipulating arbitrarily large 
 *   integers (ALInts)
 *
 * <insert appropriate FOSS license>
 */

#include <stdlib.h>
#include "alint.h"

/**
 * Initialize an arbitrarily large integer value. Client must call
 * this procedure before using the library.
 */
ALInt * ali_init() {
  ALInt * a = (ALInt *) malloc (sizeof (ALInt));
  a->sign = 1;
  a->ndigits = 0;
  a->first = NULL;
  a->last = NULL;
  return a;
}

/**
 * Create a new arbitrarily large integer. Returns pointer.
 */
ALInt * ali_new(unsigned short value, unsigned short sign, unsigned int ndigits) {
  ALInt * a = (ALInt *) malloc (sizeof (ALInt));
  a->sign = sign;
  a->ndigits = ndigits;

  struct ALIntDigit * d = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
  d->value = value;
  d->prev = NULL;
  d->next = NULL;

  a->first = d;
  a->last = d;
  return a;
}

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void ali_free(ALInt * i) {
  struct ALIntDigit * ptr = i->first;

  while(ptr != NULL) {
    struct ALIntDigit * temp = ptr->next;
    free(ptr);
    ptr = temp;
  }
  free(i);
}

/**
 * Clean up all allocated memory. Client is required to run this 
 * procedure when they finish their program.
 */
void ali_cleanup() {
  // STUB
}


/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_add(ALInt * a, ALInt * b) {
  struct ALIntDigit * ptrA = a->last;
  struct ALIntDigit * ptrB = b->last;
  int remainder = 0;
  int buffer = 0;

  ALInt * sum = ali_init();
  struct ALIntDigit * ptrNew = NULL;
  sum->last = ptrNew;
  
  while(ptrA != NULL && ptrB != NULL) {
    // allocate new digit at the left end of sum and move first ptr to match
    ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
    sum->first = ptrNew;

    remainder = (ptrA->value + ptrB->value) % BASE;
    // digit equals current remainder plus previous buffer
    ptrNew->value = remainder + buffer;

    // calculate buffer for next round
    buffer = (ptrA->value + ptrB->value) / BASE;

    sum->ndigits++;
    // move the pointers to the left
    ptrA = ptrA->prev;
    ptrB = ptrB->prev;
  }
  return sum;
}

/**
 * Subtract one arbitrarily large integer from another, creating a
 * newly allocated ALInt. Client is responsible for freeing any
 * memory associated with the new value using ali_free.
 */
ALInt * ali_subtract(ALInt * a, ALInt * b);

/**
 * Multiply two arbitrarily large integers together, creating a
 * newly allocated ALInt. Client is responsible for freeing any
 * memory associated with the new value using ali_free.
 */
ALInt * ali_multiply(ALInt * a, ALInt * b);

/**
 * Divide one arbitrarily large integer by another, returning a
 * newly allocated ALInt that is the quotient. Client is
 * responsible for freeing any memory associated with the new value
 * using ali_free.
 */
ALInt * ali_quotient(ALInt * a, ALInt * b);

/**
 * Divide one arbitrarily large integer by another, returning a
 * newly allocated ALInt that is the remainder. Client is
 * responsible for freeing any memory associated with the new value
 * using ali_free.
 */
ALInt * ali_remainder(ALInt * a, ALInt * b);


/**
 * Convert from int to ALInt, creating a newly allocated ALInt whose 
 * value is i.
 */
ALInt * int2ali (int i);

/**
 * Convert from long to ALInt, creating a newly allocated ALInt 
 * whose value is i.
 */
ALInt * long2ali (long i);

/**
 * Convert from double to ALInt, creating a newly allocated ALInt 
 * whose value is i.
 */
ALInt * double2ali (double i);

/**
 * Convert from string to ALInt, creating a newly allocated ALInt 
 * whose value is i.
 */
ALInt * str2ali (char * i);


/**
 * Find the int that corresponds to a. If a > INT_MAX, returns
 * INT_MAX. If a < INT_MIN, returns INT_MIN.
 */
int ali2int (ALInt * a);

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
long ali2long (ALInt * a);

/**
 * Find the double that corresponds to a. If a > DOUBLE_MAX, returns
 * DOUBLE_MAX. If a < DOUBLE_MIN, returns DOUBLE_MIN.
 */
double ali2double (ALInt * a);

/**
 * Convert a to string representation.  Returns a newly-allocated
 * string.
 */
char * ali2str (ALInt * a);


