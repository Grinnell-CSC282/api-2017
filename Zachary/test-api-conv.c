/**
 * test-api-conv.c
 *   Tests for the conversion functions for the APInt library.
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

  int    large = 10000;
  char*  large_str = "10000";
  long   large_long = 72036854775808;
  char*  large_long_str = "72036854775808";
  int    nlarge = -10000;
  char*  nlarge_str = "-10000";
  long   nlarge_long = -72036854775808;
  char*  nlarge_long_str = "-72036854775808";

  api_init();
  
  // Constants
  assert (api2int(API_ZERO) == 0);
  assert (strcmp(api2str(API_ZERO), "0")  == 0);
  assert (api2long(API_ZERO) == (long) 0);
  assert (api2double(API_ZERO) == (double) 0);
  assert (api2int(API_TWO) == 2);
  assert (strcmp(api2str(API_TWO), "2")  == 0);
  assert (api2long(API_TWO) == (long) 2);
  assert (api2double(API_TWO) == (double) 2);
  
  // Larger numbers - Assumes constructors work
  assert (api2int(str2api(large_str)) == large);
  assert (api2long(str2api(large_long_str)) == large_long);
  assert (api2double(str2api(large_long_str)) == (double) large_long);
  assert (strcmp(large_long_str, long2api(large_long)) == 0);
  
  // Negative larger numbers
  assert (api2int(str2api(nlarge_str)) == nlarge);
  assert (api2long(str2api(nlarge_long_str)) == nlarge_long);
  assert (api2double(str2api(nlarge_long_str)) == (double) nlarge_long);
  assert (strcmp(nlarge_long_str, long2api(nlarge_long)) == 0);
  
  api_cleanup();
  
  // And we're done.
  return 0;
} // main
