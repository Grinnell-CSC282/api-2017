/**
 * alilib-free.c
 *    Free arbitrarily long integers for alilib.
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
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void 
ali_free (ALInt *i)
{
	free (i->digits);
	free (i);
} // ali_free