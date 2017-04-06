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

/**
* api_compare and api_true_compare.
* api_compare compares the true value of of two apis. api_true_compare
*   considers the sign too.
* return values:
*     a >  b : +1
*     a == b :  0
*     a <  b : -1
*/
int
api_true_compare (APInt * a, APInt * b)
{
  // we check for a difference in sign
  if (a->sign == positive && b->sign == negative)
    {
      return 1;
    }				// if
  else if (a->sign == negative && b->sign == positive)
    {
      return -1;
    }				// else if
  // no difference in sign, calling api_compare
  else
    {
        if (a->sign == positive)
        {
          return api_compare(a,b);
        }
        else
        {
          return -api_compare(a,b);
        }
    }				// else
}

int
api_compare (APInt * a, APInt * b)
{
  // comparing the size
  if (a->list->size > b->list->size)
    {
      return 1;
    }
  else if (a->list->size < b->list->size)
    {
      return -1;
    }
  // size is the same. Comparing individual values
  else
    {
      for (int i = a->list->size - 1; i > -1; i--)
	{
	  if (a->list->array[i] > b->list->array[i])
	    {
	      return 1;
	    }			// if
	  else if (a->list->array[i] < b->list->array[i])
	    {
	      return -1;
	    }			// else if
	}			// for

      // all values are the same. The true or real values are the same
      return 0;
    }				// else

}

/**
* add and sup each have a helper. The helper has a third value called normal.
* A normal of 1 means to calculate the addition or subtraction properly.
* A normal of 0 means to ignore the the signs and just subtract the true values.
* For instance, api_add(10, -5, 1) = 5 but api_add(10, -5, 0) = 15, and
*   api_add(-5, 10, 0) = -15.
* For instance, api_sub(10, -5, 1) = 15 but api_sub(10, -5, 0) = 5, and
*   api_sub(-5, 10, 0) = 5.
*/

APInt *
api_add (APInt * a, APInt * b)
{
  return api_add_helper (a, b, 1);
}

APInt *
api_add_helper (APInt * a, APInt * b, int normal)
{
  /* making sure we are doing true addition. Adding a negative to positive is \
   * not truely addition
   */
  if (normal == 1 && a->sign == positive && b->sign == negative)
    {
      return api_sub_helper (a, b, 0);
    }				// if
  else if (normal == 1 && a->sign == negative && b->sign == positive)
    {
      return api_sub_helper (b, a, 0);
    }				// if
  // here begins the true addition
  else
    {
      APInt *ret = str2api ("");	// the return value

      ret->sign = a->sign;	// the sign is set to the first variable
      bool left_over = false;
      // a bool used to remember if we have the added values that exceed 10


      int i, j, sum;
      /* i : current index of a->list->array.
       * j : current index of b->list->array.
       *sum: sum of the last two indexes.
       */

      /*
       * here we add elements of a and b that have the same index as long
       * we do not exceed the size of either a or b.
       */
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
      // copying the rest of the value, if b is our longer value
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
      // copying the rest of the value, if a is our longer value
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
      /* making sure our left_over is false. This is a special case when \
       * a and b have the same length and we have a left_over value.
       */
      if (left_over)
	{
	  add_last (ret->list, 1);
	}			// if
      return ret;
    }				// else
}


APInt *
api_sub (APInt * a, APInt * b)
{
  return api_sub_helper (a, b, 1);
}

APInt *
api_sub_helper (APInt * a, APInt * b, int normal)
{
  /* making sure we are doing true subtraction. Subtracting negative from
   *   positive is not truely subtraction
   */
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
      APInt *ret = str2api ("");	// the return value
      // by comparing we know about the sign of the outcome.
      if (api_compare (a, b) == 0)
	{
	  return ret;
	}			// if
      // the case if the true value of a is bigger than b
      else if (api_compare (a, b) == 1)
	{
	  ret->sign = a->sign;
	  bool left_over = false;
	  // a bool used to keep track of value that are below 0
	  int i, dif;
	  /* i : used to keep track of our index, for both i and j
	   * dif: difference of the last two indexes
	   */
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
	  // copying the rest of a
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

	  /*  It is important to note that we will never have a case where
	   *     i == a->list->size but left_over = true. We know this because
	   *     we made sure a > b. If such a thing happens, then we know that
	   *     b > a.
	   */
	}			// else if
      // the case where b is bigger than a
      else
	{
	  ret->sign = b->sign;
	  bool left_over = false;
	  // a bool used to keep track of value that are below 0
	  int i, dif;
	  /* i : used to keep track of our index, for both i and j
	   * dif: difference of the last two indexes
	   */
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
	  // copying the rest of b
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
	  /*  It is important to note that we will never have a case where
	   *     i == b->list->size but left_over = true. We know this because
	   *     we made sure a < b. If such a thing happens, then we know that
	   *     b < a.
	   */

	}			// else
      /* due to how I do subtraction, the result of api_sub(15, 10) = 05.
       *  Mathematically this is currect, but the size of the outcome is 2, not 1.
       *  This part of code is designed to resolve this issue.
       */
      int zero_count = 0;	// the zero count
      char *string = api2str (ret);
      for (;
	   string[zero_count] != '\0' && (string[zero_count] == '0'
					  || string[zero_count] ==
					  '+'
					  || string[zero_count] ==
					  '-'); zero_count++)
	;
      // negative 1 because it also counted the sign
      ret->list->size -= zero_count - 1;	// fixing the size
      free (string);
      return ret;
    }				// else
}

/**
* Well, it multiplies.
*/
APInt *
api_mlt (APInt * a, APInt * b)
{
  // if one number is multiplied by 0
  if (a->list->size == 0 || b->list->size == 0)
    {
      return str2api ("");
    }				// if
  else
    {
      APInt *ret = str2api ("");	// the return value
      int left_over, multiple;
      /*
       * left_over : the amount that exceeded 10
       * multiple  : the value we hold the current multiplication results
       *             before we add it to the return value.
       */
      APInt *middle;
      for (int i = 0; i < b->list->size; i++)
	{
	  left_over = 0;
	  middle = str2api ("");
	  // this for loop multiplies middle by 10
	  for (int j = 0; j < i; j++)
	    {
	      add_last (middle->list, 0);
	    }			// for
	  // this for loop multiplies an element of b by all the elements in a
	  for (int j = 0; j < a->list->size; j++)
	    {
	      multiple = a->list->array[j] * b->list->array[i] + left_over;
	      left_over = multiple / BASE;
	      add_last (middle->list, multiple % BASE);
	    }			// for
	  // making sure we do not have left_over left
	  if (left_over != 0)
	    {
	      add_last (middle->list, left_over);
	    }			// if
	  APInt *oldret = ret;	// making sure we do not lose trak of the old ret
	  ret = api_add (ret, middle);	// updating the return value
	  api_free (oldret);	// freeing the old return
	  api_free (middle);	// freeing the middle
	}			// for
      // choosing the sign of the return value
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

/**
* It divides
*/
APInt *
api_dvd (APInt * a, APInt * b)
{
  // divding by zero.
  APInt *zero = str2api ("");
  if (api_compare (zero, b) == 0)
    {
      printf
	("Sorry, but I do not think I know enough math to answer this. :(");
      free (zero);
      return NULL;
    }				// if
  else
    {
      APInt *one = int2api (1);	// api that corresponds to 1
      APInt *ret = str2api ("");	// our return value
      APInt *oldret;		// a place to keep oldret so that we can free it
      APInt *current = api_add (a, zero);	// keeping track of a current api
      APInt *oldcurr;		// a place to keep the old current api
      free (zero);
      // a loop that will not break until b < current
      while (api_compare (current, b) == 0 || api_compare (current, b) == 1)
	{
	  oldret = ret;
	  ret = api_add (ret, one);
	  free (oldret);
	  oldcurr = current;
	  current = api_sub_helper (current, b, 0);
	  free (oldcurr);
	}			// while
      // choosing the sign of the return value
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
