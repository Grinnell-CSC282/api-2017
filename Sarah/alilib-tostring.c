/**
 * alilib-tostring.c
 *    Converting an arbitratily long integer to a string for alilib.
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
} // ali2str