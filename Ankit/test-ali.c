#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "ali_core.h"
#include "ali_arith.h"
#include "ali_conv.h"

int
main (int argc, char *argv[])
{
  // Test if our int conversions work
  assert(ali2int(int2alint(10)) == 10);
  assert(ali2int(int2alint(0)) == 0);
  assert(ali2int(int2alint(INT_MIN)) == INT_MIN);
  assert(ali2int(int2alint(INT_MAX)) == INT_MAX);
  assert(ali2int(int2alint(9299858)) == 9299858);
  assert(ali2int(int2alint(3852205)) == 3852205);

  // Test if our long conversions work
  assert(ali2long(long2alint(0)) == 0);
  assert(ali2long(long2alint(LONG_MAX)) == LONG_MAX);
  assert(ali2long(long2alint(LONG_MIN)) == LONG_MIN);
  assert(ali2long(int2alint(INT_MAX)) == INT_MAX);

  // Test integer addition
  assert(ali2int(alint_add(int2alint(1), int2alint(2))) == 3);
  assert(ali2int(alint_add(int2alint(512), int2alint(512))) == 1024);
  assert(ali2int(alint_add(int2alint(1024), int2alint(1024))) == 2048);
  assert(ali2int(alint_add(int2alint(9299858), int2alint(3852205))) == 13152063);
  assert(ali2int(alint_add(int2alint(0xFF), int2alint(0x01))) == 0x100);
  assert(ali2int(alint_add(int2alint(311), int2alint(311))) == 622);
  assert(ali2int(alint_add(int2alint(0), int2alint(0))) == 0);
  assert(ali2int(alint_add(int2alint(-10), int2alint(10))) == 0);
  
  assert(int2alint(10)->data[1] == 0);
}
