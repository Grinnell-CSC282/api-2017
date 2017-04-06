typedef struct ALIntDigit
  {
    int val;
    struct ALIntDigit *next;
    struct ALIntDigit *prev;
  } ALIntDigit;
struct ALInt
  {
    int ndigits;
    int sign; // -1 for negative 1 for positive
    struct ALIntDigit *front;
    struct ALIntDigit *back;
  };
typedef struct ALInt ALInt;

/**
 * Free the memory associated with an ALInt.  Afterwards,
 * i should no longer be used.
 */
void ali_free (ALInt *i);

int ali_init ();

int ali_cleanup ();

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * int2ali (int i);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * str2ali (int i);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * long2ali (int i);

/**
 * Create a newly allocated ALInt whose value is i.
 */
ALInt * double2ali (int i);

/**
 * Find the long that corresponds to a.  If a > LONG_MAX,
 * returns LONG_MAX.  If a < LONG_MIN, returns LONG_MIN.
 */
long ali2long (ALInt *a);

/**
 * Convert a to string representation.  Returns a newly-allocated
 * string.
 */
char * ali2str (ALInt *a);

/**
 * Find the int that corresponds to a.
 */
long ali2int (ALInt *a);

/**
 * Find the double that corresponds to a.
 */
char * ali2double (ALInt *a);

/**
 * Add two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_add (ALInt *a, ALInt *b);

/**
 * Subtract two arbitrarily large integers, creating a newly allocated
 * arbitrarily large integer.  The client is responsible for freeing
 * any memory associated with the new value using ali_free.
 */
ALInt * ali_subtract (ALInt *a, ALInt *b);

/**
 * Multiply two arbitrarily large integers, creating a newly allocated
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
