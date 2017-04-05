/**
 * apilib-ops.c
 *   The operator functions for the arbitrary precision integers library.
 *
 * <Insert appropriate open-source license.>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "apilib.h"

// +-----------+-----------------------------------------------------
// | Operators |
// +-----------+

/**
 * Preconditions: a, b are both positive integers
 * a, b are non-null
 * BASE is less than INT_MAX / 2 (see apilib-ctors)
 * Postconditions: the resulting APInt does not have a value for
 * sign. Function is for internal library use only.
 * returns a + b, ignoring whatever sign values a and b had.
 */ 
APInt *
api_unsigned_add (APInt a*, APInt b*)
{
  api_node_t * c_cur_node, c_prev_node;
  APInt * c = (APInt *) malloc(sizeof(APInt));
  c_prev_node = NULL;
  
  api_node_t * a_cur_node = a->tail; // Starts from the lowest digits.
  api_node_t * b_cur_node = b->tail;

  int carryover = 0;
  c->size = 0;

  // Walk through linked lists and add values
  while(a_cur_node != NULL || b_cur_node != NULL)
    {
      // Node allocation and data structure positioning
      c->size++;
      c_cur_node = (api_node_t*) malloc(sizeof(api_node_t));
      if(c_prev_node == NULL)
        {
          c_tail = c_cur_node;
        }
      else
        {
          c_prev_node->next = c_cur_node;
        }
      c_cur_node->prev = c_prev_node;

      // Numerical accounting
      int sum = carryover;
      sum += a_cur_node == NULL ? 0 : a_cur_node->val;
      sum += b_cur_node == NULL ? 0 : b_cur_node->val;
      c_cur_node->val = sum % BASE;
      carryover = sum / BASE;
    
      //Transition to next node
      c_prev_node = c_cur_node;
      a_cur_node = a_cur_node == NULL ? NULL : a_cur_node->next;
      b_cur_node = b_cur_node == NULL ? NULL : b_cur_node->next;
    } // while

  // Last structure assignment
  c_cur_node->next = NULL;
  c->head = c_cur_node;

  return c;
} // api_unsigned_add

/**
 * Preconditions: a, b are both positive integers
 * a, b are non-null
 * a >= b
 * BASE is less than INT_MAX / 2 (see apilib-ctors)
 * Postconditions: the resulting APInt does not have a value for
 * sign. Function is for internal library use only.
 * returns a - b, ignoring whatever sign values a and b had.
 */
APInt *
api_unsigned_subtract (APInt a*, APInt b*)
{
  api_node_t * c_cur_node, c_prev_node;
  APInt * c = (APInt *) malloc(sizeof(APInt));
  c_prev_node = NULL;
  
  api_node_t * a_cur_node = a->tail; // Starts from the lowest digits.
  api_node_t * b_cur_node = b->tail;
  int a_place = a->size;
  
  int carryover = 0;
  c->size = 0;

  // Walk through linked lists and add value. Assumed that a is larger.
  while(a_cur_node != NULL)
    {
      // Node allocation and data structure positioning
      c->size++;
      c_cur_node = (api_node_t*) malloc(sizeof(api_node_t));
      if(c_prev_node == NULL)
        {
          c_tail = c_cur_node;
        }
      else
        {
          c_prev_node->next = c_cur_node;
        }
      c_cur_node->prev = c_prev_node;
     
      // Numerical accounting
      int sum = carryover;
      sum += a_cur_node == NULL ? 0 : a_cur_node->val;
      sum -= b_cur_node == NULL ? 0 : b_cur_node->val;
      if (sum < 0)
        {
          sum += BASE;
          carryover = -1;
        } // if
      c_cur_node->val = sum;
      
      //Transition to next node
      c_prev_node = c_cur_node;
      a_cur_node = a_cur_node->next;
      b_cur_node = b_cur_node == NULL ? NULL : b_cur_node->next;
    } // while

  // Remove leading zeroes
  // Stop if you get to the last digit
  while(c_cur_node->val == 0 && c_cur_node->prev != NULL)
    {
      c->size--;
      api_node_t * temp = c_cur_node;
      free(temp);
      c_cur_node = c_cur_node->prev;
    } // while

  // Last structure assignment
  c_cur_node->next = NULL;
  c->head = c_cur_node;
  
  return c;
} // api_unsigned_add

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt *
api_add (APInt *a, APInt *b)
{
  APInt * c;
  if (a->sign == b->sign)
    {
      c = api_unsigned_add(a, b);
      c->sign = a->sign;
    } // if
  else
    {
      if (api_unsigned_cmp(a, b) > 0) // |a| > |b|
        {
          c = api_unsigned_subtract(a, b);
          c->sign = a->sign;
        }
      else if (api_unsigned_cmp(a, b) < 0)
        {
          c = api_unsigned_subtract(b, a);
          c->sign = b->sign;
        }
      else
        {
          c = API_ZERO;
        }
    } // else

  return c;
} // api_add

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt *
api_subtract (APInt *a, APInt *b)
{
  int temp_b = (APInt*) malloc(sizeof(APInt));
  memcpy(temp_b, b, sizeof(APInt));
  temp_b->sign = 1 - b->sign;
  return api_add(a, temp_b);
} // api_subtract

/**
 * Multiply two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
APInt *
api_product (APInt *a, APInt *b)
{
  //STUB
  // Signs easy to deal with
  // product is easy with a binary representation - just bitshift
  // Helper function to bitshift across gaps?
  // Keep a running total for the sum?
} // api_product

/**
 * Find the remainder of two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
APInt *
api_remainder (APInt *a, APInt *b)
{
  //STUB
  // Binary search plus double helper function and memoizing?
} // api_remainder

/**
 * Find the quotient of two arbitrarily large integers, creating a 
 * newly allocated arbitrarily large integer.  The client is responsible 
 * for freeing any memory associated with the new value using ali_free.
 */
APInt *
api_quotient (APInt *a, APInt *b)
{
  //STUB
  // Remainder + subtraction
} // api_quotient

/**
 * Compare two API values. Return a negative number if a is 
 * less than b, 0 if they are the same, and a positive number
 * ifa is greater than b
 * Treats a and b as unsigned
 */
int * api_unsigned_cmp (APInt *a, APInt *b)
{
  // Compare based on size 
  if (a->size != b->size) return a->size - b->size;

  // Compare based on value
  // Start from the most significant digits
  api_node_t * a_cur_node = a->head;
  api_node_t * b_cur_node = b->head;

  // While the digits are the same and we are not at the last digit...
  while (a_cur_node->val == b_cur_node->val && a_cur_node->next != NULL)
    {
      // Move on
      a_cur_node = a_cur_node->prev;
      b_cur_node = b_cur_ndoe->prev;
    }

  return a_cur_node->val - b_cur_node->val;
}


/**
 * Compare two API values. Return a negative number  if the first is 
 * less than the  second, 0 if they are the same, and a positive number
 * if the first is greater than the second
 */
int * api_cmp (APInt *a, APInt *b)
{
  // Compare based on sign
  if (a->sign != b->sign) return a->sign - b->sign;

  // Multiplying by a->sign flips result if both are negative
  return api_unsigned_cmp(a, b) * a->sign;
}
