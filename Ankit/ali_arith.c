#include <limits.h>
#include "ali_core.h"
#include "ali_arith.h"

#define MAX(a,b) ((a > b) ? a : b)

alint *
alint_add (alint * a, alint * b)
{
  alint *sum = alint_init(MAX(a->size, b->size) + 1); // this is fine for now
  uint8_t carry = 0;
  int16_t byte_sum; 
  for (int i = 0; i < a->size; i++) {
    byte_sum = a->data[i] + b->data[i] + carry;
    carry = 0;
    if (byte_sum > 0xFF) {
      carry = byte_sum / 0x100;
      byte_sum = byte_sum - 0x100;
    }
    sum->data[i] = byte_sum;
  }
  return sum;
}
