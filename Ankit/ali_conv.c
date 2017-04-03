#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "ali_conv.h"

#define MIN(a,b) ((a < b) ? a : b)

alint*
int2alint (int var)
{
  alint* ret = alint_init(sizeof(var));
  memcpy(ret->data, &var, sizeof(var));
  ret->size = sizeof(var);
  return ret;
}

alint*
long2alint (long var)
{
  alint* ret = alint_init(sizeof(var));
  memcpy(ret->data, &var, sizeof(var));
  ret->size = sizeof(var);
  return ret;
}

/* Convert an arbitrarily large integer to a regular int. Undefined
 when the value contained in integer is outside the bounds of int
*/
int
ali2int (alint *integer)
{
  int ret = 0;
  memcpy(&ret, integer->data, sizeof(ret));
  return ret;
}

long
ali2long (alint *integer)
{
  long ret = 0;
  alint_resize(integer, sizeof(ret));
  memcpy(&ret, integer->data, sizeof(ret));
  return ret;
}
