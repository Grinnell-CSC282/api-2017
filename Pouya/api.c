/**
* Program made to store arbitrary large numbers.
* Created by : PMR
* Course : CSC 282
* Instructor: SamR
--------------------------------------------------------------------------------
* Implementation:
*     Numbers are stored using arrayLists. A set of functions are defined to
*       have the same arithemtic abilities as integers.
--------------------------------------------------------------------------------
* Library headers:
*     array_operations.h : header for the arrayList operatoins.
*     api.h              : header for the api operatoins.
--------------------------------------------------------------------------------
* Libraries:
*
--------------------------------------------------------------------------------
* Files:
*
--------------------------------------------------------------------------------
* In-depth discription of the Implementation:
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "array_operations.h"

int main(int argc, char const *argv[]) {
  array_list  * arr = array_list_init();
  for (int i = 0; i < 100; i++){
    add_last(arr, i);
  }
  for (int i = 0; i < 100; i++){
    printf("%d ", arr->array[i]);
  }
  free_list(arr);
}
