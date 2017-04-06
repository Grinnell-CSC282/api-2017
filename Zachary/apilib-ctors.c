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
  return long2api((long) i);
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
  if(val == 0) return API_ZERO; // Easy early test
  
  api_node_t * cur, prev;
  APInt * cur_api = (APInt *) malloc(sizeof(APInt));
  cur_api->size = 0;
  prev = NULL;
  long val = i >= 0 i : i * -1;
  
  while(val > 0)
    {
      // Linked list maintenance
      cur = (api_node_t *) malloc(sizeof(api_node_t));
      cur_api->size++;
      if (prev == NULL)
        {
          cur_api->tail = cur;
        }
      else
        {
          prev->next = cur;
        }
      cur->prev = prev;

      // Set node value; adjust
      cur->val = val % BASE;
      val = val / BASE; // Division in c rounds down.

      prev = cur;
    }
  cur->next = NULL;
  cur_api->head = cur; // head is most significant bits

  cur_api->sign = i >= 0 ? 1 : 0;
  return cur_api;
} // long2api

/**
  * Create a newly allocated ALInt whose value is d.
  */
APInt *
double2api (double d)
{
  if(val == 0) return API_ZERO; // Easy early test
  
  api_node_t * cur, prev;
  APInt * cur_api = (APInt *) malloc(sizeof(APInt));
  cur_api->size = 0;
  prev = NULL;
  double val = i >= 0 i : i * -1;
  
  while(val > 0)
    {
      // Linked list maintenance
      cur = (api_node_t *) malloc(sizeof(api_node_t));
      cur_api->size++;
      if (prev == NULL)
        {
          cur_api->tail = cur;
        }
      else
        {
          prev->next = cur;
        }
      cur->prev = prev;

      // Set node value; adjust
      cur->val = val % BASE;
      val = val / BASE; // Division in c rounds down.

      prev = cur;
    }
  cur->next = NULL;
  cur_api->head = cur; // head is most significant bits

  cur_api->sign = i >= 0 ? 1 : 0;
  return cur_api;
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
