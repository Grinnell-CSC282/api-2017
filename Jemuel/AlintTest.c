#include "Alint.h"
#include <stdio.h>      // For printf and fprintf
#include <stdlib.h>     // For scanf
#include <limits.h>     // For LONG_MAX and LONG_MIN
#include <ctype.h>      // For isdigit and such.

/* Jemuel's Testing */
// ali2long ali2int ali2double
void aliConvTests(ALInt * a)
{
  ALInt * posIntTest = int2ali (37);
  ALInt * negIntTest = int2ali (-37);
  ALInt * posDoubleTest = double2ali (37.8);
  ALInt * negDoubleTest = double2ali (-37.8);
  ALInt * zeroTest = int2ali (0);
  ALInt * largePosIntTest = int2ali (28377678342);
  ALInt * largeNegIntTest = int2ali (-28377678342);

  /* Positive Integer Test */
  assert(ali2long(posIntTest) == 37);
  assert(ali2int(posIntTest) == 37);
  assert(ali2double(posIntTest) == 37);

  /* Negative Integer Test */
  assert(ali2long(negIntTest) == -37.0);
  assert(ali2int(negIntTest) == -37);
  assert(ali2double(negIntTest) == -37.0);

  /* Positive Double Test */
  assert(ali2long(posDoubleTest) == 37.8);
  assert(ali2int(posDoubleTest) == 37);
  assert(ali2double(posDoubleTest) == 37.8);

  /* Negative Double Test */
  assert(ali2long(negDoubleTest) == -37.8);
  assert(ali2int(negDoubleTest) == -38);
  assert(ali2double(negDoubleTest) == -37.8);

  /* Zero Test */
  assert(ali2long(zeroTest) == 0.0);
  assert(ali2int(zeroTest) == 0);
  assert(ali2double(zeroTest) == 0.0);

  /* Large Positive Int Test */
  assert(ali2long(largePosIntTest) == 28377678342.0);
  assert(ali2int(largePosIntTest) == 28377678342);
  assert(ali2double(largePosIntTest) == 28377678342.0);

  /* Large Negative Int Test */
  assert(ali2long(largeNegIntTest) == -28377678342.0);
  assert(ali2int(largeNegIntTest) == -28377678342);
  assert(ali2double(largeNegIntTest) == -28377678342.0);
}

int main()
{

}
