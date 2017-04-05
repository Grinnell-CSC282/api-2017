#include "api.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
/**
* apid_add, api_dub, api_mlt, api_dvd are the common arithemtic operations
*   implemented for arbitrary precision numbers.
* Each take two parameters.
* In the case of subtraction, the second will be subtracted from the first.
* In the case of division, the first will be divided by the second.
* The function will terminate and return null incase b is the equivalent of
*   zero.
*/
// if normal is 1, it is true, if not it is 0
APInt *
api_add_helper (APInt * a, APInt * b, int normal)
{
  if (normal == 1 && a->sign == positive && b->sign == negative)
    {
      return api_sub_helper (a, b, 0);
    }
  else if (normal == 1 && a->sign == negative && b->sign == positive)
    {
      return api_sub_helper (b, a, 0);
    }
  else
    {
      APInt *ret = str2api ("");

      ret->sign = a->sign;
      bool left_over = false;
      int i, j, sum;
      for (i = 0, j = 0; i < a->list->size && j < b->list->size; i++, j++)
	{
	  sum = a->list->array[i] + b->list->array[j];
	  if (left_over)
	    {
	      sum++;
	      left_over = false;
	    }			// if
	  if (sum >= BASE)
	    {
	      sum = sum % BASE;
	      left_over = true;
	    }			// if
	  add_last (ret->list, sum);
	}			// for
      for (; j < b->list->size; j++)
	{
	  if (left_over)
	    {
	      left_over = false;
	      add_last (ret->list, b->list->array[j] + 1);
	    }			// if
	  else
	    {
	      add_last (ret->list, b->list->array[j]);
	    }
	}			// for
      for (; i < a->list->size; i++)
	{
	  if (left_over)
	    {
	      left_over = false;
	      add_last (ret->list, a->list->array[i] + 1);
	    }			// if
	  else
	    {
	      add_last (ret->list, a->list->array[i]);
	    }
	}			// for
      if (left_over)
	{
	  add_last (ret->list, 1);
	}
      return ret;
    }				// else
}

APInt *
api_add (APInt * a, APInt * b)
{
  return api_add_helper (a, b, 1);
}

APInt *
api_sub_helper (APInt * a, APInt * b, int normal)
{
  if (normal == 1 && a->sign == positive && b->sign == negative)
    {
      return api_add_helper (a, b, 0);
    }				// if
  else if (normal == 1 && a->sign == negative && b->sign == positive)
    {
      return api_add_helper (b, a, 0);
    }				// else if
  else
    {
      if (api_compare (a, b) == 2)
	{
	  return str2api ("");
	}			// if
      else if (api_compare (a, b) == 0)
	{
	  APInt *ret = str2api ("");
	  ret->sign = a->sign;
	  bool left_over = false;
	  int i, dif;
	  for (i = 0; i < b->list->size; i++)
	    {
	      dif = a->list->array[i] - b->list->array[i];
	      if (left_over)
		{
		  dif--;
		  left_over = false;
		}		// if
	      if (dif < 0)
		{
		  dif += BASE;
		  left_over = true;
		}		// if
	      add_last (ret->list, dif);
	    }			// for
	  for (; i < a->list->size; i++)
	    {
	      if (left_over)
		{
		  left_over = false;
		  add_last (ret->list, a->list->array[i] - 1);
		}		// if
	      else
		{
		  add_last (ret->list, a->list->array[i]);
		}		// else
	    }			//for

	  // this is important. I noticed due to the fact that I might have some
	  // zeros, I don't acutally reduce the size. Here I attempt to do that:
	  int zero_count = 0;	// finding the amount of zeroes.
	  char *string = api2str (ret);
	  for (; string[zero_count] != '\0' && (string[zero_count] == '0'
						|| string[zero_count] == '+'
						|| string[zero_count] == '-');
	       zero_count++)
	    ;
	  // negative 1 because it also counted the sign
	  ret->list->size -= zero_count - 1;	// fixing the size
	  free (string);
	  return ret;
	}			// else if
      else
	{
	  APInt *ret = str2api ("");
	  ret->sign = b->sign;
	  bool left_over = false;
	  int i, dif;
	  for (i = 0; i < a->list->size; i++)
	    {
	      dif = b->list->array[i] - a->list->array[i];
	      if (left_over)
		{
		  dif--;
		  left_over = false;
		}		// if
	      if (dif < 0)
		{
		  dif += BASE;
		  left_over = true;
		}		// if
	      add_last (ret->list, dif);
	    }			// for
	  for (; i < b->list->size; i++)
	    {
	      if (left_over)
		{
		  left_over = false;
		  add_last (ret->list, b->list->array[i] - 1);
		}		// if
	      else
		{
		  add_last (ret->list, b->list->array[i]);
		}		// else
	    }			// for
	  // this is important. I noticed due to the fact that I might have some
	  // zeros, I don't acutally reduce the size. Here I attempt to do that:
	  int zero_count = 0;	// finding the amount of zeroes.
	  char *string = api2str (ret);
	  for (; string[zero_count] != '\0' && (string[zero_count] == '0'
						|| string[zero_count] == '+'
						|| string[zero_count] == '-');
	       zero_count++)
	    ;
	  // negative 1 because it also counted the sign
	  ret->list->size -= zero_count - 1;	// fixing the size
	  free (string);
	  return ret;
	}			// else

    }				// else
}

APInt *
api_sub (APInt * a, APInt * b)
{
  return api_sub_helper (a, b, 1);
}

// return 0 if a is bigger than b, 1 if b is bigger than a
// returns 2 if they are the same
int
api_compare (APInt * a, APInt * b)
{
  if (a->list->size > b->list->size)
    {
      return 0;
    }
  else if (a->list->size < b->list->size)
    {
      return 1;
    }
  else
    {
      for (int i = a->list->size - 1; i > -1; i--)
	{
	  if (a->list->array[i] > b->list->array[i])
	    {
	      return 0;
	    }			// if
	  else if (a->list->array[i] < b->list->array[i])
	    {
	      return 1;
	    }			// else if
	}			// for
      return 2;
    }				// else

}

int
api_true_compare (APInt * a, APInt * b)
{
  if (a->sign == positive && b->sign == negative)
    {
      return 0;
    }
  else if (a->sign == negative && b->sign == positive)
    {
      return 1;
    }
  else
    {
      return api_compare (a, b);
    }
}

APInt *
api_mlt (APInt * a, APInt * b)
{
  if (a->list->size == 0 || b->list->size == 0)
    {
      return str2api ("");
    }				// if
  else
    {
      APInt *ret = str2api ("");
      int left_over, multiple;
      APInt *middle;
      for (int i = 0; i < b->list->size; i++)
	{
	  left_over = 0;
	  middle = str2api ("");
	  for (int j = 0; j < i; j++)
	    {
	      add_last (middle->list, 0);
	    }			// for
	  for (int j = 0; j < a->list->size; j++)
	    {
	      multiple = a->list->array[j] * b->list->array[i] + left_over;
	      left_over = multiple / BASE;
	      add_last (middle->list, multiple % BASE);
	    }			// for
	  if (left_over != 0)
	    {
	      add_last (middle->list, left_over);
	    }			// if
	  APInt *oldret = ret;
	  ret = api_add (ret, middle);
	  api_free (oldret);
	  api_free (middle);
	}			// for
      if ((b->sign == positive && a->sign == positive)
	  || (a->sign == negative && b->sign == negative))
	{
	  ret->sign = positive;
	}			// if
      else
	{
	  ret->sign = negative;
	}			// else
      return ret;
    }				// else
}

APInt *
api_dvd (APInt * a, APInt * b)
{
  APInt *zero = str2api ("");
  if (api_compare (zero, b) == 2)
    {
      printf
	("OK, enough. My laptop is bleeding next to me and I'm writing this code instead of fixing it. At this moment, I don't want to think about dividing things by zero. I'll change this later, but not at 2:35 AM because of a bluetooth issue.");
      free (zero);
      return NULL;
    }				// if
  else
    {
      APInt *one = int2api (1);
      APInt *ret = str2api ("");
      APInt *oldret;
      APInt *current = api_add (a, zero);
      APInt *oldcurr;
      free (zero);
      while (api_compare (current, b) == 0 || api_compare (current, b) == 2)
	{
	  oldret = ret;
	  ret = api_add (ret, one);
	  free (oldret);
	  oldcurr = current;
	  current = api_sub_helper (current, b, 0);
	  free (oldcurr);
	}			// while
      if ((b->sign == positive && a->sign == positive)
	  || (a->sign == negative && b->sign == negative))
	{
	  ret->sign = positive;
	}			// if
      else
	{
	  ret->sign = negative;
	}			// else
      free (one);
      free (current);
      return ret;
    }				// else
}
