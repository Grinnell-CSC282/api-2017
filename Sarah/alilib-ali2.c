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
	long l = atol (ali2str (a));
	if (l > LONG_MAX)
	{
		return LONG_MAX;
	}
	else if (l < LONG_MIN)
	{
		return LONG_MIN;
	}
	else
	{
		return l;
	}
} // ali2long

 /**
 * Find the double that corresponds to a.  If a > DOUBLE_MAX,
 * returns DOUBLE_MAX.  If a < DOUBLE_MIN, returns DOUBLE_MIN.
 */
double 
ali2double (ALInt *a)
{
	double d = atof (ali2str (a));
	if (d > DOUBLE_MAX)
	{
		return DOUBLE_MAX;
	}
	else if (d < DOUBLE_MIN)
	{
		return DOUBLE_MIN;
	}
	else
	{
		return d;
	}
} // ali2double

 /**
 * Find the int that corresponds to a.  If a > INT_MAX,
 * returns INT_MAX.  If a < INT_MIN, returns INT_MIN.
 */
int 
ali2int (ALInt *a)
{
	int i = atoi (ali2str (a));
	if (i > INT_MAX)
	{
		return INT_MAX;
	}
	else if (i < INT_MIN)
	{
		return INT_MIN;
	}
	else
	{
		return i;
	}
} // ali2int

/**
* Convert a to string representation.  Returns a newly-allocated
* string.
*/
char * 
ali2str (ALInt *a)
{
	// Malloc a new string
	char * ret = malloc (sizeof (char) * a->ndigits + 1);
	if (a->sign == -1)
	{
		ret[0] = '-';
	}
	else 
	{
		ret[0] = ' ';
	}
	for (int i = 1; i < 5; i++) {
        ret[i] = a->digits[i];
    }
    ret += '\0';
	// Return the new string
	return ret;
} // ali2str