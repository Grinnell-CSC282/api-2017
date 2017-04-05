/**
 * apilib-libctors.c
 *   The library initializer and finalizer functions for the arbitrary 
 *   precision integers library.
 *
 * <Insert appropriate open-source license.>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "apilib.h"

// +---------+-------------------------------------------------------
// | Structs |
// +---------+

#define BASE 16 // The base for numbers used in the representation.
// Should be a power of two - multiplication (and other functions)
//   are contingent on a power of two base
// Addition is also contingent on base being less than INT_MAX / 2

typedef struct api_node {
  int val; // Represents values in hex; all ints are positive
  struct api_node * next;
  struct api_node * prev;
} api_node_t;

typedef struct apint {
  int sign; // 1 for positive, 0 for negative\
  int size;
  api_node_t * head; // Points to leading digits
  api_node_t * tail; // Poitns to unit digits
} APInt;

// +-------------------+---------------------------------------------
// | Library Functions |
// +-------------------+

/**
 * Initializes constants for API library. Must be called before library
 * is used.
 */
void
api_init()
{
  APInt * API_ZERO = int2api(0);
  APInt * API_ONE = int2api(1);
  APInt * API_TWO = int2api(2);
  APInt * API_NEG_ONE = int2api(-1);
  APInt * API_NEG_TWO = int2api(-2);
} // api_init

/**
 * Removes constants for API library. Should be called before program
 * is exited.
 */
void
api_cleanup()
{
  api_free(API_ZERO);
  api_free(API_ONE);
  api_free(API_TW0);
  api_free(API_NEG_ONE);
  api_free(API_NEG_TWO);
} // api_cleanup
