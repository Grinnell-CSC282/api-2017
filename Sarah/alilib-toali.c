/**
 * alilib-toali.c
 *    Converts an integer to an arbitrarily long integer for alilib.
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
  * Create a newly allocated ALInt whose value is i.
  */
ALInt * 
int2ali (int i) 
{
	// Determine the sign of the new integer
	int new_sign = 0;
	if (i < 0)
	{
		new_sign = -1;
	}
	else 
	{
		new_sign = 1;
	}
	// Find the number of digits of the new integer
	int new_ndigits = 0;
	int n = i;
	while (n != 0)
	{
		n /= 10;
		new_ndigits++;
	}
	// Put the integer into the array
	// Declare a new array for the new integer
	int new_digits[new_ndigits];
	if (new_ndigits != 0)
	{
		n = i;
		int j = 0;
		while (n != 0)
		{
			new_digits[j] = n % 10;
			n /= 10;
			j++;
		}
	}
	// Return the new struct
	return alint_init (new_ndigits, new_sign, new_digits);
}