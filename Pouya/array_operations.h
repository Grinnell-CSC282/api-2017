#ifndef __ARRAY_OPERANDS__
#define __ARRAY_OPERANDS__
#include <stdlib.h>
/**
Array List to hold arbitrary large integers.
It remembers the current size of the number, the maximum size the current array
can hold, and a charachter array. A charachter array is used for efficiency.
Later, I will improve the program to use the entire capacity of a char.
Currently it only uses 10/256 of it.
Note that size is not zero indexed. For instance, 2323 will have size 4.  

There are three main functions.
  array_list_init : initilizes an array. Original max_size is set to START_SIZE.
  add_last        : adds a value to the end of an array. Makes sure we
                      do not get out of bounds.
  free_list       : frees our list in a proper manner.
*/
#define START_SIZE 16

struct array_list
{
  size_t size;
  size_t max_size;
  unsigned char *array;
};

typedef struct array_list array_list;

array_list *array_list_init ();
void add_last (array_list * list, char val);
void free_list (array_list * list);


#endif
