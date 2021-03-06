/** 
 * alint.c
 *   A library for storing and manipulating arbitrarily large 
 *   integers (ALInts)
 *
 * <insert appropriate FOSS license>
 */

// include standard library for NULL, malloc, etc.
#include <stdlib.h>
// include library for booleans
#include <stdbool.h>
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
  // What is this even supposed to do
  return NULL;
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
  // Wait how am I supposed to find allocated ALInts to free them
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

  // create sum structure
  ALInt * sum = (ALInt *) malloc (sizeof (ALInt));
  struct ALIntDigit * ptrNew;
  struct ALIntDigit * temp;
  bool first = true;
  
  // if we've got one negative, use subtraction method instead
  if(a->sign == 1 && b->sign == 0) {
    b->sign = 1;
    printf("+/-:  %s, %s\n", ali2str(a), ali2str(b));
    return ali_subtract(a, b);
  } else if(a->sign == 0 && b->sign == 1) {
    a->sign = 1;
    printf("-/+:  %s, %s\n", ali2str(a), ali2str(b));
    return ali_subtract(b, a);
  // if we've got two positives, we're positive
  } else if(a->sign == 1 && b->sign == 1) {
    sum->sign = 1;
    printf("+/+:  %s, %s\n", ali2str(a), ali2str(b));
  // if two negatives, we're negative
  } else {
    sum->sign = 0;
    printf("-/-:  %s, %s\n", ali2str(a), ali2str(b));
  }

  while(ptrA != NULL && ptrB != NULL) {
    // if first time around, set things up a little differently
    if(first) {
      ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
      sum->last = ptrNew;
      sum->first = ptrNew;
      ptrNew->next = NULL;
      first = false;
    } else {
      // allocate new digit at the left end of sum and assign ptrs to match
      ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
      temp = sum->first;
      sum->first = ptrNew;
      sum->first->next = temp;
      temp->prev = ptrNew;
    }

    remainder = (ptrA->value + ptrB->value) % BASE;
    // digit equals current remainder plus previous buffer
    ptrNew->value = remainder + buffer;

    // calculate buffer for next round
    buffer = (ptrA->value + ptrB->value) / BASE;

    // add one to the digit count
    sum->ndigits++;
    // move the pointers to the left
    ptrA = ptrA->prev;
    ptrB = ptrB->prev;
  }

  // deal with any remaining digits in either number
  while(ptrA != NULL) {
    ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
    // assign pointers
    temp = sum->first;
    sum->first = ptrNew;
    sum->first->next = temp;
    temp->prev = ptrNew;
    // compute value and add one to the digit count
    ptrNew->value = buffer + ptrA->value;
    sum->ndigits++;
    // move pointer to the left
    ptrA = ptrA->prev;
  } 
  while(ptrB != NULL) {
    ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
    // assign pointers
    temp = sum->first;
    sum->first = ptrNew;
    sum->first->next = temp;
    temp->prev = ptrNew;
    // compute value and add one to the digit count
    ptrNew->value = buffer + ptrB->value;
    sum->ndigits++;
    // move pointer to the left
    ptrB = ptrB->prev;
  }
  return sum;
}

/**
 * Subtract one arbitrarily large integer from another, creating a
 * newly allocated ALInt. Client is responsible for freeing any
 * memory associated with the new value using ali_free.
 */
ALInt * ali_subtract(ALInt * a, ALInt * b) {
  struct ALIntDigit * ptrA = a->last;
  struct ALIntDigit * ptrB = b->last;
  int difference = 0;

  // create sum structure
  ALInt * dif = (ALInt *) malloc (sizeof (ALInt));
  struct ALIntDigit * ptrNew;
  struct ALIntDigit * temp;
  bool first = true;
  
  // if the first number is negative, use addition method instead
  if(a->sign == 0 && b->sign == 1) {
    b->sign = 0;
    return ali_add(a, b);
  // if the second number is negative, use addition method instead
  } else if (a->sign == 1 && b->sign == 0) {
    b->sign = 1;
    return ali_add(a, b);
  // if we've got two positives, determine resulting sign
  } else if(a->sign == 1 && b->sign == 1) {
    // if a has more digits, the result will be positive
    if(a->ndigits > b->ndigits) {
      dif->sign = 1;
    // if b has more, result will be negative, and we want to switch a & b
    //   to make subtracting easier
    } else if(a->ndigits < b->ndigits) {
      dif->sign = 0;
      temp = ptrA;
      ptrA = ptrB;
      ptrB = temp;
    // if they have the same number of digits...
    } else {
      struct ALIntDigit * signPtrA = a->first;
      struct ALIntDigit * signPtrB = b->first;
      // find first instance of unequal digits
      while((signPtrA != NULL) && (signPtrA->value == signPtrB->value)) {
        signPtrA = signPtrA->next;
        signPtrB = signPtrB->next;
      }
      // if we reach the end and all digits are equal, we know we'll get zero
      if(signPtrA == NULL) {
        ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
        dif->last = ptrNew;
        dif->first = ptrNew;
        dif->sign = 1;
        dif->ndigits = 1;
        ptrNew->next = NULL;
        ptrNew->prev = NULL;
        ptrNew->value = 0;
        return dif;
      // otherwise, compare the digits we found
      } else {
        if(signPtrA->value > signPtrB->value) {
          dif->sign = 1;
        // if b is greater, result will be negative, and we want to switch a & b
        //   to make subtracting easier
        } else {
          dif->sign = 0;
          temp = ptrA;
          ptrA = ptrB;
          ptrB = temp;
        }
      }
    }
  // if two negatives, we need to switch positions
  } else {
    a->sign = 1;
    b->sign = 1;
    return ali_subtract(b, a);
  }

  while(ptrB != NULL) {
    // if first time around, set things up a little differently
    if(first) {
      ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
      dif->last = ptrNew;
      dif->first = ptrNew;
      ptrNew->next = NULL;
      first = false;
    } else {
      // allocate new digit at the left end of dif and assign ptrs to match
      ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
      temp = dif->first;
      dif->first = ptrNew;
      dif->first->next = temp;
      temp->prev = ptrNew;
    }

    // if the subtractee (ptrA) is smaller than the subtractor, borrow from the 
    //   next column
    if(ptrA->value < ptrB->value) {
      ptrA->value += BASE;
      ptrA->prev->value -= 1;
    }

    difference = ptrA->value - ptrB->value;
    // digit equals difference
    ptrNew->value = difference;

    // add one to the digit count
    dif->ndigits++;
    // move the pointers to the left
    ptrA = ptrA->prev;
    ptrB = ptrB->prev;
  }

  // deal with any remaining digits in the larger (first) number
  while(ptrA != NULL) {
    ptrNew = (struct ALIntDigit *) malloc (sizeof (struct ALIntDigit));
    // assign pointers
    temp = dif->first;
    dif->first = ptrNew;
    dif->first->next = temp;
    temp->prev = ptrNew;
    // add value and add one to the digit count
    ptrNew->value = ptrA->value;
    dif->ndigits++;
    // move pointer to the left
    ptrA = ptrA->prev;
  }

  return dif;
}

/**
 * Multiply two arbitrarily large integers together, creating a
 * newly allocated ALInt. Client is responsible for freeing any
 * memory associated with the new value using ali_free.
 */
ALInt * ali_multiply(ALInt * a, ALInt * b) {
  return NULL;
}

/**
 * Divide one arbitrarily large integer by another, returning a
 * newly allocated ALInt that is the quotient. Client is
 * responsible for freeing any memory associated with the new value
 * using ali_free.
 */
ALInt * ali_quotient(ALInt * a, ALInt * b) {
  return NULL;
}

/**
 * Divide one arbitrarily large integer by another, returning a
 * newly allocated ALInt that is the remainder. Client is
 * responsible for freeing any memory associated with the new value
 * using ali_free.
 */
ALInt * ali_remainder(ALInt * a, ALInt * b) {
  return NULL;
}



/**
 * Convert from int to ALInt, creating a newly allocated ALInt whose 
 * value is i.
 */
ALInt * int2ali (int i) {
  ALInt * a = (ALInt *) malloc (sizeof (ALInt));
  // set sign value (positive or negative)
  if(i < 0) {
    a->sign = 0;
    // if i is negative, make it not negative
    i = abs(i);
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
    // if i is negative, make it not negative
    i = abs(i);
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
    // if i is negative, make it not negative
    i = abs(i);
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
  } while(i >= 1);

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
  
  // if the number is negative, multiply by -1
  if(a->sign == 0) {
    i *= -1;
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

  // if the number is negative, multiply by -1
  if(a->sign == 0) {
    l *= -1;
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

  // if the number is negative, multiply by -1
  if(a->sign == 0) {
    d *= -1;
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
    str = strcat(str, ch);
    ptr = ptr->next;
  }

  // if the number is negative, append a (-)
  if(a->sign == 0) {
    sprintf(ch, "-");
    str = strcat(ch, str);
  }

  return str;
}


