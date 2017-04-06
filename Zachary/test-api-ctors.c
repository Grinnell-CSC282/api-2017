/**
 * test-api-ctors.c
 *   Tests for the constructors for the APInt library.
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
  assert (api_cmp(API_ZERO, int2api(0)) == 0);
  assert (api_cmp(API_ZERO, str2api("0")) == 0);
  assert (api_cmp(API_ZERO, long2api((long) 0)) == 0);
  assert (api_cmp(API_ZERO, double2api(0.0)) == 0);
  assert (api_cmp(API_TWO, int2api(2)) == 0);
  assert (api_cmp(API_TWO, str2api("2")) == 0);
  assert (api_cmp(API_TWO, long2api((long) 2)) == 0);
  assert (api_cmp(API_TWO, double2api(2.0)) == 0);
  
  // Larger numbers
  assert (api_cmp(int2api(large), str2api(large_str)) == 0);
  assert (api_cmp(int2api(large), long2api((long) large)) == 0);
  assert (api_cmp(int2api(large), double2api((double) large)) == 0);
  assert (api_cmp(str2api(large_long_str), long2api(large_long)) == 0);
  assert (api_cmp(str2api(large_long_str), double2api((double) large_long)) == 0);
  assert (api_cmp(long2api(large_long), double2api((double) large_long)) == 0);

  // Negative larger numbers
  assert (api_cmp(int2api(nlarge), str2api(nlarge_str)) == 0);
  assert (api_cmp(int2api(nlarge), long2api((long) nlarge)) == 0);
  assert (api_cmp(int2api(nlarge), double2api((double) nlarge)) == 0);
  assert (api_cmp(str2api(nlarge_long_str), long2api(nlarge_long)) == 0);
  assert (api_cmp(str2api(nlarge_long_str), double2api((double) nlarge_long)) == 0);
  assert (api_cmp(long2api(nlarge_long), double2api((double) nlarge_long)) == 0);

  api_cleanup();
  
  // And we're done.
  return 0;
} // main

