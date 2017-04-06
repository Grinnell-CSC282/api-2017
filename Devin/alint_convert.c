#include "alint.h"
#include "alint_convert.h"
#include <math.h>

long 
alint_to_long(ALInt *a)
{
  long result = 0;
  int count;
  ALIntDigit cur = a->first;

  for (count=1; count <= pow(10, a->num_digits); count *= 10)
  {
    result += (cur->val) * count;
    if (cur != a->last)
      cur = cur->next;
  }

  return result;
}

char * 
alint_to_str(ALInt *a)
{
  char str[a->num_digits + 2]; // 2 extra for null terminator and sign
  ALIntDigit cur = a->first;
  int count = 1;

  if (a->sign == 1)
    str[0] = '+';
  else
    str[0] = '-';

  while (cur != a->last)
  {
    str[count++] = (char) cur->val;
    cur = cur->next;
  }

  str[count++] = (char) cur->val; // For last element
  str[count] = '\0';

  return str;
}

int 
alint_to_int(ALInt *a)
{
  int result = 0;
  int count;
  ALIntDigit cur = a->first;

  for (count=1; count <= pow(10, a->num_digits); count *= 10)
  {
    result += (cur->val) * count;
    if (cur != a->last)
      cur = cur->next;
  }

  return result;
}

double 
alint_to_double(ALInt *a)
{
  int result = 0;
  int count;
  ALIntDigit cur = a->first;

  for (count=1; count <= pow(10, a->num_digits); count *= 10)
  {
    result += (cur->val) * count;
    if (cur != a->last)
      cur = cur->next;
  }

  return result;
}
