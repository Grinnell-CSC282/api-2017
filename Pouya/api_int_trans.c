#include "api.h"
#include "array_operations.h"
#include <stdint.h>
#include <stdio.h>
/**
* Operations to turn an APInt into an int and vice versa.
* Caution: if the user attempts to turn an APInt that is bigger than the bounds
*   of int, behaviour is undefined for now.
*/
int
api2int (APInt * i)
{
  if (i->list->size == 0)
    {
      return 0;
    }				// if
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
