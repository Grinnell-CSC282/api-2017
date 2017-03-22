#include <stdlib.h>
#include "ali.h"


alint * alint_init() {
  alint * ret = malloc(sizeof(alint));
  ret->data = malloc(sizeof(data_t) * ALI_BLOCK_SIZE);
  ret->size = 0;
  ret->max_size = ALI_BLOCK_SIZE;
  return ret;
}
