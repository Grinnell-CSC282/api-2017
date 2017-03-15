typedef struct ALIntDigit
 {
  char val;
  struct ALIntDigit *next;
  struct ALIntDigit *prev;
 } ALIntDigit;

struct ALInt 
  {
    int length;
    int nonnegative; // 1 for positive and 0, 0 for negative
    ALIntDigit *head;
    ALIntDigit *tail;
  };

typedef struct ALInt ALInt;

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_add (ALInt *a, ALInt *b);

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_subtract (ALInt *a, ALInt *b);

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_multiply (ALInt *a, ALInt *b);

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_quotient (ALInt *a, ALInt *b);

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_remainder (ALInt *a, ALInt *b);

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void ali_free (ALInt *i);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * double2ali (double d);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * long2ali (long l);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * int2ali (int i);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * str2ali (char* str);

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
long ali2long (ALInt *a);

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
int ali2int (ALInt *a);

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
double ali2double (ALInt *a);

/**
 * Convert a to string representation.  Returns a newly-allocated
 * string.
 */
char * ali2str (ALInt *a);
