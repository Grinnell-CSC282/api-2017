#include <stdlib.h>
#include "ali_core.h"

alint *
alint_init (size_t start_size)
{
  alint *ret = malloc (sizeof (alint));
  ret->data = malloc (sizeof (data_t) * start_size);
  for (size_t i = 0; i < start_size; i++)
    ret->data[i] = 0;
  ret->size = start_size;
  return ret;
}

void
alint_free (alint * integer)
{
  free (integer->data);
  free (integer);
}
