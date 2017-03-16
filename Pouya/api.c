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
#include "api.h"

int main(int argc, char const *argv[]) {
  APInt * api1 = str2api("123");
  APInt * api2 = str2api("356");
  APInt * api3 = api_add(api2, api1);
  printf("%d\n", api2int(api1));
  printf("%d\n", api2int(api2));
  printf("%d\n", api2int(api3));
  api_free(api1);
  api_free(api2);
  api_free(api3);
}
