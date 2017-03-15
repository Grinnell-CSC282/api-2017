#include <stdlib.h>
#include "api.h"
#include "array_operations.h"

APInt * int2api (int i){
  APInt * api = (APInt *) malloc(sizeof(APInt));
  if (i >= 0){
    api->sign = positive;
  }
  else {
    api->sign = negative;
  }
  api->list = array_list_init();
  while (i != 0){
    api->list->array[(api->list->size)++] = i % BASE;
    i = (i - (i % BASE)) / BASE;
  }
  return api;
}
