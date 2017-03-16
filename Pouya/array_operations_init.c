/**
* Function to initilize an array_list
*/
#include <stdlib.h>
#include "array_operations.h"

array_list *
array_list_init ()
{
  array_list *list = malloc (sizeof (array_list));
  list->array = (unsigned char *) malloc (START_SIZE);
  list->max_size = START_SIZE;
  list->size = 0;
  return list;
}
