#include "api.h"
#include "array_operations.h"
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
/**
* Operations to turn an APInt into an long and vice versa.
* Caution: if the user attempts to turn an APInt that is bigger than the bounds
*   of int, behaviour is undefined for now.
*/
long
api2long (APInt * i)
{
  if (i->list->size == 0)
    {
      return 0;
    }				// if
  APInt *api_max = long2api (LONG_MAX);
  // incase our number is bigger or equal to api_max
  if (api_true_compare (api_max, i) != 1)
    {
      api_free (api_max);
      return LONG_MAX;
    }
  api_free (api_max);
  APInt * api_min = long2api(LONG_MIN);
  // incase our number is smaller or equal to api_min
  if (api_true_compare (api_min, i) != -1)
    {
      api_free (api_min);
      return LONG_MIN;
    }
  api_free (api_min);
  long ret = 0;			// the return value;
  long power = 1;		// keeping track of our power, more efficient than
  //    calling pow each time
  // for loop to extract an integer from our array_list
  for (int j = 0; j < i->list->size; j++)
    {
      ret += power * i->list->array[j];
      power *= BASE;
    }				// for
  // if statements to add in the sign of our number
  if (!i->sign)
    {
      return ret;
    }				// if
  else
    {
      return -ret;
    }				// else
}				// api2int


APInt *
long2api (long i)
{
  APInt *api = (APInt *) malloc (sizeof (APInt));	// making our number
  // finding out about the sign
  if (i >= 0)
    {
      api->sign = positive;
    }				// if
  else
    {
      api->sign = negative;
      // since we have already saved the sign, we no longer need this.
      i *= -1;
    }				// else
  api->list = array_list_init ();
  while (i != 0)
    {
      add_last (api->list, i % BASE);
      i = (i - (i % BASE)) / BASE;
    }				// while
  return api;
}
