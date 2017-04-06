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
  assert(ali2int(int2alint(INT_MIN + 1)) == INT_MIN + 1);
  assert(ali2int(int2alint(INT_MAX)) == INT_MAX);
  assert(ali2int(int2alint(9299858)) == 9299858);
  assert(ali2int(int2alint(3852205)) == 3852205);
  assert(ali2int(int2alint(-2312312)) == -2312312);

  // Test if our long conversions work
  assert(ali2long(int2alint(INT_MIN)) == INT_MIN);
  assert(ali2long(long2alint(LONG_MIN)) == LONG_MIN);
  assert(ali2long(long2alint(0)) == 0);
  assert(ali2long(long2alint(LONG_MAX)) == LONG_MAX);
  assert(ali2long(int2alint(-1)) == -1);
  assert(ali2long(long2alint(-547608330240)) == -547608330240);

  //Test alint resizing
  alint *a = int2alint(10);
  alint_resize(a, sizeof(long));
  assert(ali2int(a) == 10);

  alint *b = int2alint(-10000000);
  alint_resize(b, sizeof(long));
  assert(ali2int(b) == -10000000);
  assert(b->size == sizeof(long));

  alint_free(a);
  alint_free(b);

  // Test integer addition
  assert(ali2int(alint_add(int2alint(-1), int2alint(1))) == 0);
  assert(ali2int(alint_add(int2alint(-10), int2alint(1))) == -9);
  assert(ali2int(alint_add(int2alint(1), int2alint(2))) == 3);
  assert(ali2int(alint_add(int2alint(512), int2alint(512))) == 1024);
  assert(ali2int(alint_add(int2alint(1024), int2alint(1024))) == 2048);
  assert(ali2int(alint_add(int2alint(9299858), int2alint(3852205))) == 13152063);
  assert(ali2int(alint_add(int2alint(0xFF), int2alint(0x01))) == 0x100);
  assert(ali2int(alint_add(int2alint(311), int2alint(311))) == 622);
  assert(ali2int(alint_add(int2alint(0), int2alint(0))) == 0);
  assert(ali2int(alint_add(int2alint(1), long2alint(14000))) == 14001);
}
