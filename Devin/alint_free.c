#include "alint_free.h"
// Frees the values of the linked list by setting them to NULL iteratively

void alint_free(ALInt *i)
{
  cur = i->first;
  while (cur != NULL)
  {
    cur->val = NULL;
    cur = cur->next;
  } 
}
