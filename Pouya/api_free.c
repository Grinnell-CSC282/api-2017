#include <stdlib.h>
#include "array_operations.h"
#include "api.h"


void api_free(APInt *i){
  free_list(i->list);
  free(i);
}
