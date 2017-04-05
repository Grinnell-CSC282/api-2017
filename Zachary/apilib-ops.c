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
  // Should be straightforward no matter what the implementation
  // Sign might be a pain. Helper functions for unsigned addition & subtraction?
  // Use API_CMP to cheat at finding bigger numbers for subtraction
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
  // Signs are a mess here
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
  // Signs easy to deal with
  // product is easy with a binary representation - just bitshift
  // Helper function to bitshift across gaps?
  // Keep a running total for the sum?
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
  // Binary search plus double helper function and memoizing?
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
  // Remainder + subtraction
} // api_quotient
