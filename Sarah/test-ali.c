/**
 * test-ali.c
 *    Tests for the ali library.
 *
 * <insert appropriate open source license>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <assert.h>
#include <string.h>
#include "alilib.h"

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main ()
{
	// Some sample structs to work with
	ALInt * int_2034 = int2ali (2034);
	ALInt * int_1234567 = int2ali (-1234567);
	ALInt * int_5 = int2ali (5);
	ALInt * int_12 = int2ali (-12);

	// Checking that sign and ndigits are properly created
	assert (int_2034->ndigits == 4);
	assert (int_2034->sign == 1);
	assert (int_1234567->ndigits == 7);
	assert (int_1234567->sign == -1);
	assert (int_5->ndigits == 1);
	assert (int_5->sign == 1);
	assert (int_12->ndigits == 2);
	assert (int_12->sign == -1);

	// Checking that ALInts are converted to the correct long
	//assert (ali2long (int_2034) == (long) 2034);
	//assert (ali2long (int_1234567) == (long) 1234567);
	//assert (ali2long (int_5) == (long) 5);
	//assert (ali2long (int_12) == (long) 12);

	// Checking that ALInts get converted to strings properly
	assert (strcmp (ali2str (int_2034), "2034") == 0);
	assert (strcmp (ali2str (int_1234567), "1234567") == 0);
	assert (strcmp (ali2str (int_5), "5") == 0);
	assert (strcmp (ali2str (int_12), "12") == 0);

	// Check that ali_add works
	
	// Check that ali_subtract works
	
	// Check that ali_multiply works
	
	// Check that ali_quotient works
	
	// Check that ali_remainder works
	
	// Free the memory allocated
	ali_free (int_2034);
	ali_free (int_1234567);
	ali_free (int_5);
	ali_free (int_12);
	
	// Done with tests, return
	return 0;
} // main