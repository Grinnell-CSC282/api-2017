/** 
 * 	alilib.h
 *  	a library that handles arbitrarily large integers 
 *  	
 * Function declarations by Sam Rebelsky 
 * http://www.cs.grinnell.edu/~rebelsky/musings/cnix-alint-library
 *
 * <insert appropritate open-source license>
 */

#ifndef __ALILIB_H__
#define __ALILIB_H__

// +------------+----------------------------------------------------
// | Definition |
// +------------+

struct ALInt 
  {
    int ndigits;
    int sign;       // 1 for positive, -1 for negative
    int digits[];   // Each represents one base-16 digit
  };
typedef struct ALInt ALInt;

// +-----------+-----------------------------------------------------
// | Constants |
// +-----------+

#define LONG_MAX 100000.0
#define LONG_MIN 100000.0

#define INT_MAX 100000
#define INT_MIN 100000

#define DOUBLE_MAX 100000.0
#define DOUBLE_MIN 100000.0

// +------------+----------------------------------------------------
// | Procedures |
// +------------+

/**
 * Initializes the library. The client must run this procedure before
 * using the library.
 */
void ali_init();

/**
 * Cleans up all memory that may have been allocated. The client must run
 * this procedure when they are finished using the library.
 */
void ali_cleanup();

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void ali_free (ALInt *i); 

/**
 * Creates a new ALInt from values for that integer.
 */
ALInt * ali_new(int new_ndigits, int new_sign, int new_digits[]);

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_add (ALInt *a, ALInt *b);

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_subtract (ALInt *a, ALInt *b);

/**
 * Mutiply two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_multiply (ALInt *a, ALInt *b);

/**
 * Find the quotient two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
ALInt * ali_quotient (ALInt *a, ALInt *b);

/**
 * Find the remainder two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
ALInt * ali_remainder (ALInt *a, ALInt *b);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * int2ali (int i);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * str2ali (char * s);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * long2ali (long l);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * double2ali (double d);

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
long ali2long (ALInt *a);

/**
 * Find the double that corresponds to a.  If a > DOUBLE_MAX,
 * returns DOUBLE_MAX.  If a < DOUBLE_MIN, returns DOUBLE_MIN.
 */
double ali2double (ALInt *a);

/**
 * Find the int that corresponds to a.  If a > INT_MAX,
 * returns INT_MAX.  If a < INT_MIN, returns INT_MIN.
 */
int ali2int (ALInt *a);

/**
 * Convert a to string representation.  Returns a newly-allocated
 * string.
 */
char * ali2str (ALInt *a);

/**
 * Determine whether the signs of a and b are the same or different.
 * Returns an integer indicating --
 * 0: +a + b
 * 1: +a - b
 * 2: -a + b
 * 3: -a - b
 */
int find_signs(ALInt *a, ALInt *b);

/**
 * Finds the bigger of two ALInts (by length) and returns it.
 */
ALInt * find_bigger(ALInt *a, ALInt *b);

/**
 * Shifts an array of digits to get rid of any leading zeros and
 * returns a new array without them
 */
int * remove_leading_zeroes(int array[], int arr_len);

#endif // __ALILIB_H__