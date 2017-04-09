/** 
 * alint.c
 *   A library for storing and manipulating arbitrarily large 
 *   integers (ALInts)
 *
 * <insert appropriate FOSS license>
 */

// include standard library for NULL, malloc, etc.
#include <stdlib.h>
// include i/o library
#include <stdio.h>
// include string library
#include <string.h>
// include the math library
#include <math.h>
// include limits like INT_MAX and LONG_MIN
#include <limits.h>
// include header file
#include "alint.h"


/**
 * Initialize an arbitrarily large integer value. Client must call
 * this procedure before using the library.
 */
ALInt * ali_init() {
  // STUB
}

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void ali_free(ALInt * i) {
  struct ALIntDigit * ptr = i->first;

  // free each digit
  while(ptr != NULL) {
    struct ALIntDigit * temp = ptr;
    ptr = ptr->next;
    free(temp);
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

/* !!! HERE !!! says it can't access ptrB->value on 3rd run through? */
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
ALInt * int2ali (int i) {
  ALInt * a = (ALInt *) malloc (sizeof (ALInt));
  // set sign value (positive or negative)
  if(i < 0) {
    a->sign = 0;
  }
  else {
    a->sign = 1;
  }
  // set number of digits
  a->ndigits = (int) log10((double) i) + 1;

  // create ALIntDigits and set next pointers
  short digit;
  struct ALIntDigit * cur;
  // the rightmost next pointer will be null
  struct ALIntDigit * next = NULL;
  do {
    digit = i % 10;

    cur = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
    // set value and next ptr
    cur->value = digit;
    cur->next = next;
    // prepare for next round
    next = cur;

    // divide by 10 to move left
    i /= 10;
  } while(i != 0);

  // set first pointer
  a->first = cur;
  // set prev pointers
  cur->prev = NULL;
  struct ALIntDigit * temp;
  while(cur->next != NULL) {
    temp = cur;
    cur = cur->next;
    cur->prev = temp;
  }
  // set last pointer
  a->last = cur;

  return a;
}

/**
 * Convert from long to ALInt, creating a newly allocated ALInt 
 * whose value is i.
 */
ALInt * long2ali (long i) {
  ALInt * a = (ALInt *) malloc (sizeof (ALInt));
  // set sign value (positive or negative)
  if(i < 0) {
    a->sign = 0;
  }
  else {
    a->sign = 1;
  }
  // set number of digits
  a->ndigits = (int) log10((double) i) + 1;

  // create ALIntDigits and set next pointers
  short digit;
  struct ALIntDigit * cur;
  // the rightmost next pointer will be null
  struct ALIntDigit * next = NULL;
  do {
    digit = i % 10;

    cur = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
    // set value and next ptr
    cur->value = digit;
    cur->next = next;
    // prepare for next round
    next = cur;

    // divide by 10 to move left
    i /= 10;
  } while(i != 0);

  // set first pointer
  a->first = cur;
  // set prev pointers
  cur->prev = NULL;
  struct ALIntDigit * temp;
  while(cur->next != NULL) {
    temp = cur;
    cur = cur->next;
    cur->prev = temp;
  }
  // set last pointer
  a->last = cur;

  return a;
}

/**
 * Convert from double to ALInt, creating a newly allocated ALInt 
 * whose value is i.
 */
ALInt * double2ali (double i) {
  ALInt * a = (ALInt *) malloc (sizeof (ALInt));
  // set sign value (positive or negative)
  if(i < 0) {
    a->sign = 0;
  }
  else {
    a->sign = 1;
  }
  // set number of digits
  a->ndigits = (int) log10(i) + 1;

  // create ALIntDigits and set next pointers
  short digit;
  struct ALIntDigit * cur;
  // the rightmost next pointer will be null
  struct ALIntDigit * next = NULL;
  do {
    digit = ((int) i) % 10;

    cur = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
    // set value and next ptr
    cur->value = digit;
    cur->next = next;
    // prepare for next round
    next = cur;

    // divide by 10 to move left
    i /= 10;
  } while(i != 0);

  // set first pointer
  a->first = cur;
  // set prev pointers
  cur->prev = NULL;
  struct ALIntDigit * temp;
  while(cur->next != NULL) {
    temp = cur;
    cur = cur->next;
    cur->prev = temp;
  }
  // set last pointer
  a->last = cur;

  return a;
}

/**
 * Convert from string to ALInt, creating a newly allocated ALInt 
 * whose value is i.
 */
ALInt * str2ali (char * i) {
  int j = atoi(i);
  return int2ali(j);
}



/**
 * Find the int that corresponds to a. If a > INT_MAX, returns
 * INT_MAX. If a < INT_MIN, returns INT_MIN.
 * (Yes I could just do this with ali2str and then atoi but that feels
 *   like cheating somehow.)
 * (It wasn't cheating for str2ali because I say so.)
 */
int ali2int (ALInt * a) {
  int i = 0;
  double digit = a->ndigits - 1;

  /* iterate through digits, multiplying each by the appropriate power of 10
     and then adding to i */
  struct ALIntDigit * ptr = a->first;
  while(ptr != NULL && i < INT_MAX && i > INT_MIN) {
    i += ptr->value * pow(10, digit);
    ptr = ptr->next;
    digit -= 1;
  }

  // return i or an upper/lower limit
  if(i < INT_MIN) {
    return (int) INT_MIN;
  }
  else if(i > INT_MAX) {
    return (int) INT_MAX;
  }
  else {
    return i;
  }
}

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
long ali2long (ALInt * a) {
  long l = 0;
  double digit = a->ndigits - 1;

  /* iterate through digits, multiplying each by the appropriate power of 10
     and then adding to l */
  struct ALIntDigit * ptr = a->first;
  while(ptr != NULL && l < LONG_MAX && l > LONG_MIN) {
    l += ptr->value * pow(10, digit);
    ptr = ptr->next;
    digit -= 1;
  }

  // return l or an upper/lower limit
  if(l < LONG_MIN) {
    return (long) LONG_MIN;
  }
  else if(l > LONG_MAX) {
    return (long) LONG_MAX;
  }
  else {
    return l;
  }
}

/**
 * Find the double that corresponds to a. If a > DOUBLE_MAX, returns
 * DOUBLE_MAX. If a < DOUBLE_MIN, returns DOUBLE_MIN.
 */
double ali2double (ALInt * a) {
  double d = 0;
  double digit = a->ndigits - 1;

  /* iterate through digits, multiplying each by the appropriate power of 10
     and then adding to d */
  struct ALIntDigit * ptr = a->first;
  while(ptr != NULL && d < DOUBLE_MAX && d > DOUBLE_MIN) {
    d += ptr->value * pow(10, digit);
    ptr = ptr->next;
    digit -= 1;
  }

  // return d or an upper/lower limit
  if(d < DOUBLE_MIN) {
    return (double) DOUBLE_MIN;
  }
  else if(d > DOUBLE_MAX) {
    return (double) DOUBLE_MAX;
  }
  else {
    return d;
  }
}

/**
 * Convert a to string representation.  Returns a newly-allocated
 * string.
 */
char * ali2str (ALInt * a) {
  char * str = (char *) malloc (sizeof (char) * a->ndigits);
  char * ch = (char *) malloc (sizeof (char));

  // iterate through digits, storing each as char* and then adding to str
  struct ALIntDigit * ptr = a->first;
  while(ptr != NULL) {
    // convert digit to char*
    sprintf(ch, "%hu", ptr->value);
    // append to str
    strcat(str, ch);
    ptr = ptr->next;
  }

  return str;
}


