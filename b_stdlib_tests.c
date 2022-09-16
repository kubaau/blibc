#include "b_stdlib.h"

#include "b_assert.h"
#include "b_limits.h"

#define B_DEFINE_INTEGER_COMPARE(type)                                        \
  static int b_compare_##type (const void *a, const void *b)                  \
  {                                                                           \
    const type arg1 = *(const type *)a;                                       \
    const type arg2 = *(const type *)b;                                       \
    return (arg1 > arg2) - (arg1 < arg2);                                     \
  }

B_DEFINE_INTEGER_COMPARE (int)
B_DEFINE_INTEGER_COMPARE (short)

void
test_qsort_b_bsearch (void)
{
  short shorts[] = { -2, 99, 0, -743, 2, -10000, 4 };
  int ints[] = { -2, 99, 0, -743, 2, B_INT_MIN, 4 };
  short s;
  int i;

  b_qsort (ints, sizeof (ints) / sizeof (*ints), sizeof (int), b_compare_int);
  b_assert (ints[0] == B_INT_MIN);
  b_assert (ints[1] == -743);
  b_assert (ints[2] == -2);
  b_assert (ints[3] == 0);
  b_assert (ints[4] == 2);
  b_assert (ints[5] == 4);
  b_assert (ints[6] == 99);

  b_qsort (shorts, sizeof (shorts) / sizeof (*shorts), sizeof (short),
           b_compare_short);
  b_assert (shorts[0] == -10000);
  b_assert (shorts[1] == -743);
  b_assert (shorts[2] == -2);
  b_assert (shorts[3] == 0);
  b_assert (shorts[4] == 2);
  b_assert (shorts[5] == 4);
  b_assert (shorts[6] == 99);

#define B_BSEARCH_TEST_INTS                                                   \
  ((const int *)b_bsearch (&i, ints, sizeof (ints) / sizeof (*ints),          \
                           sizeof (int), b_compare_int))
  i = B_INT_MIN;
  b_assert (B_BSEARCH_TEST_INTS - ints == 0);
  i = -743;
  b_assert (B_BSEARCH_TEST_INTS - ints == 1);
  i = -2;
  b_assert (B_BSEARCH_TEST_INTS - ints == 2);
  i = 0;
  b_assert (B_BSEARCH_TEST_INTS - ints == 3);
  i = 2;
  b_assert (B_BSEARCH_TEST_INTS - ints == 4);
  i = 4;
  b_assert (B_BSEARCH_TEST_INTS - ints == 5);
  i = 99;
  b_assert (B_BSEARCH_TEST_INTS - ints == 6);

#define B_BSEARCH_TEST_SHORTS                                                 \
  ((const short *)b_bsearch (&s, shorts, sizeof (shorts) / sizeof (*shorts),  \
                             sizeof (short), b_compare_short))
  s = -10000;
  b_assert (B_BSEARCH_TEST_SHORTS - shorts == 0);
  s = -743;
  b_assert (B_BSEARCH_TEST_SHORTS - shorts == 1);
  s = -2;
  b_assert (B_BSEARCH_TEST_SHORTS - shorts == 2);
  s = 0;
  b_assert (B_BSEARCH_TEST_SHORTS - shorts == 3);
  s = 2;
  b_assert (B_BSEARCH_TEST_SHORTS - shorts == 4);
  s = 4;
  b_assert (B_BSEARCH_TEST_SHORTS - shorts == 5);
  s = 99;
  b_assert (B_BSEARCH_TEST_SHORTS - shorts == 6);
}

void
test_atoi (void)
{
  b_assert (b_atoi ("42") == 42);
  b_assert (b_atoi ("  42") == 42);
  b_assert (b_atoi (" +42") == 42);
  b_assert (b_atoi (" -42") == -42);
  b_assert (b_atoi (" 42abc") == 42);
  b_assert (b_atoi (" 3.14") == 3);
  b_assert (b_atoi ("") == 0);
  b_assert (b_atoi ("+") == 0);
  b_assert (b_atoi ("-") == 0);
  b_assert (b_atoi ("abc") == 0);
}

void
test_atol (void)
{
  b_assert (b_atol ("42") == 42);
  b_assert (b_atol ("  42") == 42);
  b_assert (b_atol (" +42") == 42);
  b_assert (b_atol (" -42") == -42);
  b_assert (b_atol (" 42abc") == 42);
  b_assert (b_atol (" 3.14") == 3);
  b_assert (b_atol ("") == 0);
  b_assert (b_atol ("+") == 0);
  b_assert (b_atol ("-") == 0);
  b_assert (b_atol ("abc") == 0);
}

void
test_malloc (void)
{
  char *cp1;
  char *cp2;
  int *ip1;
  int *ip2;

  cp1 = b_malloc (1);
  b_assert (cp1);

  cp2 = b_malloc (0);
  b_assert (cp2 - cp1 == 1);

  ip1 = b_malloc (sizeof (int));
  b_assert ((b_size_t)ip1 % sizeof (int) == 0);

  ip2 = b_malloc (sizeof (int));
  b_assert (ip2 - ip1 == 1);
  b_assert ((b_size_t)ip2 % sizeof (int) == 0);

  cp1 = b_malloc (1024);
  b_assert (cp1 == B_NULL);
  b_free (cp1);
}

void
test_calloc (void)
{
  char *cp1;
  char *cp2;
  int *ip1;
  int *ip2;
  int i;

  cp1 = b_calloc (1, 1);
  b_assert (cp1);

  cp2 = b_calloc (1, 0);
  b_assert (cp2 - cp1 == 1);

  cp1 = b_calloc (0, 1);
  b_assert (cp1 - cp2 == 1);

  ip1 = b_calloc (1, sizeof (int));
  b_assert ((b_size_t)ip1 % sizeof (int) == 0);

  ip2 = b_calloc (10, sizeof (int));
  b_assert (ip2 - ip1 == 1);
  b_assert ((b_size_t)ip2 % sizeof (int) == 0);

  for (i = 0; i < 10; ++i)
  {
    b_assert(ip2[i] == 0);
  }

  ip1 = b_calloc (2, sizeof (int));
  b_assert (ip1 - ip2 == 10);
  b_assert ((b_size_t)ip1 % sizeof (int) == 0);

  cp1 = b_calloc (32, 32);
  b_assert (cp1 == B_NULL);
  b_free (cp1);
}

void
test_realloc (void)
{
}
