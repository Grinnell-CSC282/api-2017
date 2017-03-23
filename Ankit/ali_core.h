#ifndef __ALI_H__
#define __ALI_H__
#include <stdint.h>
#include <stddef.h>
#define BLOCKS(x) (sizeof(x) / sizeof(uint8_t))

typedef uint8_t data_t;

typedef struct
{
  data_t *data;
  size_t size;
  uint8_t sign;
} alint;

void alint_free (alint * integer);
alint *alint_init (size_t starting_size);
#endif
