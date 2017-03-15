#include <stdlib.h>
#include "array_operations.h"
#include "api.h"


void api_free(APInt *i){
  if (i->list != NULL){
    free_list(i->list);
  }
  if (i->p_list != NULL){
    free_list(i->p_list);
  }
  free(i);
}
