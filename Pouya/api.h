

#ifndef __API__
#define __API__
#include <stdint.h>

#define BASE 10
struct APInt
{
  size_t size;
  int sign;
  unsigned char arr[16];
};
typedef struct APInt APInt;

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
