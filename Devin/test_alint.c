#include <assert.h>
#include <limits.h>
#include "alint.h"

int
main (int argc, char *argv[])
{ 
  // Initialize alint library
  alint_init();

  // Test strings
  ALInt *str_ali;
  char *test_str = "1234567890";
  str_ali = str_to_alint(test_str);
  char *result_str;
  result_str = alint_to_str(str_ali);
  assert(test_str == result_str);
   
  // Test integers
  ALInt *int_ali;
  int test_int = 938401234; // Should be one digit less than max
  int_ali = int_to_alint(test_int); 
  int result_int;
  result_int = alint_to_int(int_ali);
  assert(test_int == result_int);
  
  // Test longs
  ALInt *long_ali;
  long test_long = 28394012345;
  long_ali = long_to_alint(test_long);
  long result_long;
  result_long = alint_to_long(long_ali);
  assert(test_long == result_long);
  
  // Test doubles
  ALInt *double_ali;
  double test_double = 123456863;
  double_ali = double_to_alint(test_double);
  double result_double;
  result_double = alint_to_double(double_ali);
  assert(test_double == result_double);

  // Test arithmetic operations, add more cases time permitting
  // Edge cases to test: negatives, uneven division, larger numbers, 0
  ALInt *x = int_to_alint(12);
  ALInt *y = int_to_alint(6);
  ALInt *add_result = alint_add(x, y);
  ALInt *sub_result = alint_sub(x, y);
  ALInt *mul_result = alint_mul(x, y);
  ALInt *div_result = alint_div(x, y);
  ALInt *mod_result = alint_remainder(x, y);

  assert(add_result = int_to_alint(18));
  assert(sub_result = int_to_alint(6));
  assert(mul_result = int_to_alint(72));
  assert(div_result = int_to_alint(2));
  assert(mod_result = int_to_alint(0));

  // Future tests should include the cleanup and free functions,
  // and operations throwing errors when they pass values from limits.h

  return 0;
}
