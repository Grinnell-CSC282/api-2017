/**
 * alilib-init.c
 *    Initialization functions for arbitrarily long integers for alilib.
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
// | Procedure  |
// +------------+

/**
 * Creates a new ALInt from values for that integer.
 */
ALInt * 
alint_init(int new_ndigits, int new_sign, int new_digits[]) 
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