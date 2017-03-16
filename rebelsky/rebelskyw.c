#include <stdlib.h>
#include <stdio.h>

struct ALInt
{
  struct ALInt_node *head;
  struct ALInt_node *tail;
  unsigned int sign:1;
  unsigned long length;
};

struct ALInt_node
{
  unsigned int val:1;
  struct ALInt_node *next;
  struct ALInt_node *prev;
};

void
ali_unpad (struct ALInt *val)
{
  struct ALInt_node *current = val->tail;
  unsigned long deleted = 0;
  while (current->val == 0 && val->head != current)
    {
      current = current->prev;
      free (current->next);
      current->next = NULL;
      deleted++;
    }
  val->tail = current;
  val->length = val->length - deleted;
}

struct ALInt *
uint_to_ali (unsigned int uint)
{
  struct ALInt *result = malloc (sizeof (struct ALInt));
  struct ALInt_node *head = malloc (sizeof (struct ALInt_node));
  int length = sizeof (uint) * 8;
  result->sign = 0;             // Since we have an unsiqned integer
  result->head = head;
  result->length = length;
  head->val = uint & 1 ? 1 : 0;
  struct ALInt_node *current = head;
  struct ALInt_node *next;
  int i;
  for (i = 1; i < length; i++)
    {
      next = malloc (sizeof (struct ALInt_node));
      current->next = next;
      next->prev = current;
      current = next;
      current->val = uint & (1 << i) ? 1 : 0;
    }
  result->tail = next;
  ali_unpad (result);
  return result;
}

void
ali_delete (struct ALInt *val)
{
  struct ALInt_node *current = val->tail;
  while (current != val->head)
    {
      current = current->prev;
      free (current->next);
    }
  free (current);
  free (val);
}

void
ali_pad (struct ALInt *ali, unsigned long bits)
{
  if (bits > ali->length)
    {
      unsigned long i;
      for (i = 0; i < (bits - ali->length); i++)
        {
          struct ALInt_node *new = malloc (sizeof (struct ALInt_node));
          new->val = 0;
          new->prev = ali->tail;
          ali->tail->next = new;
          ali->tail = new;
        }
      ali->length = bits;
    }
}

char *
ali_to_str (struct ALInt *val)
{
  unsigned long length = val->length;
  char *result = malloc (sizeof (length) + 1 + val->sign);
  struct ALInt_node *current = val->head;
  result[length - 1 + val->sign] = current->val ? '1' : '0';
  int i;
  for (i = 1; i < length; i++)
    {
      current = current->next;
      result[length - 1 + val->sign - i] = current->val ? '1' : '0';
    }
  if (val->sign)
    {
      result[0] = '-';
    }
  result[length + val->sign] = '\0';
  return result;
}

struct ALInt *
ali_create_size (unsigned long length)
{
  struct ALInt *result = malloc (sizeof (struct ALInt));
  struct ALInt_node *head = malloc (sizeof (struct ALInt_node));
  head->val = 0;
  result->head = head;
  result->length = length;
  result->sign = 0;
  struct ALInt_node *prev = head;
  struct ALInt_node *new;
  unsigned long i;
  for (i = 1; i < length; i++)
    {
      new = malloc (sizeof (struct ALInt_node));
      new->val = 0;
      prev->next = new;
      new->prev = prev;
      prev = new;
    }
  result->tail = new;
  return result;
}

void
ali_copy (struct ALInt *dest, struct ALInt *src)
{
  dest->sign = src->sign;
  if (src->length > dest->length)
    {
      ali_pad (dest, src->length);
    }
  else
    {
      unsigned long i;
      struct ALInt_node *cur = dest->tail;
      for (i = 0; i < (dest->length - src->length); i++)
        {
          cur->val = 0;
          cur = cur->prev;
        }
    }
  struct ALInt_node *src_cur = src->head;
  struct ALInt_node *dest_cur = dest->head;
  //printf("dest: %s\n", ali_to_str(dest));
  unsigned long i;
  for (i = 0; i < src->length; i++)
    {
      //printf("Looping: src_cur val: %d\n", src_cur->val);
      dest_cur->val = src_cur->val;
      //printf("dest: %s\n", ali_to_str(dest));
      src_cur = src_cur->next;
      dest_cur = dest_cur->next;
    }
}

struct ALInt *
ali_help_add (struct ALInt *ali1, struct ALInt *ali2)
{
  struct ALInt *result;
  if (ali1->length >= ali2->length)
    {
      result = ali_create_size (ali1->length + 1);
    }
  else
    {
      result = ali_create_size (ali2->length + 1);
    }
  unsigned long bit;
  struct ALInt_node *a_node = ali1->head;
  struct ALInt_node *b_node = ali2->head;
  struct ALInt_node *r_node = result->head;
  int A, B;
  int C = 0;                    // Initialize carry bit so the first loop works.
  for (bit = 0; bit < result->length; bit++)
    {
      if (a_node)
        {
          A = a_node->val;
          if (a_node != ali1->tail)
            {
              a_node = a_node->next;
            }
          else
            {
              a_node = NULL;
            }
        }
      else
        {
          A = 0;
        }
      if (b_node)
        {
          B = b_node->val;
          if (b_node != ali2->tail)
            {
              b_node = b_node->next;
            }
          else
            {
              b_node = NULL;
            }
        }
      else
        {
          B = 0;
        }
      if ((A | B | C) == 0)
        {
          C = 0;
          r_node->val = 0;
        }
      else
        {
          if (A & B & C)
            {
              C = 1;
              r_node->val = 1;
            }
          else
            {
              if (A & B || A & C || B & C)
                {
                  C = 1;
                  r_node->val = 0;
                }
              else
                {
                  C = 0;
                  r_node->val = 1;
                }
            }
        }
      r_node = r_node->next;
    }
  ali_unpad (result);
  return result;
}

void
ali_left_shift (struct ALInt *ali, unsigned long bits)
{
  unsigned long bit;
  struct ALInt_node *new;
  for (bit = 0; bit < bits; bit++)
    {
      new = malloc (sizeof (struct ALInt_node));
      ali->head->prev = new;
      new->next = ali->head;
      ali->head = new;
    }
  ali->length = ali->length + bits;
}

struct ALInt *
ali_help_mult (struct ALInt *ali1, struct ALInt *ali2)
{
  struct ALInt *result = ali_create_size (ali1->length + ali2->length);
  struct ALInt *temp = ali_create_size (result->length);
  ali_copy (temp, ali1);
  //printf ("ali1, temp : %s | %s\n", ali_to_str(ali1), ali_to_str(temp));
  unsigned long bit;
  // struct ALInt_node *a_node = ali1->head;
  struct ALInt_node *b_node = ali2->head;
  //struct ALInt_node *r_node = result->head;
  //unsigned long n = 0;
  int b = 0;
  // struct ALInt_node *a_node = ali1->head;
  for (bit = 0; bit < ali2->length; bit++)
    {
      //printf("Result: %s\n", ali_to_str (result));
      //printf("Temp: %s\n", ali_to_str (temp));
      b = b_node->val;
      if (b != 0)
        {
          //struct ALInt* del = result;
          result = ali_help_add (result, temp);
          //ali_delete (del);
        }
      ali_left_shift (temp, 1);
      b_node = b_node->next;
    }
  ali_unpad (result);
  return result;
}

int
ali_help_geq (struct ALInt *ali1, struct ALInt *ali2)
{
  ali_unpad (ali1);
  ali_unpad (ali2);
  if (ali1->length > ali2->length)
    {
      return 1;
    }
  if (ali2->length > ali1->length)
    {
      return 0;
    }
  struct ALInt_node *a = ali1->tail;
  struct ALInt_node *b = ali2->tail;
  while (a->val == b->val && !(a == ali1->head))
    {
      a = a->prev;
      b = b->prev;
    }
  if (a->val == 1)
    {
      return 1;
    }
  return 0;
}

struct ALInt *
ali_help_sub (struct ALInt *ali1, struct ALInt *ali2)
{
  int C = 0;
  struct ALInt *result;
  if (ali1->length >= ali2->length)
    {
      result = ali_create_size (ali1->length);
    }
  else
    {
      result = ali_create_size (ali2->length);
    }
  struct ALInt_node *a_node;
  struct ALInt_node *b_node;
  if (ali_help_geq (ali1, ali2))
    {
      a_node = ali1->head;
      b_node = ali2->head;
    }
  else
    {
      a_node = ali2->head;
      b_node = ali1->head;
      result->sign = 1;
    }
  struct ALInt_node *r_node = result->head;
  int A, B;
  unsigned long i;
  for (i = 0; i < result->length; i++)
    {
      if (a_node)
        {
          A = a_node->val;
          if (a_node != ali1->tail)
            {
              a_node = a_node->next;
            }
          else
            {
              a_node = NULL;
            }
        }
      else
        {
          A = 0;
        }
      if (b_node)
        {
          B = b_node->val;
          if (b_node != ali2->tail)
            {
              b_node = b_node->next;
            }
          else
            {
              b_node = NULL;
            }
        }
      else
        {
          B = 0;
        }
      //printf ("A, B, C: %d, %d, %d\n", A, B, C);
      if (!(A || B || C))
        {
          C = 0;
          r_node->val = 0;
        }
      else if (!(A || B) && C)
        {
          //printf ("The case I want");
          C = 1;
          r_node->val = 1;
        }
      else if (!(A || C) && B)
        {
          C = 1;
          r_node->val = 1;
        }
      else if (!A && B && C)
        {
          C = 1;
          r_node->val = 0;
        }
      else if (A && !(B || C))
        {
          C = 0;
          r_node->val = 1;
        }
      else if (A && C && !B)
        {
          C = 0;
          r_node->val = 0;
        }
      else if (A && B && !C)
        {
          C = 0;
          r_node->val = 0;
        }
      else if (A && B && C)
        {
          C = 1;
          r_node->val = 1;
        }
      //printf ("C, r_node: %d, %d\n", C, r_node->val);
      r_node = r_node->next;
    }
  ali_unpad (result);
  return result;
}

struct ALInt *
ali_add (struct ALInt *ali1, struct ALInt *ali2)
{
  struct ALInt *result;
  int sign1 = ali1->sign;
  int sign2 = ali2->sign;
  if (!(sign1 || sign2))
    {
      result = ali_help_add (ali1, ali2);
      result->sign = 0;
      return result;
    }
  if (!(sign1) && sign2)
    {
      return ali_help_sub (ali1, ali2);
    }
  if (sign1 && !(sign2))
    {
      return ali_help_sub (ali2, ali1);
    }
  if (sign1 && sign2)
    {
      result = ali_help_add (ali1, ali2);
      result->sign = 1;
      return result;
    }
  return NULL;
}

struct ALInt *
ali_sub (struct ALInt *ali1, struct ALInt *ali2)
{
  ali2->sign = ali2->sign ? 0 : 1;
  return ali_add (ali1, ali2);
}

struct ALInt *
ali_mult (struct ALInt *ali1, struct ALInt *ali2)
{
  int sign1 = ali1->sign;
  int sign2 = ali2->sign;
  if (sign1 == sign2)
    {
      return ali_help_mult (ali1, ali2);
    }
  else
    {
      struct ALInt *result = ali_help_mult (ali1, ali2);
      result->sign = 1;
      return result;
    }
}

int
main (int argc, char **argv)
{
  struct ALInt *a = uint_to_ali (atoi (argv[1]));
  struct ALInt *b = uint_to_ali (atoi (argv[2]));
  a->sign = atoi (argv[3]);
  b->sign = atoi (argv[4]);
  printf (ali_to_str (ali_mult (a, b)));
  printf ("\n");
  ali_delete (a);
  ali_delete (b);
  return 0;
}
