#include "api.h"
#include "array_operations.h"
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
/**
* Operations to turn an APInt into an int and vice versa.
* Caution: if the user attempts to turn an APInt that is bigger than the bounds
*   of int, program return INT_MAX;
*/
int
api2int (APInt * i)
{
  if (i->list->size == 0)
    {
      return 0;
    }				// if
  APInt *api_max = int2api (INT_MAX);
  // incase our number is bigger or equal to api_max
  if (api_true_compare (api_max, i) != 1)
    {
      api_free (api_max);
      return INT_MAX;
    }
  api_free (api_max);
  APInt *api_min = int2api (INT_MIN);
  // incase our number is smaller or equal to api_min
  if (api_true_compare (api_min, i) != -1)
    {
      api_free (api_min);
      return INT_MIN;

    }
  api_free (api_min);
  int ret = 0;			// the return value;
  int power = 1;		// keeping track of our power, more efficient than
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
int2api (int i)
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
