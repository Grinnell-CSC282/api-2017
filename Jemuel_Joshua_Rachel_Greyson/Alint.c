#include "Alint.h"
#include <stdio.h>      // For printf and fprintf
#include <stdlib.h>     // For scanf
#include <limits.h>     // For LONG_MAX and LONG_MIN
#include <ctype.h>      // For isdigit and such.

int
str2long (char *str, long *lp)
{
  long result = 0;
  long sign = 1;

  // Skip over whitespace
  while ((*str != '\0') && (isspace (*str)))
    str++;

  // Check for the sign
  if (*str == '-')
    {
      str++;
      sign = -1;
    }
  else if (*str == '+')
    {
      str++;
    }

  // Sanity check
  if (!*str)
    return 1;

  // Read all of the digits
  while (isdigit (*str))
    {
      long increment = sign * convertDigit (*str);
      // Upper-bound check
      if ((sign == 1) && (result > (LONG_MAX - increment) / 10))
        return 3;
      // Lower-bound check
      if ((sign == -1) && (result < (LONG_MIN - increment) / 10))
        return 3;
      // Update the result
      result = result*10 + increment;
      // And move on to the next character
      str++;
    } // while

  // Sanity check
  if (*str != '\0')
    return 2;

  // I think that's it.
  *lp = result;
  return 0;
} // str2long

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void
ali_free (ALInt *i)
{
  if(i != NULL)
  {
    if (i -> head != NULL)
    {
      ALIntDigit *cur = i->head;
      ALIntDigit *next;
      while(cur)
      {
          next = cur->next;
          free (cur);
          cur = next;
      }
      free (i);
    }
  }
}

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * // unfinished
int2ali (int i)
{
  ALInt *new = (ALInt *) malloc(sizeof(ALInt));
  if(i < 0)
  {
    new->sign = -1;
  }
  while (i >= 0)
  {
    ALIntDigit *new = (ALIntDigit *) malloc(sizeof(ALIntDigit));
    new->val =
  }
}

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt *
str2ali (char *i)
{

}

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt *
long2ali (long i)
{

}

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt *
double2ali (double i)
{

}

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
long
ali2long (ALInt *a)
{
  long result = 0;
  //long sign = -1;

  int base = 10;
  int power = 0;

  ALIntDigit *cur = a->back;
  while(sum < LONG_MAX)
  {
    int num = cur->val;
    result += num * (base * power);
    power++;
    cur = cur->prev;
  }
  if(a->sign == -1)
  {
    result * -1;
  }
  return result;
}

/**
 * Convert a to string representation.  Returns a newly-allocated
 * string.
 */
char *
ali2str (ALInt *a)
{

}

/**
 * Find the int that corresponds to a.
 */
long
ali2int (ALInt *a)
{
  return (int) ali2long(a);
}

/**
 * Find the double that corresponds to a.
 */
double
ali2double (ALInt *a)
{
  return (double) ali2long(a);
}


/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt *
ali_add (ALInt *a, ALInt *b)
{

}

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt *
ali_subtract (ALInt *a, ALInt *b)
{

}

/**
 * Multiply two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt *
ali_multiply (ALInt *a, ALInt *b)
{

}

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt *
ali_quotient (ALInt *a, ALInt *b)
{

}

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt *
ali_remainder (ALInt *a, ALInt *b)
{

}
