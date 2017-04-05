/**
 * apilib.h
 *   A library for arbitrary precision integers.
 *
 * <Insert appropriate open-source license.>
 */

#ifndef __APILIB_H_
#define __APILIB_H__

// +---------+-------------------------------------------------------
// | Structs |
// +---------+

typedef struct ap_int {
  int stub;
} APInt;

// +-----------+---------------------------------------------
// | Constants |
// +-----------+

APInt* API_ZERO;
APInt* API_ONE;
APInt* API_TWO;
APInt* API_NEG_ONE;
APInt* API_NEG_TWO;

// +-------------------+---------------------------------------------
// | Library Functions |
// +-------------------+

/**
 * Initializes constants for API library. Must be called before library
 * is used.
 */
void api_init();

/**
 * Removes constants for API library. Should be called before program
 * is exited.
 */
void api_cleanup();

// +--------------+---------------------------------------------------
// | Constructors |
// +--------------+

/**
  * Create a newly allocated ALInt whose value is i.
  */
APInt * int2api (int i);

/**
  * Create a newly allocated ALInt whose value is parsed from str
  */
APInt * str2api (char* str);

/**
  * Create a newly allocated ALInt whose value is l.
  */
APInt * long2api (long l);

/**
  * Create a newly allocated ALInt whose value is d.
  */
APInt * double2api (double d);

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void api_free (APInt *i);

// +-------------+---------------------------------------------------
// | Conversions |
// +-------------+

/**
  * Create an int whose value is min(INT_MAX, api)
  */
int api2int (APInt * api);

/**
  * Create a string representing api
  */
char* api2str (APInt * api);

/**
  * Create a long whose value is min(LONG_MAX, api)
  */
long api2long (APInt * api);

/**
  * Create a double whose value is min(INT_MAX, api)
  */
double api2double (APInt * api);

// +-----------+-----------------------------------------------------
// | Operators |
// +-----------+

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt * api_add (APInt *a, APInt *b);

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt * api_subtract (APInt *a, APInt *b);

/**
 * Multiply two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt * api_product (APInt *a, APInt *b);


/**
 * Find the remainder of two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
APInt * api_remainder (APInt *a, APInt *b);

/**
 * Find the quotient of two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
APInt * api_quotient (APInt *a, APInt *b);

/**
 * Compare two API values. Return -1 if the first is less than the 
 * second, 0 if they are the same, and 1 if the first is greater than 
 * the second
 */
int * api_cmp (APInt *a, APInt *b);


#endif // __APILIB_H_
