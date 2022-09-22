#include "b_stdlib.h"

#include "b_assert.h"
#include "b_stddef.h"

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
  typedef struct
  {
    long l1;
    long l2;
  } test;

  short *s;
  char *c;
  long *l;
  test *t;
  int *i;

  b_free (b_malloc (0));

#define B_INTERNAL_MALLOC_TEST(var)                                           \
  var = b_malloc (sizeof (*var));                                             \
  b_assert (var);                                                             \
  b_assert ((b_size_t)var % sizeof (*var) == 0);                              \
  *var = 42;                                                                  \
  b_assert (*var == 42);                                                      \
  b_free (var);

  B_INTERNAL_MALLOC_TEST (c)
  B_INTERNAL_MALLOC_TEST (s)
  B_INTERNAL_MALLOC_TEST (i)
  B_INTERNAL_MALLOC_TEST (l)
#undef B_INTERNAL_MALLOC_TEST

  t = b_malloc (sizeof (*t));
  b_assert (t);
  b_assert ((b_size_t)t % sizeof (*t) == 0);
  t->l1 = 42;
  t->l2 = 43;
  b_assert (t->l1 == 42);
  b_assert (t->l2 == 43);
  b_free_sized (t, sizeof (*t));

  t = b_malloc (1000000);
  b_assert (t);
  b_assert ((b_size_t)t % sizeof (b_max_align_t) == 0);
  (t + 1)->l1 = 42;
  (t + 2)->l2 = 43;
  b_assert ((t + 1)->l1 == 42);
  b_assert ((t + 2)->l2 == 43);
  b_free (t);
}

void
b_test_calloc (void)
{
  int *ptr;
  int i;

  b_free (b_calloc (0, 0));
  b_free (b_calloc (0, 1));
  b_free (b_calloc (1, 0));

  ptr = b_calloc (1, sizeof (*ptr));
  b_assert (ptr);
  b_assert ((b_size_t)ptr % sizeof (*ptr) == 0);
  *ptr = 42;
  b_assert (*ptr == 42);
  b_free (ptr);

  ptr = b_calloc (10, sizeof (*ptr));
  b_assert (ptr);
  b_assert ((b_size_t)ptr % sizeof (*ptr) == 0);
  for (i = 0; i < 10; ++i)
    {
      b_assert (ptr[i] == 0);
    }
  ptr[0] = 42;
  ptr[9] = 43;
  b_assert (ptr[0] == 42);
  b_assert (ptr[9] == 43);
  b_free (ptr);

  ptr = b_calloc (1000, 1000);
  b_assert (ptr);
  b_free (ptr);
}

void
b_test_realloc (void)
{
  int *ptr1;
  int *ptr2;

  b_free (b_realloc (B_NULL, 0));
  b_free (b_realloc (B_NULL, 1));

  ptr1 = b_realloc (B_NULL, sizeof (int));
  b_assert (ptr1);
  b_assert ((b_size_t)ptr1 % sizeof (int) == 0);
  *ptr1 = 42;
  b_assert (*ptr1 == 42);
  b_free (ptr1);

  ptr1 = b_malloc (sizeof (int));
  *ptr1 = 42;
  ptr2 = ptr1;
  ptr1 = b_realloc (ptr1, sizeof (int[10]));
  b_assert (ptr1);
  b_assert (ptr1 != ptr2);
  b_assert ((b_size_t)ptr1 % sizeof (int) == 0);
  ptr1[1] = 43;
  ptr1[9] = 44;
  b_assert (ptr1[0] == 42);
  b_assert (ptr1[1] == 43);
  b_assert (ptr1[9] == 44);
  b_free (ptr1);

  ptr2 = ptr1;
  ptr1 = b_realloc (ptr1, sizeof (int[5]));
  b_assert (ptr1);
  b_assert (ptr1 == ptr2);
  b_assert ((b_size_t)ptr1 % sizeof (int) == 0);
  ptr1[2] = 41;
  ptr1[4] = 40;
  b_assert (ptr1[0] == 42);
  b_assert (ptr1[1] == 43);
  b_assert (ptr1[2] == 41);
  b_assert (ptr1[4] == 40);
  b_free (ptr1);
}

void
b_test_aligned_alloc (void)
{
  int *ptr = b_aligned_alloc (256, sizeof (int));
  b_assert (ptr);
  b_assert ((b_size_t)ptr % 256 == 0);
  *ptr = 42;
  b_assert (*ptr == 42);
  b_free (ptr);

  ptr = b_aligned_alloc (256, sizeof (int));
  b_free_aligned_sized (ptr, 256, sizeof (int));
}

void
b_test_abs (void)
{
  b_assert (b_abs (0) == 0);
  b_assert (b_abs (1) == 1);
  b_assert (b_abs (-1) == 1);
  b_assert (b_abs (100) == 100);
  b_assert (b_abs (-100) == 100);
}

void
b_test_labs (void)
{
  b_assert (b_labs (0) == 0);
  b_assert (b_labs (1) == 1);
  b_assert (b_labs (-1) == 1);
  b_assert (b_labs (100) == 100);
  b_assert (b_labs (-100) == 100);
  b_assert (b_labs (3147483647) == 3147483647);
  b_assert (b_labs (-3147483647) == 3147483647);
}

void
b_test_div (void)
{
  b_div_t div;

  div = b_div (0, 1);
  b_assert (div.quot == 0 && div.rem == 0);
  div = b_div (1, 1);
  b_assert (div.quot == 1 && div.rem == 0);
  div = b_div (2, 2);
  b_assert (div.quot == 1 && div.rem == 0);
  div = b_div (3, 2);
  b_assert (div.quot == 1 && div.rem == 1);
  div = b_div (23, 5);
  b_assert (div.quot == 4 && div.rem == 3);
  div = b_div (-23, 5);
  b_assert (div.quot == -4 && div.rem == -3);
}

void
b_test_ldiv (void)
{
  b_ldiv_t div;

  div = b_ldiv (0, 1);
  b_assert (div.quot == 0 && div.rem == 0);
  div = b_ldiv (1, 1);
  b_assert (div.quot == 1 && div.rem == 0);
  div = b_ldiv (2, 2);
  b_assert (div.quot == 1 && div.rem == 0);
  div = b_ldiv (3, 2);
  b_assert (div.quot == 1 && div.rem == 1);
  div = b_ldiv (23, 5);
  b_assert (div.quot == 4 && div.rem == 3);
  div = b_ldiv (-23, 5);
  b_assert (div.quot == -4 && div.rem == -3);
  div = b_ldiv (3147483647, 5);
  b_assert (div.quot == 629496729 && div.rem == 2);
}

void
b_test_rand ()
{
  b_assert (b_rand () == 1);
  b_assert (b_rand () == 2);
  b_assert (b_rand () == 3);
  b_srand (1);
  b_assert (b_rand () == 1);
  b_assert (b_rand () == 2);
  b_assert (b_rand () == 3);
  b_srand (2);
  b_assert (b_rand () == 2);
  b_assert (b_rand () == 3);
  b_assert (b_rand () == 4);
}
