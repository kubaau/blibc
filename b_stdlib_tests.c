#include "b_stdlib.h"

#include "b_assert.h"

#define B_INTERNAL_DEFINE_INTEGER_COMPARE(type)                               \
  static int b_internal_compare_##type (const void *a, const void *b)         \
  {                                                                           \
    const type arg1 = *(const type *)a;                                       \
    const type arg2 = *(const type *)b;                                       \
    return (arg1 > arg2) - (arg1 < arg2);                                     \
  }
B_INTERNAL_DEFINE_INTEGER_COMPARE (int)
B_INTERNAL_DEFINE_INTEGER_COMPARE (short)
#undef B_INTERNAL_DEFINE_INTEGER_COMPARE

void
b_test_qsort_b_bsearch (void)
{
  short shorts[] = { -2, 99, 0, -743, 2, -10000, 4 };
  int ints[] = { -2, 99, 0, -743, 2, -10000, 4 };
  short s;
  int i;

  b_qsort (ints, sizeof (ints) / sizeof (*ints), sizeof (int),
           b_internal_compare_int);
  b_assert (ints[0] == -10000);
  b_assert (ints[1] == -743);
  b_assert (ints[2] == -2);
  b_assert (ints[3] == 0);
  b_assert (ints[4] == 2);
  b_assert (ints[5] == 4);
  b_assert (ints[6] == 99);

  b_qsort (shorts, sizeof (shorts) / sizeof (*shorts), sizeof (short),
           b_internal_compare_short);
  b_assert (shorts[0] == -10000);
  b_assert (shorts[1] == -743);
  b_assert (shorts[2] == -2);
  b_assert (shorts[3] == 0);
  b_assert (shorts[4] == 2);
  b_assert (shorts[5] == 4);
  b_assert (shorts[6] == 99);

#define B_INTERNAL_BSEARCH_TEST                                               \
  ((const int *)b_bsearch (&i, ints, sizeof (ints) / sizeof (*ints),          \
                           sizeof (int), b_internal_compare_int))
  i = -10000;
  b_assert (B_INTERNAL_BSEARCH_TEST - ints == 0);
  i = -743;
  b_assert (B_INTERNAL_BSEARCH_TEST - ints == 1);
  i = -2;
  b_assert (B_INTERNAL_BSEARCH_TEST - ints == 2);
  i = 0;
  b_assert (B_INTERNAL_BSEARCH_TEST - ints == 3);
  i = 2;
  b_assert (B_INTERNAL_BSEARCH_TEST - ints == 4);
  i = 4;
  b_assert (B_INTERNAL_BSEARCH_TEST - ints == 5);
  i = 99;
  b_assert (B_INTERNAL_BSEARCH_TEST - ints == 6);
#undef B_INTERNAL_BSEARCH_TEST

#define B_INTERNAL_BSEARCH_TEST                                               \
  ((const short *)b_bsearch (&s, shorts, sizeof (shorts) / sizeof (*shorts),  \
                             sizeof (short), b_internal_compare_short))
  s = -10000;
  b_assert (B_INTERNAL_BSEARCH_TEST - shorts == 0);
  s = -743;
  b_assert (B_INTERNAL_BSEARCH_TEST - shorts == 1);
  s = -2;
  b_assert (B_INTERNAL_BSEARCH_TEST - shorts == 2);
  s = 0;
  b_assert (B_INTERNAL_BSEARCH_TEST - shorts == 3);
  s = 2;
  b_assert (B_INTERNAL_BSEARCH_TEST - shorts == 4);
  s = 4;
  b_assert (B_INTERNAL_BSEARCH_TEST - shorts == 5);
  s = 99;
  b_assert (B_INTERNAL_BSEARCH_TEST - shorts == 6);
#undef B_INTERNAL_BSEARCH_TEST
}

void
b_test_atoi (void)
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
b_test_atol (void)
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
b_test_malloc (void)
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
b_test_calloc (void)
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
      b_assert (ip2[i] == 0);
    }

  ip1 = b_calloc (2, sizeof (int));
  b_assert (ip1 - ip2 == 10);
  b_assert ((b_size_t)ip1 % sizeof (int) == 0);

  cp1 = b_calloc (32, 32);
  b_assert (cp1 == B_NULL);
  b_free (cp1);
}

void
b_test_realloc (void)
{
}
