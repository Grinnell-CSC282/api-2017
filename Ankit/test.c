#include <stdio.h>
#include <assert.h>
#include "alint.c"

int
main(int argc, char *argv[]) {
  assert(alint_init() != 0);
}
