#ifndef __ARRAY_OPERANDS__
#define __ARRAY_OPERANDS__
#include <stdlib.h>

#define START_SIZE 16

struct array_list{
  size_t size;
  size_t max_size;
  unsigned char * array;
};

typedef struct array_list array_list;

array_list * array_list_init();
void ensure_capacity(array_list * list);
void add_last(array_list * list, char val);
void free_list(array_list * list);


#endif
