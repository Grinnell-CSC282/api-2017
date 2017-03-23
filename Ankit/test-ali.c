#include <stdio.h>
#include <assert.h>
#include "ali.h"

int
main(int argc, char *argv[]) {
  assert(alint_init(sizeof(int)) != 0);
}
