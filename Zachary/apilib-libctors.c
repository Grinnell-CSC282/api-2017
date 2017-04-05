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

typedef struct api_node {
  int val;
  struct api_node * next;
  struct api_node * prev;
} api_node_t;

typedef struct apint {
  int sign; // 1 for positive, 0 for negative
  api_node_t * head;
  api_node_t * tail;
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
