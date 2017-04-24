#include "alint.c"
#include <stdio.h>
#include <assert.h>

int main(int argc, char * argv[]) {
  // creating ALInts
  ALInt * ali1 = int2ali(213);
  ALInt * ali2 = int2ali(5042);
  ALInt * ali3 = int2ali(-42);
  ALInt * ali4 = int2ali(-162);
  ALInt * ali5 = int2ali(300000);

  // checking pointers
  assert (ali2->first->value == 5);
  assert (ali2->first->prev == NULL);
  assert (ali2->first->next->prev == ali2->first);
  assert (ali2->last->next == NULL);
  assert (ali2->last->prev == ali2->first->next->next);
  assert (ali2->last->value = 2);
  assert (ali2->last->prev->prev == ali2->first->next);

  // checking ali2str
  assert (strcmp(ali2str(ali2), "5042") == 0);
  assert (strcmp(ali2str(ali1), "213") == 0);
  assert (strcmp(ali2str(ali3), "-42") == 0);

  // checking signs
  assert (ali1->sign == 1);
  assert (ali3->sign == 0);

  // checking conversions
  assert (ali2int(ali1) == 213);
  assert (ali2double(ali2) == 5042.0);
  assert (ali2long(ali3) == -42);

  assert (ali2int(double2ali(120.6)) == 120);
  assert (ali2int(int2ali(-120)) == -120);
  assert (ali2int(long2ali(45)) == 45);

  // checking ali_add
  assert (strcmp(ali2str(ali_add(ali1, ali2)), "5255") == 0);
  assert (strcmp(ali2str(ali_add(ali3, ali4)), "-204") == 0);
  assert (strcmp(ali2str(ali_add(ali5, ali2)), "305042") == 0);
  // ordering check
  assert (strcmp(ali2str(ali_add(ali2, ali5)), "305042") == 0);
  // conversion to subtraction check
  assert (strcmp(ali2str(ali_add(ali2, ali3)), "5000") == 0);
  printf("%s\n", ali2str(ali_add(ali3, ali2)));
 // assert (strcmp(ali2str(ali_add(ali3, ali2)), "5000") == 0);

  // checking ali_subtract
  assert (strcmp(ali2str(ali_subtract(ali1, ali2)), "-4829") == 0);
  printf("%s\n", ali2str(ali_subtract(ali2, ali3)));
  //assert (strcmp(ali2str(ali_subtract(ali2, ali3)), "5084") == 0);
  printf("%s\n", ali2str(ali_subtract(ali3, ali4)));
  //assert (strcmp(ali2str(ali_subtract(ali3, ali4)), "120") == 0);  
  printf("%s\n", ali2str(ali_subtract(ali5, ali1)));
  //assert (strcmp(ali2str(ali_subtract(ali5, ali1)), "299787") == 0);
  printf("%s\n", ali2str(ali_subtract(ali1, ali5)));
  //assert (strcmp(ali2str(ali_subtract(ali1, ali5)), "-299787") == 0);

  return 0;
}
