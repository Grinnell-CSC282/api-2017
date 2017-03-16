#include "alint.h"

#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

void 
testNormalInt() {
  ALInt *i = str2ali("100"); 
  assert( ali2int(i) == 100 );
  assert( ali2double(i) == 100.0 );
  assert( ali2long(i) == 100.0 );

  char *str = ali2str(i);
  assert (strcmp(str,"100") == 0);

  ali_free(i);
  free(str);
}

void testNegativeInt() {
  ALInt *i = str2ali("-100"); 
  assert( ali2int(i) == -100 );
  assert( ali2double(i) == -100.0 );
  assert( ali2long(i) == -100.0 );

  char *str = ali2str(i);
  assert (strcmp(str,"-100") == 0);

  ali_free(i);
  free(str);
}

void 
testNormalDouble() {
  ALInt *i = double2ali(100.0); 
  assert( ali2int(i) == 100 );
  assert( ali2double(i) == 100.0 );
  assert( ali2long(i) == 100.0 );

  char *str = ali2str(i);
  assert (strcmp(str,"100") == 0);

  ali_free(i);
  free(str);
}

void testNegativeDouble() {
  ALInt *i = double2ali(-100.0); 
  assert( ali2int(i) == -100 );
  assert( ali2double(i) == -100.0 );
  assert( ali2long(i) == -100.0 );

  char *str = ali2str(i);
  assert (strcmp(str,"-100") == 0);

  ali_free(i);
  free(str);
}

void testNegativeLargeInt() {
  ALInt *i = str2ali("-5256008675309"); 
  assert( ali2int(i) == -INT_MAX );

  char *str = ali2str(i);
  assert (strcmp(str,"-5256008675309") == 0);

  ali_free(i);
  free(str);
}

void
testLargeInt() {
  ALInt *i = str2ali("5256008675309"); 
  assert( ali2int(i) == INT_MAX );

  char *str = ali2str(i);
  assert (strcmp(str,"5256008675309") == 0);

  ali_free(i);
  free(str);
}

int
main (int argc, char *argv[])
{
  testNormalInt();
  testLargeInt();
  testNegativeInt();
  testNegativeLargeInt();
  testNormalDouble();
  testNegativeDouble();
}
