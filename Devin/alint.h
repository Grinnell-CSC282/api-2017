typedef struct 
{
  unsigned int val;
  struct ALIntDigit *next;
  struct ALIntDigit *prev;
} ALIntDigit;

typedef struct 
{
  int num_digits;
  int sign; // 1 for positive, -1 for negative
  struct ALIntDigit *first;
  struct ALIntDigit *last;
} ALInt;

int alint_init;
int alint_cleanup;
