#include "api.h"
#include <stdint.h>



int api2int (APInt * i){
  int ret = 0;
  int power = 1;
  for (int j = 0; j < i->list->size; j++){
    ret += power * i->list->array[j];
    power *= BASE;
  }
  if (!i->sign){
    return ret;
  }
  else {
  return -ret;
  }
}
