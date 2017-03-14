/**
 * alilib-helpers.c
 *    Helper functions for operations on arbitrarily long integers for alilib.
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
 * Determine whether the signs of a and b are the same or different.
 * Returns an integer indicating --
 * 0: +a + b
 * 1: +a - b
 * 2: -a + b
 * 3: -a - b
 */
int 
find_signs(ALInt *a, ALInt *b)
{
	int flag = 0;
	// Determine if adding or subtracting
	if (a->sign == b->sign)
	{
		if (a->sign == 1)
		{
			flag = 0;
		}
		else 
		{
			flag = 3;
		}
	}
	else
	{
		if (a->sign == 1)
		{
			flag = 1;
		}
		else 
		{
			flag = 2;
		}
	}
	return flag;
}

/**
 * Finds the bigger of two ALInts (in terms of length) and returns it
 */
ALInt *
find_bigger(ALInt *a, ALInt *b)
{
	// Find the bigger number (in terms of length)
	if (a->ndigits > b->ndigits)
	{
		return a;
	}
	else
	{
		return b;
	}
}

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
}

/**
 * Shifts an array of digits to get rid of any leading zeros and
 * returns a new array without them
 */
int *
remove_leading_zeroes(int array[], int arr_len)
{
	int new_len = arr_len;
	// Shift to get rid of any leading zeros
	while (array[0] == 0)
	{
		for (int i = 1; i < arr_len; i++) 
		{
			array[i-1] = array[i];
			new_len--;
		}
	}
	return array;
}