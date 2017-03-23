#include <stdlib.h>
#include "ali.h"

alint * alint_init(size_t start_size) {
  alint * ret = malloc(sizeof(alint));
  ret->data = malloc(sizeof(data_t) * start_size);
  ret->size = 0;
  ret->max_size = start_size;
  return ret;
}
