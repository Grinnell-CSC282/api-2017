/**
 * test-api-ops.c
 *   Tests for the operations for the APInt Library
 *
 * <Insert appropriate open-source license.>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <assert.h>
#include <limits.h>
#include "apilib.h"

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[<a href="#referent" id="reference"></a>])
{

  // Operations with constants
  
  // Comparison
  assert (api_cmp(API_ZERO,    API_ZERO)     == 0);
  assert (api_cmp(API_ZERO,    API_ONE)      == -1);
  assert (api_cmp(API_ONE,     API_ZERO)     == 1);
  assert (api_cmp(API_NEG_ONE, API_ZERO)     == 1);
  assert (api_cmp(API_ZERO,    API_NEG_ONE)  == -1);
  assert (api_cmp(API_ONE,     API_ONE)      == 0);
  assert (api_cmp(API_NEG_ONE, API_NEG_ONE)  == 0);
  
  // addition
  assert (api_cmp(api_add(API_ONE,     API_ONE),     API_TWO) == 0);
  assert (api_cmp(api_add(API_ZERO,    API_ONE),     API_ONE) == 0);
  assert (api_cmp(api_add(API_ONE,     API_ZERO),    API_ONE) == 0);
  assert (api_cmp(api_add(API_NEG_ONE, API_ONE),     API_ZERO) == 0); 
  assert (api_cmp(api_add(API_ONE,     API_NEG_ONE), API_ZERO) == 0);
  assert (api_cmp(api_add(API_TWO,     API_NEG_ONE), API_ONE) == 0);

  // subtraction
  assert (api_cmp(api_subtract(API_ZERO,    API_ZERO),    API_ZERO) == 0);
  assert (api_cmp(api_subtract(API_ONE,     API_ONE),     API_ZERO) == 0);
  assert (api_cmp(api_subtract(API_ZERO,    API_ONE),     API_NEG_ONE) == 0);
  assert (api_cmp(api_subtract(API_ONE,     API_ZERO),    API_ONE) == 0);
  assert (api_cmp(api_subtract(API_ONE,     API_NEG_ONE), API_TWO) == 0);
  assert (api_cmp(api_subtract(API_NEG_ONE, API_ONE),     API_NEG_TWO) == 0);
  assert (api_cmp(api_subtract(API_TWO,     API_ONE),     API_ONE) == 0);
  
  // product
  assert (api_cmp(api_product(API_ZERO,    API_ZERO),    API_ZERO) == 0);
  assert (api_cmp(api_product(API_ONE,     API_ONE),     API_ONE) == 0);
  assert (api_cmp(api_product(API_ZERO,    API_ONE),     API_ZERO) == 0);
  assert (api_cmp(api_product(API_ONE,     API_ZERO),    API_ZERO) == 0);
  assert (api_cmp(api_product(API_ONE,     API_NEG_ONE), API_NEG_ONE) == 0);
  assert (api_cmp(api_product(API_NEG_ONE, API_ONE),     API_NEG_ONE) == 0);
  assert (api_cmp(api_product(API_TWO,     API_ONE),     API_TWO) == 0);
  assert (api_cmp(api_product(API_TWO,     API_ZERO),    API_ZERO) == 0);

  // remainder
  assert (api_cmp(api_remainder(API_ONE,     API_ONE),     API_ZERO) == 0);
  assert (api_cmp(api_remainder(API_ZERO,    API_ONE),     API_ZERO) == 0);
  assert (api_cmp(api_remainder(API_ONE,     API_NEG_ONE), API_ZERO) == 0);
  assert (api_cmp(api_remainder(API_NEG_ONE, API_ONE),     API_ZERO) == 0);
  assert (api_cmp(api_remainder(API_TWO,     API_ONE),     API_ZER0) == 0);
  assert (api_cmp(api_remainder(API_ONE,     API_TWO),     API_ONE) == 0);

  // quotient
  assert (api_cmp(api_quotient(API_ONE,     API_ONE),     API_ONE) == 0);
  assert (api_cmp(api_quotient(API_ZERO,    API_ONE),     API_ZERO) == 0);
  assert (api_cmp(api_quotient(API_ONE,     API_NEG_ONE), API_NEG_ONE) == 0);
  assert (api_cmp(api_quotient(API_NEG_ONE, API_ONE),     API_NEG_ONE) == 0);
  assert (api_cmp(api_quotient(API_TWO,     API_ONE),     API_TWO) == 0);
  assert (api_cmp(api_quotient(API_ONE,     API_TWO),     API_ZERO) == 0);
  
  // And we're done.
  return 0;
} // main

