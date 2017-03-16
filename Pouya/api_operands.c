#include "api.h"
#include <stdbool.h>
/**
* apid_add, api_dub, api_mlt, api_dvd are the common arithemtic operations
*   implemented for arbitrary precision numbers.
* Each take two parameters.
* In the case of subtraction, the second will be subtracted from the first.
* In the case of division, the first will be divided by the second.
* The function will terminate and return null incase b is the equivalent of
*   zero.
*/

APInt * api_add (APInt *a, APInt *b){
  if ( a->sign == positive && b->sign == negative)
  {
    return api_sub(a,b);
  }
  else if (a->sign == negative && b->sign == positive)
  {
    return api_sub(b, a);
  }
  else
  {
      APInt * ret = int2api(0);
      bool left_over = false;
      int i,j,sum;
      for (i = 0, j = 0; i < a->list->size && j < b->list->size; i++, j++){
        sum = a->list->array[i] + b->list->array[j];
        if (left_over) {
          sum++;
          left_over = false;
        } // if
        if (sum > BASE)
        {
          sum = sum % BASE;
          left_over = true;
        } // if
        add_last(ret->list, sum);
      } // for
      for (; j < b->list->size; j++){
        if (left_over){
          left_over = false;
          add_last(ret->list, b->list->array[j] + 1);
        } // if
        else {
          add_last(ret->list, b->list->array[j]);
        }
      } // for
      for (; i < a->list->size; i++){
        if (left_over){
          left_over = false;
          add_last(ret->list, a->list->array[i] + 1);
        } // if
        else {
          add_last(ret->list, a->list->array[i]);
        }
      } // for
      return ret;
  } // else
}
APInt * api_sub (APInt *a, APInt *b){
  return NULL;
}
APInt * api_mlt (APInt *a, APInt *b);
APInt * api_dvd (APInt *a, APInt *b);
