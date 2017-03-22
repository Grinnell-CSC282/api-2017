#include <stdint.h>

#define ALI_BLOCK_SIZE 16

typedef uint8_t * alint;

alint * ali_add (alint *, alint *);
void ali_free(alint *);
long ali2long (alint *);
char * ali2str (alint *);
int ali2int (alint *);
double ali2double (alint *);

alint * long2alint (long);
alint * str2alint (char*);
