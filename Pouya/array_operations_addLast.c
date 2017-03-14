/**
* Function to add a value an array_list
*/
#include "array_operations.h"
#include <stdint.h>
void add_last(array_list * list, char val){
  ensure_capacity(list);
  list->array[(list->size)++] = val;
}
