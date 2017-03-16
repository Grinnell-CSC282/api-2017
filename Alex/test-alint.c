#include "alint.h"

#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  ALInt *i = str2ali("100"); 
  assert( ali2int(i) == 100 );

  char *str = ali2str(i);
  assert (strcmp(str,"100") == 0);

  ali_free(i);
  free(str);
  i = str2ali("5256008675309"); 
  assert( ali2int(i) == INT_MAX );

  str = ali2str(i);
  assert (strcmp(str,"5256008675309") == 0);
}
