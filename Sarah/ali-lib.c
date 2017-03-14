/**
 * ali-lib.c
 *   Library to handle standard operations on arbitrarily long integers
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
#include "ali-lib.h"

// +------------+----------------------------------------------------
// | Procedures |
// +------------+

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * 
ali_add (ALInt *a, ALInt *b)
{
	int new_ndigits = find_bigger (a, b)->ndigits;
	int flag = find_signs (a, b);
	int new_sign = 0;
	int new_digits[new_ndigits * 2];

	// If subtracting instead of adding then go to ali_subtract
	if (flag == 1)
	{
		ali_subtract (a, b);
	}
	else if (flag == 2)
	{
		ali_subtract (b, a);
	}
	// Otherwise, add
	else
	{
		if (flag == 4)
		{
			new_sign = -1;
		}
		else 
		{
			new_sign = 1;
		}
		int carry = 0;
		// Add the integers together
		for (int i = new_ndigits - 1; i >= 0; i--)
		{
			int sum = a->digits[i] + b->digits[i];
			// Check for carry over in addition
			if (sum > 9) 
			{
				carry += sum % 10;
				sum = sum - carry;
			}
			// Setting new value in array of digits
			new_digits[i] = sum + carry;
			if (new_digits[i] > 9)
			{
				carry = new_digits[i] % 10;
				new_digits[i] = new_digits[i] - carry;
			}
			else
			{
				carry = 0;
			}
		}
	}

	// Return the new struct
	return alint_init (new_ndigits, new_sign, 
			remove_leading_zeroes(new_digits, new_ndigits * 2));
}

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * 
ali_subtract (ALInt *a, ALInt *b)
{
	int new_ndigits = find_bigger (a, b)->ndigits;
	int flag = find_signs (a, b);
	int new_sign = 0;
	int new_digits[new_ndigits];

	// If adding instead of subtracting then go to ali_add
	if (flag == 0 || flag == 4)
	{
		ali_add (a, b);
	}
	else 
	{
		int carry = 0;
		// Subtract the integers from one another
		for (int i = new_ndigits - 1; i >= 0; i--)
		{
			int diff = a->digits[i] - b->digits[i];
			// Check for carry over in subtraction
			if (diff < a->digits[i]) 
			{
				carry += diff % 10;
				diff = diff - carry;
			}
			// Setting new value in array of digits
			new_digits[i] = diff + carry;
			if (new_digits[i] > 9)
			{
				carry = new_digits[i] % 10;
				new_digits[i] = new_digits[i] - carry;
			}
			else
			{
				carry = 0;
			}
		}
	}
	// Return the new struct
	return alint_init (new_ndigits, new_sign, 
			remove_leading_zeroes(new_digits, new_ndigits));
}

/**
 * Mutiply two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * 
ali_multiply (ALInt *a, ALInt *b)
{
	int flag = find_signs(a, b);
	int new_sign = 0;
	int new_ndigits = find_bigger (a, b)->ndigits;;
	int new_digits[new_ndigits * 2];

	if (flag == 1 || flag == 4)
	{
		new_sign = 1;
	}
	else
	{
		new_sign = -1;
	}

	// Multiply the two integers together
	int carry = 0;
	for (int i = new_ndigits - 1; i >= 0; i--)
	{
		for(int j = new_ndigits - 1; j >= 0; j--)
		{
			int product = a->digits[i] * b->digits[j];
			// Check for carry over in multiplication
			if (product > 9) 
			{
				carry += product % 10;
				product = product - carry;
			}
			// Setting new value in array of digits
			new_digits[i] = product + carry;
			if (new_digits[i] > 9)
			{
				carry = new_digits[i] % 10;
				new_digits[i] = new_digits[i] - carry;
			}
			else
			{
				carry = 0;
			}
		}
	}

	// Return the new struct
	return alint_init (new_ndigits, new_sign, 
			remove_leading_zeroes(new_digits, new_ndigits * 2));
}

/**
 * Find the quotient two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
ALInt * 
ali_quotient (ALInt *a, ALInt *b)
{
}

/**
 * Find the remainder two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
ALInt * 
ali_remainder (ALInt *a, ALInt *b)
{
}

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void 
ali_free (ALInt *i)
{
	free (i->digits);
	free (i);
}

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

 /**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
long 
ali2long (ALInt *a)
{

}

/**
 * Convert a to string representation.  Returns a newly-allocated
 * string.
 */
char * 
ali2str (ALInt *a)
{
	// Malloc a new string
	char ret[a->ndigits + 1];
	// Convert to string representation
	int n = 0;
	for (int i = 0; i < 5; i++) {
        n += sprintf (&ret[n], "%d", a->digits[i]);
    }
	// Return the new string
	return ret;
}

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