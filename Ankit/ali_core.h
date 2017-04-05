#ifndef __ALI_H__
#define __ALI_H__
#include <stdint.h>
#include <stddef.h>

typedef uint8_t data_t;

typedef struct
{
  data_t *data;
  size_t size;
  uint8_t sign;
} alint;

void alint_free (alint * integer);
alint* alint_init (size_t starting_size);
void alint_resize (alint* integer, size_t new_size);
#endif
