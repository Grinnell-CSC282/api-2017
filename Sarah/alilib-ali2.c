/**
 * alilib-ali2.c
 *    Converts an arbitrarily large integer to something else
 *    (double, int, string, long) for alilib.
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
* Find the long that corresponds to a.  If a > LONG_MAX,
* returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
*/
long 
ali2long (ALInt *a)
{
	return atol (ali2str (a));
} // ali2long

 /**
 * Find the double that corresponds to a.  If a > DOUBLE_MAX,
 * returns DOUBLE_MAX.  If a < DOUBLE_MIN, returns DOUBLE_MIN.
 */
double 
ali2double (ALInt *a)
{
	return atof (ali2str (a));
} // ali2double

 /**
 * Find the int that corresponds to a.  If a > INT_MAX,
 * returns INT_MAX.  If a < INT_MIN, returns INT_MIN.
 */
int 
ali2int (ALInt *a)
{
	return atoi (ali2str (a));
} // ali2int

/**
* Convert a to string representation.  Returns a newly-allocated
* string.
*/
char * 
ali2str (ALInt *a)
{
	// Malloc a new string
	char ret[a->ndigits + 1];
	if (a->sign == -1)
	{
		ret[0] = '-';
	}
	else 
	{
		ret[0] = ' ';
	}
	// Convert to string representation
	int n = 0;
	for (int i = 1; i < 5; i++) {
        n += sprintf (&ret[n], "%d", a->digits[i]);
    }
	// Return the new string
	return ret;
} // ali2str