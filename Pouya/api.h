#ifndef __API__
#define __API__

#include "array_operations.h"
#define BASE 10

enum int_sign{
  positive,
  negative
};

struct APInt
{
  int base;
  enum int_sign sign;
  array_list * list;
  array_list * p_list;
};
typedef struct APInt APInt;
/**
* apid_add, api_dub, api_mlt, api_dvd are the common arithemtic operations
*   implemented for arbitrary precision numbers.
* Each take two parameters.
* In the case of subtraction, the second will be subtracted from the first.
* In the case of division, the first will be divided by the second.
* The function will terminate and return null incase b is the equivalent of
*   zero.
*/
APInt * api_add (APInt *a, APInt *b);
APInt * api_sub (APInt *a, APInt *b);
APInt * api_mlt (APInt *a, APInt *b);
APInt * api_dvd (APInt *a, APInt *b);
APInt * str2api (char * i);
APInt * int2api (int i);
APInt * long2api (long i);
APInt * double2api (double i);
char * api2str (APInt * i);
int api2int (APInt * i);
long api2long (APInt * i);
double api2double (APInt * i);
void api_init();
void api_cleanup();
void api_free(APInt *i);


#endif // __API__
