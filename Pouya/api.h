#ifndef __API__
#define __API__

#define BASE 10
struct APInt
{
  int sign;
  array_list list;
};
typedef struct APInt APInt;
/**
* apid_add, api_dub, api_mlt, api_dvd are the common arithemtic operations
*   implemented for arbitrary precision numbers.
* Each take to parameters.
* In the case of subtraction, the second will be subtracted from the first.
* In the case of division, the first will be divided by the second.
* The function will terminate and return null incase b is the equivalent of
*   zero.
*/
API * api_add (APInt *a, APInt *b);
API * api_sub (APInt *a, APInt *b);
API * api_mlt (APInt *a, APInt *b);
API * api_dvd (APInt *a, APInt *b);
API * str2api (char * i[]);
API * int2api (int i);
API * long2api (long i);
API * double2api (double i);
char * api2str (API * i);
int api2int (API * i);
long api2long (API * i);
double api2double (API * i);
void api_init();
void api_cleanup();
void api_free(ALInt *i);


#endif // __API__
