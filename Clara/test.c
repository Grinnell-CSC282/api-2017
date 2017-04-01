#include "alint.c"
#include <stdio.h>

int main(int argc, char * argv[]) {
  ALInt * ali = int2ali(213);

  printf("Printing...\n");
  printf("Integer = 213\n");
  printf("First value: %d\n", ali->first->value);
  printf("Last value: %d\n", ali->last->value);
  
  printf("Printing string representation...\n");
  printf("%s\n", ali2str(ali));

  return 0;
}
