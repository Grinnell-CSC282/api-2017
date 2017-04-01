#include "alint.c"
#include <stdio.h>
#include <assert.h>

int main(int argc, char * argv[]) {
  ALInt * ali1 = int2ali(213);
  ALInt * ali2 = int2ali(5042);

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

  //assert (strcmp(ali2str(ali_add(ali1, ali2)), "5255") == 0);

  return 0;
}
