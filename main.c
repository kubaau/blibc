#include "b_assert.h"
#include "b_ctype_tests.h"
#include "b_errno.h"
#include "b_inttypes.h"
#include "b_iso646.h"
#include "b_stdbool.h"
#include "b_stddef.h"
#include "b_stdint.h"
#include "b_stdlib.h"
#include "b_stdlib_tests.h"
#include "b_string_tests.h"
#include "b_threads_tests.h"
#include "b_wchar.h"
#include "b_wctype.h"

int
main ()
{
  typedef struct
  {
    int i;
    char c;
    float f;
  } test;

  b_test_isalnum ();
  b_test_isalpha ();
  b_test_islower ();
  b_test_isupper ();
  b_test_isdigit ();
  b_test_isxdigit ();
  b_test_iscntrl ();
  b_test_isgraph ();
  b_test_isspace ();
  b_test_isblank ();
  b_test_isprint ();
  b_test_ispunct ();
  b_test_tolower ();
  b_test_toupper ();

  b_assert (!b_errno);
  b_errno = B_ENOMEM;
  b_assert (b_errno == 12);
  b_errno = B_EDOM;
  b_assert (b_errno == 33);
  b_errno = B_ERANGE;
  b_assert (b_errno == 34);

  b_assert (!B_NULL);
  b_assert (b_offsetof (test, i) == 0);
  b_assert (b_offsetof (test, c) == sizeof (int));
  b_assert (b_offsetof (test, f) == sizeof (int) + sizeof (int));

  b_test_qsort_b_bsearch ();

  b_test_atoi ();
  b_test_atol ();

  b_test_strcpy ();
  b_test_strncpy ();
  b_test_strcat ();
  b_test_strncat ();
  b_test_strlen ();
  b_test_strcmp ();
  b_test_strncmp ();
  b_test_strchr ();
  b_test_strrchr ();
  b_test_strspn ();
  b_test_strcspn ();
  b_test_strpbrk ();
  b_test_strstr ();
  b_test_strtok ();
  b_test_strdup ();
  b_test_strndup ();
  b_test_memchr ();
  b_test_memcmp ();
  b_test_memset ();
  b_test_memcpy ();
  b_test_memmove ();
  b_test_memccpy ();
  b_test_strerror ();

  b_test_malloc ();
  b_test_calloc ();
  b_test_realloc ();
  b_test_aligned_alloc ();

  b_test_abs ();
  b_test_labs ();

  b_test_div ();
  b_test_ldiv ();

  b_test_rand ();

  b_test_threads ();

  return B_EXIT_SUCCESS;
}
