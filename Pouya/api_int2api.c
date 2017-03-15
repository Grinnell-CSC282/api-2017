#include <stdlib.h>
#include "api.h"
#include "array_operations.h"

APInt * int2api (int i){
  APInt * api = (APInt *) malloc(sizeof(APInt));
  api->base = BASE;
  if (i >= 0){
    api->sign = positive;
  }
  else {
    api->sign = negative;
    i *= -1;
  }
  api->list = array_list_init();
  while (i != 0)
  {
    add_last(api->list, i % api->base);
    i = (i - (i % api->base)) / api->base;
  }
  api->p_list = NULL;
  return api;
}
