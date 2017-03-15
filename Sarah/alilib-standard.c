/**
 * alilib-standard.c
 *    Standard and necessary procedures for alilib.
 *
 * <insert appropriate open source license>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "alilib.h"

// +------------+----------------------------------------------------
// | Procedures |
// +------------+

/**
 * Initializes the library
 */
void 
ali_init()
{

} // ali_init

/**
 * Cleans up all memory that may have been allocated.
 */
void 
ali_cleanup()
{

} // ali_cleanup

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void 
ali_free (ALInt *i)
{
	free (i->digits);
	free (i);
} // ali_free

/**
 * Creates a new ALInt from values for that integer.
 */
ALInt * 
ali_new(int new_ndigits, int new_sign, int new_digits[]) 
{
	// Declare a new arbitrarily long integer
	ALInt * newALInt = (ALInt *) malloc (sizeof (ALInt));
	// Assigning the values of the new integer to the struct	
	newALInt->ndigits = new_ndigits;
	newALInt->sign = new_sign;
	memcpy(newALInt->digits, new_digits, new_ndigits * sizeof (int));
	// Return the new struct
	return newALInt;
} // ali_init