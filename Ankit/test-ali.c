#include <assert.h>
#include <stdio.h>
#include "ali_core.h"
#include "ali_arith.h"
#include "ali_conv.h"

int
main (int argc, char *argv[])
{
  assert(ali2int(int2alint(10)) == 10);
  assert(ali2int(int2alint(0)) == 0);
  assert(ali2int(long2alint(10)) == 10);
  assert(int2alint(10)->data[1] == 0);
}
