/**
 * alilib-tolong.c
 *    Converting an arbitratily long integer to a long for alilib.
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

}