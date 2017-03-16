#include <stdlib.h>
#include "array_operations.h"
#include "api.h"

/**
* Function to free an APInt
*/
void api_free(APInt *i){
  if (i != NULL){
    if (i->list != NULL){
      free_list(i->list);
    }
    free(i);
  }
}
