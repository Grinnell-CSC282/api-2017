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
  APInt *api1 = str2api ("1");
  APInt *api2 = str2api ("-123");
  APInt *api3 = str2api ("4");
  APInt *api4 = str2api ("456");
  APInt *api5 = str2api ("104");
  APInt *api6 = str2api ("-104");
  APInt * api7 = api_dvd(api1, api4);
  APInt * api8 = api_dvd(api1, api1);
  APInt *api9 = api_dvd (api6, api4);
  APInt * api10 = api_dvd(api4, api6);
  printf("%d\n", api2int(api7));
  printf("%d\n", api2int(api8));
  printf ("%d\n", api2int (api9));
  printf("%d\n", api2int(api10));
  api_free (api5);
  api_free (api6);
  api_free (api7);
  api_free (api8);
  api_free (api9);
  api_free (api10);
  api_free (api4);
  api_free (api1);
  api_free (api2);
  api_free (api3);
}
