/**
* Function to make sure arrays have proper size,
*   will create a new array and repalce everything in it in case it is our of
*   space.
*/
#include <stdlib.h>
#include "array_operations.h"

void ensure_capacity(array_list * list){
  if (list->size >= list->max_size){
    // note that the malloc is designed to work unsigned chars
    unsigned char * new = (unsigned char *) malloc( list->max_size * 2);
    for (int i = 0; i < list->size; i++){
        new[i] = list->array[i];
    }
    list->max_size *= 2;
    unsigned char * temp = list->array;
    list->array = new;
    free(temp);
  }
}
