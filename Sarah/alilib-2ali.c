/**
 * alilib-toali.c
 *    Converts another format (string, integer, double, long)
 *    to an arbitrarily long integer for alilib.
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
	return ali_new (new_ndigits, new_sign, new_digits);
} // int2ali

/**
  * Create a newly allocated ALInt whose value is i.
  */
 ALInt * 
 str2ali (char * s)
 {
 	return int2ali (atoi (*s));
 } // str2ali

 /**
  * Create a newly allocated ALInt whose value is i.
  */
 ALInt * 
 long2ali (long l)
 {
 	char buffer[50];
 	sprintf (buffer, "%lu", l);
 	return str2ali (buffer);
 } //long2ali

/**
  * Create a newly allocated ALInt whose value is i.
  */
 ALInt * 
 double2ali (double d)
 {
 	char buffer[50];
 	sprintf (buffer, "%f", d);
 	return str2ali (buffer);
 } //double2ali