#include <stdio.h>
#include <ctype.h>
#include "api.h"
#include "array_operations.h"
//Programed implemented for base 10 at the moment
APInt *
str2api (char *i)
{
  int index = 0;
  char sign = '+';
  // finds the sign if one exists
  if (i[0] == '+')
    {
      index++;
    }
  else if (i[0] == '-')
    {
      index++;
      sign = '-';
    }
  for (; '\0' != i[index] && isdigit (i[index]); index++);
  // if the given string is an integer.
  if ('\0' == i[index])
    {
      index--;
      APInt *api = (APInt *) malloc (sizeof (APInt));
      if (sign == '+')
	{
	  api->sign = positive;
	}
      else if (sign == '-')
	{
	  api->sign = negative;
	}
      api->list = array_list_init ();
      for (; index > -1 && isdigit (i[index]); index--)
	{
	  add_last (api->list, i[index] - '0');
	}
      return api;
    }
  // if the given string is illegal
  else
    {
      printf ("Illegal characters exist in the given string\n");
      return NULL;
    }

}

char *
api2str (APInt * i)
{
  if (i->list->size == 0)
    {
      char *ret = (char *) malloc (sizeof (char));
      ret[0] = '\0';
      return ret;
    }
  char *ret = (char *) malloc (sizeof (char) * ((i->list->size) + 2));
  int j = 0;
  if (i->sign == positive)
    {
      ret[0] = '+';
    }
  else
    {
      ret[0] = '-';
    }
  for (int k = i->list->size; k > 0; k--)
    {
      ret[k] = i->list->array[j++] + '0';
    }
  ret[j] = '\0';
  return ret;
}

/*APInt * str2api (char * i){
  int index = 0;
  char sign = '+';
  // finds the sign if one exists
  if (i[0] == '+'){
    index++;
  }
  else if (i[0] == '-'){
    index++;
    sign = '-';
  }
  for (; '\0' != i[index] && isdigit(i[index]); index++);
  // if the given string is an integer.
  if ('\0' == i[index]){
    index--;
    APInt * api  = (APInt * ) malloc(sizeof(APInt));
    if (sign == '+'){
      api->sign = positive;
    }
    else if (sign == '-'){
      api->sign = negative;
    }
    api->p_list = NULL;
    api->list = array_list_init();
    for(; index > -1 && isdigit(i[index]) ; index--){
      add_last(api->list, i[index]-'0');
    }
    return api;
  }
  // if the given string is illegal
  else if ('.' != i[index] && !isdigit(i[index])){
    printf("Illegal characters exist in the given string\n");
    return NULL;
  }
  // if the given string has a '.' in it
  else if ('.' == i[index]){
    int int_size = index++ - 1;
    for (; '\0' != i[index] && isdigit(i[index]); index++);
    // if the given string is a true float
    if ('\0' == i[index]){
      APInt * api  = (APInt * ) malloc(sizeof(APInt));
      if (sign == '+'){
        api->sign = positive;
      }
      else if (sign == '-'){
        api->sign = negative;
      }
      api->p_list = array_list_init();
      int p_size = int_size + 2;
      add_last(api->p_list, 0);
      for (; i[p_size] != '\0';p_size++){
        add_last(api->p_list, i[p_size]-'0');
      }
      api->list = array_list_init();
      for(; int_size > -1 && isdigit(i[int_size]) ; int_size--){
        add_last(api->list, i[int_size]-'0');
      }

      return api;

    }
    // if the given array is illegal
    else {
      printf("Illegal characters exist in the given string\n");
      return NULL;
    }
  }
  return NULL;
}
*/
