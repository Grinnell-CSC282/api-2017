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

void
alint_resize(alint* integer, size_t new_size)
{
  if (integer->size >= new_size)
    return;
  integer->data = realloc (integer->data, new_size);
  for (int i = integer->size; i < new_size; i++) {
    integer->data[i] = integer->data[integer->size - 1] >> 7 ? 0xFF : 0;
  }
  integer->size = new_size;
}
