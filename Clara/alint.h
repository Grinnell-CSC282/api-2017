/** 
 * alint.h
 *   A library for storing and manipulating arbitrarily large 
 *   integers (ALInts)
 *
 * <insert appropriate FOSS license>
 */

#ifndef __ALINT_H__
#define __ALINT_H__

// +-------------+---------------------------------------------------
// | Definitions |
// +-------------+

/**
 * Store all ALInt info in a linked list.
 */
struct ALIntDigit {
  unsigned short value;
  struct ALIntDigit * prev;
  struct ALIntDigit * next;
};
typedef struct ALInt {
  unsigned short sign;
  int ndigits;
  struct ALIntDigit * first;
  struct ALIntDigit * last;
} ALInt;


// +-----------+-----------------------------------------------------
// | Constants |
// +-----------+

#define BASE 16

#define INT_MAX 1000000
#define INT_MIN 1000000

#define LONG_MAX 1000000
#define LONG_MIN 1000000

#define DOUBLE_MAX 1000000.0
#define DOUBLE_MIN 1000000.0


// +------------+----------------------------------------------------
// | Procedures |
// +------------+

// ---------------------MEMORY MANAGEMENT----------------------------
/**
 * Initialize an arbitrarily large integer value. Client must call
 * this procedure before using the library.
 */
ALInt * ali_init ();

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void ali_free (ALInt * i);

/**
 * Clean up all allocated memory. Client is required to run this 
 * procedure when they finish their program.
 */
void ali_cleanup ();

// ---------------------OPERATIONS-----------------------------------
/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_add (ALInt * a, ALInt * b);

/**
 * Subtract one arbitrarily large integer from another, creating a
 * newly allocated ALInt. Client is responsible for freeing any
 * memory associated with the new value using ali_free.
 */
ALInt * ali_subtract (ALInt * a, ALInt * b);

/**
 * Multiply two arbitrarily large integers together, creating a
 * newly allocated ALInt. Client is responsible for freeing any
 * memory associated with the new value using ali_free.
 */
ALInt * ali_multiply (ALInt * a, ALInt * b);

/**
 * Divide one arbitrarily large integer by another, returning a
 * newly allocated ALInt that is the quotient. Client is
 * responsible for freeing any memory associated with the new value
 * using ali_free.
 */
ALInt * ali_quotient (ALInt * a, ALInt * b);

/**
 * Divide one arbitrarily large integer by another, returning a
 * newly allocated ALInt that is the remainder. Client is
 * responsible for freeing any memory associated with the new value
 * using ali_free.
 */
ALInt * ali_remainder (ALInt * a, ALInt * b);

// ---------------------CONVERSIONS TO ALINT-------------------------
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

// ---------------------CONVERSIONS FROM ALINT-----------------------
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

#endif // __ALINT_H__

