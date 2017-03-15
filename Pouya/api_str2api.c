#include <stdio.h>
#include <ctype.h>
#include "api.h"
#include "array_operations.h"
//Programed implemented for base 10 at the moment
APInt * str2api (char * i){
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
    api->base = 10;
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
  else if ('.' != i[index] && !isdigit(i[index])){
    printf("Illegal charachters exist in the given string\n");
    return 0;
  }
  else if ('.' == i[index]){
    printf("float\n");
    return 0;
  }
  return 0;
}
