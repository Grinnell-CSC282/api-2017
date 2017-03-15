struct ALIntDigit
{
  byte val;
  struct ALIntDigit *next;
  struct ALIntDigit *prev;
};

struct ALInt
{
  int num_digits;
  int sign; // 1 for positive, -1 for negative
  struct ALIntDigit *first;
  struct ALIntDigit *last;
};

typedef struct ALInt ALInt;

int alint_init()
{
  // Set constants
  return 1;
}

int alint_cleanup()
{
  // Free values
  return 1;
}
