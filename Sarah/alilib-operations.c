/**
 * alilib-operations.c
 *    Standard operations on arbitrarily long integers for alilib.
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