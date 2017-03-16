/**
 * apilib-ctors.c
 *   The constructor functions for the arbitrary precision integers library.
 *
 * <Insert appropriate open-source license.>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "apilib.h"

// +--------------+---------------------------------------------------
// | Constructors |
// +--------------+

/**
  * Create a newly allocated ALInt whose value is i.
  */
APInt *
int2api (int i)
{
  // STUB
} // int2api

/**
  * Create a newly allocated ALInt whose value is parsed from str
  */
APInt *
str2api (char* str)
{
  // STUB
} // str2api

/**
  * Create a newly allocated ALInt whose value is l.
  */
APInt *
long2api (long l)
{
  // STUB
} // long2api

/**
  * Create a newly allocated ALInt whose value is d.
  */
APInt *
double2api (double d)
{
  // STUB
} // double2api

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void
api_free (APInt *i)
{
  // STUB
} // api_free
