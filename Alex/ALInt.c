#include "ALInt.h"

#include <stdlib.h>

ALInt *
ali_add (ALInt * a, ALInt * b)
{

}

ALInt *ali_subtract (ALInt * a, ALInt * b);
ALInt *ali_multiply (ALInt * a, ALInt * b);
ALInt *ali_quotient (ALInt * a, ALInt * b);
ALInt *ali_remainder (ALInt * a, ALInt * b);
void
ali_free (ALInt * i)
{
  ALIntDigit *cur = i->head;
  ALIntDigit *nxt;
  while (cur)
    {
      nxt = cur->next;
      free (cur);
      cur = nxt;
    }
  free (i);
}

ALInt *double2ali (double d);

ALInt *long2ali (long l);

ALInt *
int2ali (int i)
{
}

ALInt *str2ali (char *str);

long
ali2long (ALInt * a)
{

}

double ali2double (ALInt * a);

int ali2int (ALInt * a);

char *
ali2str (ALInt * a)
{
  char *str = malloc ((a->length + 1) * sizeof (char));
  ALIntDigit *cur = a->head;
  for (int i = 0; i < a->length; i++)
    {
      str[i] = cur->val;
      cur = cur->next;
    }
  str[a->length] = '\0';
  return str;
}
