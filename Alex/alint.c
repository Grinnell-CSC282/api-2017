#include "alint.h"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

const int E[] = {
  0,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000,
  };

ALInt *
ali_add (ALInt * a, ALInt * b)
{

}

ALInt *ali_subtract (ALInt * a, ALInt * b) {

}

ALInt *ali_multiply (ALInt * a, ALInt * b) {

}

ALInt *ali_quotient (ALInt * a, ALInt * b) {

}

ALInt *ali_remainder (ALInt * a, ALInt * b) {

}

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

ALInt *double2ali (double d) {
  return int2ali((int)d);
}

ALInt *long2ali (long l) {
  return int2ali((int)l);
}

ALInt *
int2ali (int i)
{
  char str[15]; // INT_MAX is less than 15 characters wide
  sprintf(str,"%d",i);
  return str2ali(str);
}

ALIntDigit *str2ali_k (char *str, ALIntDigit *last, int *length, ALIntDigit **tail) {
  if (!str[0]) {
    *tail = last;
    return NULL;
  }
  ALIntDigit *digit = malloc(sizeof(ALIntDigit));
  (*length)++;

  digit->prev = last;
  digit->val = str[0];
  digit->next = str2ali_k(&str[1], digit, length, tail); 

  return digit;
}

ALInt *str2ali (char *str) {
  ALInt *i = malloc(sizeof(ALInt));
  i->length = 0;
  i->nonnegative = !(str[0] =='-');
  str = i->nonnegative ? str : &str[1];
  i->head = str2ali_k(str,NULL,&i->length, &i->tail); 
 
  return i;
}

long
ali2long (ALInt * a)
{
  return (long)ali2int(a);
}

double ali2double (ALInt * a) {
  return (double)ali2int(a);
}

int ali2int (ALInt * a)
 {
  int sum = 0;
  int power = 0;
  ALIntDigit *cur = a->tail;
  while (sum < INT_MAX && sum >= 0) { // If integer overflow, sum will go negative
    if (!cur) return (a->nonnegative ? sum : -sum);
    int val = (int)cur->val - '0';
    sum += E[power] * val;

    power++;
    cur = cur->prev;
  }
  return (a->nonnegative ? INT_MAX : -INT_MAX);
 }

char *
ali2str (ALInt * a)
{
  int strlen = a->length + (a->nonnegative ? 0 : 1);
  char *str = malloc (strlen * sizeof (char));
  ALIntDigit *cur = a->head;
  int i = 0;
  if (!a->nonnegative) {
    str[i] = '-'; 
    i++;
  }
  while (i < strlen)
    {
      str[i] = cur->val;
      cur = cur->next;
      i++;
    }
  str[strlen] = '\0';
  return str;
}
