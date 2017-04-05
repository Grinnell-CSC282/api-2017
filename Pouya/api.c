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

int
main (int argc, char const *argv[])
{
  APInt *api1 = str2api ("15");
  printf ("%s\n", api2str (api1));
  APInt *api2 = str2api ("-4");
  printf ("%s\n", api2str (api2));
  APInt *api3 = api_add (api2, api1);
  printf ("%s\n", api2str (api3));
  APInt *api4 = api_sub (api1, api2);
  printf ("%s\n", api2str (api4));
  APInt *api5 = api_dvd (api1, api2);
  printf ("%s\n", api2str (api5));
  APInt *api6 = api_mlt (api2, api1);
  printf ("%s\n", api2str (api6));

  //APInt *api5 = str2api("12");
  //APInt *api6 = api_sub(api1, api5);
  //printf("%s\n", api2str(api6));
  //printf("%d\n", api6->list->size);
  api_free (api5);
  api_free (api6);
  api_free (api4);
  api_free (api1);
  api_free (api2);
  api_free (api3);
}
