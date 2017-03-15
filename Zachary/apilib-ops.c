/**
 * apilib-ops.c
 *   The operator functions for the arbitrary precision integers library.
 *
 * <Insert appropriate open-source license.>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "apilib.h"

// +-----------+-----------------------------------------------------
// | Operators |
// +-----------+

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt *
api_add (APInt *a, APInt *b)
{
  //STUB
} // api_add

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt *
api_subtract (APInt *a, APInt *b)
{
  //STUB
} // api_subtract

/**
 * Multiply two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt *
api_product (APInt *a, APInt *b)
{
  //STUB
} // api_product

/**
 * Find the remainder of two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
APInt *
api_remainder (APInt *a, APInt *b)
{
  //STUB
} // api_remainder

/**
 * Find the quotient of two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
APInt *
api_quotient (APInt *a, APInt *b)
{
  //STUB
} // api_quotient
