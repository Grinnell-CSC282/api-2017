#include <stdint.h>
#include <stddef.h>

#define ALI_BLOCK_SIZE 16

typedef uint8_t data_t;

typedef struct {
data_t * data;
size_t size;
size_t max_size;
} alint;


alint * ali_add (alint *, alint *);
void ali_free(alint *);
alint * alint_init();
long ali2long (alint *);
char * ali2str (alint *);
int ali2int (alint *);
double ali2double (alint *);

alint * long2alint (long);
alint * str2alint (char*);
alint * int2alint (int);
alint * double2alint (double);
