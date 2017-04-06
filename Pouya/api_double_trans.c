#include "api.h"
#include "array_operations.h"
#include <stdint.h>
#include <stdio.h>
#include <float.h>
/**
* Operations to turn an APInt into an long and vice versa.
* Caution: if the user attempts to turn an APInt that is bigger than the bounds
*   of int, behaviour is undefined for now.
*/
double
api2double (APInt * i)
{
  if (i->list->size == 0)
    {
      return 0;
    }				// if
  APInt *api_max = double2api (DBL_MAX);
  // incase our number is equal to api_max
  if (api_compare (api_max, i) == 0)
    {
      api_free (api_max);
      if (i->sign == positive)
	{
	  return DBL_MAX;
	}
      else
	{
	  return -DBL_MAX;
	}
    }
  // in case our number is bigger, we can return infinity
  else if (api_compare (api_max, i) == -1)
    {
      api_free (api_max);
      if (i->sign == positive)
	{
	  return 1.0 / 0.0;
	}
      else
	{
	  return -1.0 / 0.0;
	}
    }
  api_free (api_max);
  double ret = 0;		// the return value;
  double power = 1;		// keeping track of our power, more efficient than
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
double2api (double i)
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
  while (i >= 1)
    {
      add_last (api->list, ((int) i) % BASE);
      i = (i - (((int) i) % BASE)) / BASE;
    }				// while
  return api;
}
