/**
* Function to free array_lists.
* Frees the array inside first and then frees the array_list itself.
*/
#include <stdlib.h>
#include "array_operations.h"

void
free_list (array_list * list)
{
  free (list->array);
  free (list);
}
