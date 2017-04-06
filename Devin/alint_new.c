#include "alint_new.h"

void
parse_string(char *str, ALInt *alint)
{
  ALIntDigit cur; 
  alint->first = cur;
  alint->num_digits = 0;
  while (isdigit(*str))
  {
    cur->val = (int) *str;
    cur = cur->next;
    alint->last = cur;
    alint->num_digits++;
    str++; 
  } 
}

ALInt * 
int_to_alint(int i)
{
  ALInt *alint;

  // Set sign of alint
  if (i < 0)
    alint->sign = -1;
  else
    alint->sign = 1;

  // Convert i to a string
  char i_str[11];
  sprintf(i_str, "%d", i);

  // Parse string and add to alint
  parse_string(i_str, alint);

  return alint;
}

ALInt * 
str_to_alint(char *str)
{
  ALInt *alint;

  // Skip whitespace
  while ((*str != '\0') && (isspace (*str)))
    str++;
  
  // Check for a '-' sign and set if exists
  if (*str == '-')
  {
    str++;
    alint->sign = -1;
  }

  else if (*str == '+')
  {
    str++;
    alint->sign = 1;
  }

  else
    alint->sign = 1;
  
  // Parse string and add to alint
  parse_string(str, alint); 

  return alint;
}

ALInt * 
long_to_alint(long l)
{
  ALInt *alint;

  // Set sign of alint
  if (l < 0)
    alint->sign = -1;
  else
    alint->sign = 1;

  // Convert l to a string
  char l_str[20]; // 19 digits for a 64 bit compiler
  sprintf(l_str, "%ld", l);

  // Parse string and add to alint
  parse_string(l_str, alint);

  return alint;
}

ALInt * 
double_to_alint(double d)
{
  ALInt *alint;

  // Set sign of alint
  if (d < 0)
    alint->sign = -1;
  else
    alint->sign = 1;

  // Convert l to a string
  char d_str[20]; // This number is arbitrary 
  sprintf(d_str, "%f", d);

  // Parse string and add to alint
  parse_string(d_str, alint);

  return alint;

}
