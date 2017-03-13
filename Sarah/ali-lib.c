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

/*struct ALInt 
  {
    int ndigits;
    int sign;       // 1 for positive, -1 for negative
    int digits[];   // Each represents one base-16 digit
  };
typedef struct ALInt ALInt; */


/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * 
ali_add (ALInt *a, ALInt *b)
{
	int newNdigits = find_longer_number (a, b);
	int flag = find_signs (a, b);
	int newSign = 0;
	int newDigits[newNdigits + 1];

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
			newSign = -1;
		}
		else 
		{
			newSign = 1;
		}
		int carry = 0;
		// Add the integers together
		for (int i = newNdigits - 1; i >= 0; i--)
		{
			int sum = a->digits[i] + b->digits[i];
			// Check for carry over in addition
			if (sum > 9) {
				carry += sum % 10;
				sum = sum - carry;
			}
			// Setting new value in array of digits
			newDigits[i] = sum + carry;
			if (newDigits[i] > 9)
			{
				carry = newDigits[i] % 10;
				newDigits[i] = newDigits[i] - carry;
			}
			else
			{
				carry = 0;
			}
		}
	}

	// Check for a leading zero
	if (newDigits[0] == 0) {
		// Copy into a new array
		int noLeadingZeroes[newNdigits];
		for (int i = 1; i < newNdigits; i++)
		{
			noLeadingZeroes[i - 1] = newDigits[i];
		}
		memcpy(newDigits, noLeadingZeroes, newNdigits * sizeof (int));
	}

	// Return the new struct
	return alint_init (newNdigits, newSign, newDigits);
}

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * 
ali_subtract (ALInt *a, ALInt *b)
{
	int newNdigits = find_longer_number (a, b);
	int flag = find_signs (a, b);
	int newSign = 0;
	int newDigits[newNdigits + 1];

	// If adding instead of subtracting then go to ali_add
	if (flag == 0 || flag == 4)
	{
		ali_add (a, b);
	}
	else 
	{
		int carry = 0;
		// Add the integers together
		for (int i = newNdigits - 1; i >= 0; i--)
		{
			int sum = a->digits[i] - b->digits[i];
			// Check for carry over in addition
			if (sum < a->digits[i]) {
				carry += sum % 10;
				sum = sum - carry;
			}
			// Setting new value in array of digits
			newDigits[i] = sum + carry;
			if (newDigits[i] > 9)
			{
				carry = newDigits[i] % 10;
				newDigits[i] = newDigits[i] - carry;
			}
			else
			{
				carry = 0;
			}
		}
	}
	// Return the new struct
	return alint_init (newNdigits, newSign, newDigits);
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
	int newSign = 0;

	if (flag == 1 || flag == 4)
	{
		newSign = 1;
	}
	else
	{
		newSign = -1;
	}

	// Multiply the new integers together
	

	// Return the new struct
	//return alint_init (newNdigits, newSign, newDigits);
}

/**
 * Find the quotient two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
ALInt * 
ali_quotient (ALInt *a, ALInt *b)
{
	// Return the new struct
	//return alint_init (newNdigits, newSign, newDigits);
}

/**
 * Find the remainder two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
ALInt * 
ali_remainder (ALInt *a, ALInt *b)
{
	// Return the new struct
	//return alint_init (newNdigits, newSign, newDigits);
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
	int newSign = 0;
	if (i < 0)
	{
		newSign = -1;
	}
	else 
	{
		newSign = 1;
	}
	// Find the number of digits of the new integer
	int newNdigits = 0;
	int n = i;
	while (n != 0)
	{
		n /= 10;
		newNdigits++;
	}
	// Put the integer into the array
	// Declare a new array for the new integer
	int newDigits[newNdigits];
	if (newNdigits != 0)
	{
		n = i;
		int j = 0;
		while (n != 0)
		{
			newDigits[j] = n % 10;
			n /= 10;
			j++;
		}
	}
	// Return the new struct
	return alint_init (newNdigits, newSign, newDigits);
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
	char * ret = malloc (sizeof (char) * a->ndigits);
	// Convert to string representation

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
 * Finds the longer of two ALInts and returns that length
 */
int
find_longer_number(ALInt *a, ALInt *b)
{
	int len = 0;
	// Find the longer number
	if (a->ndigits > b->ndigits)
	{
		len = a->ndigits;
	}
	else
	{
		len = b->ndigits;
	}
	return len;
}

/**
 * Creates a new ALInt from values for that integer.
 */
ALInt * 
alint_init(int newNdigits, int newSign, int newDigits[]) 
{
	// Declare a new arbitrarily long integer
	ALInt * newALInt = (ALInt *) malloc (sizeof (ALInt));
	// Assigning the values of the new integer to the struct	
	newALInt->ndigits = newNdigits;
	newALInt->sign = newSign;
	memcpy(newALInt->digits, newDigits, newNdigits * sizeof (int));
	// Return the new struct
	return newALInt;
}