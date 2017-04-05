/**
 * apilib-ctors.c
 *   The constructor functions for the arbitrary precision integers library.
 *
 * <Insert appropriate open-source license.>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "apilib.h"

// +--------------+---------------------------------------------------
// | Constructors |
// +--------------+

/**
  * Create a newly allocated ALInt whose value is i.
  */
APInt *
int2api (int i)
{
  api_node_t * cur;
  APInt * cur_api = (APInt *) malloc(sizeof(APInt));
  cur = (api_node_t *) malloc(sizeof(api_node_t));
  cur_api->tail = cur_api->head = cur;
  cur_api->sign = i >= 0 ? 1 : 0;
  cur_api->size = 1;
  cur->next = cur->prev = NULL;
  cur->val = i >= 0 ? i : i * -1;
  return cur_api;
} // int2api

/**
  * Create a newly allocated ALInt whose value is parsed from str
  */
APInt *
str2api (char* str)
{
  // STUB
  // Abuse existing library functions?
  // String -> digit array -> binary -> ints
  // Helper functions! Yay...
} // str2api

/**
  * Create a newly allocated ALInt whose value is l.
  */
APInt *
long2api (long l)
{
  // STUB
} // long2api

/**
  * Create a newly allocated ALInt whose value is d.
  */
APInt *
double2api (double d)
{
  // STUB
} // double2api

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void
api_free (APInt *i)
{
  api_node_t * cur = i->head;
  while(cur != NULL){
    api_node_t * temp = cur;
    cur = cur->next;
    free(temp);
  }
  free(i);
} // api_free
