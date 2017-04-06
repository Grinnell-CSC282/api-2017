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
#include <limits.h>
#include <float.h>

int
main (int argc, char const *argv[])
{
  printf("Extensive testing begins.\n");
  APInt * ap_list[20];
  printf("We begin by testing api string transformations.\n");
  char * strings[] = {"", "21", "234", "324324", "3242654534",
  "1452364354216652344325", "4632187645646423524352344325432524516759",
"-", "+", "+4325435", "-43324325", "+89776", "-2452798756",
"-4326387484576543252436784958704653342"};
for (int i = 0; i < 13; i++)
{
  ap_list[i] = str2api(strings[i]);
}
for (int i = 0; i < 13; i++)
{
  printf("String %s, is api number %s\n", strings[i], api2str(ap_list[i]));
}
for (int i = 0; i < 13; i++)
{
  api_free (ap_list[i]);
}



  printf("\n\n\nAPI integer transformations\n");
  int  ints[] = {0, 1, 10, 3242332, 123, -32423, 3243, -3423, -0, -435};
  for (int i = 0; i < 10; i++)
  {
    ap_list[i] = int2api(ints[i]);
  }
  for (int i = 0; i < 10; i++)
  {
    printf("Integer %d, is api number %d\n", ints[i], api2int(ap_list[i]));
  }
  for (int i = 0; i < 10; i++)
  {
    api_free (ap_list[i]);
  }
  printf("Here, we attempt to turn two numbers that are bigger or smaller \
than integers into integers\n");
  ap_list[0] = int2api(INT_MAX);
  ap_list[1] = api_add(ap_list[0], ap_list[0]);
  ap_list[2] = int2api(INT_MIN);
  ap_list[3] = api_add(ap_list[2], ap_list[2]);
  ap_list[4] = int2api(INT_MIN+1);
  printf("INT_MAX is %d and 2 times INT_MAX is %d\n", INT_MAX, api2int(ap_list[1]));
  printf("INT_MIN is %d and 2 times INT_MIN is %d\n", INT_MIN, api2int(ap_list[3]));
  printf("INT_MIN + 1 is %d\n", api2int(ap_list[4]));
  for(int i = 0; i < 5; i++)
  {
    api_free (ap_list[i]);
  }

  printf("\n\n\nAPI Long transformations\n");
  long longs[] = {0, 1, 10, 3242332, 123242352343, -32423, -2343223443, 3423,
    -0, -43532423};
  for (int i = 0; i < 10; i++)
  {
    ap_list[i] = long2api(longs[i]);
  }
  for (int i = 0; i < 10; i++)
  {
    printf("Long %ld, is api number %ld\n", longs[i], api2long(ap_list[i]));
  }
  for (int i = 0; i < 10; i++)
  {
    api_free (ap_list[i]);
  }
  printf("Here, we attempt to turn two numbers that are bigger or smaller \
than longs into longs\n");
  ap_list[0] = long2api(LONG_MAX);
  ap_list[1] = api_add(ap_list[0], ap_list[0]);
  ap_list[2] = long2api(LONG_MIN);
  ap_list[3] = api_add(ap_list[2], ap_list[2]);
  ap_list[4] = long2api(LONG_MIN+1);
  printf("LONG_MAX is %ld and 2 times LONG_MAX is %ld\n", LONG_MAX, api2long(ap_list[1]));
  printf("LONG_MIN is %ld and 2 times LONG_MIN is %ld\n", LONG_MIN, api2long(ap_list[3]));
  printf("LONG_MIN + 1 is %ld\n", api2long(ap_list[4]));
  for(int i = 0; i < 5; i++)
  {
    api_free (ap_list[i]);
  }

  printf("\n\n\nAPI Double transformations\n");
  double doubles[] = {0, 1, 10, 3242332, 123242352343, -32423, -2343223443, 3423,
    -0, -43532423, 324234.23453, -32423.234, -6545.4352, 0.0};
  for (int i = 0; i < 14; i++)
  {
    ap_list[i] = double2api(doubles[i]);
  }
  for (int i = 0; i < 14; i++)
  {
    printf("double %f, is api number %f\n", doubles[i], api2double(ap_list[i]));
  }
  for (int i = 0; i < 14; i++)
  {
    api_free (ap_list[i]);
  }
  printf("Here, we attempt to turn two numbers that are bigger or smaller \
than longs into longs\n");
  ap_list[0] = double2api(DBL_MAX);
  ap_list[1] = api_add(ap_list[0], ap_list[0]);
  ap_list[2] = double2api(-DBL_MAX);
  ap_list[3] = api_add(ap_list[2], ap_list[2]);
  printf("DBL_MAX is %f and 2 times DBL_MAX is %f\n", DBL_MAX, api2double(ap_list[1]));
  printf("-DBL_MAX is %f and 2 times -DBL_MAX is %f\n", -DBL_MAX, api2double(ap_list[3]));
  for(int i = 0; i < 4; i++)
  {
    api_free (ap_list[i]);
  }
}
