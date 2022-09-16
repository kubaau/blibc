#include "b_assert.h"
#include "b_ctype_tests.h"
#include "b_errno.h"
#include "b_stddef.h"
#include "b_stdlib.h"
#include "b_stdlib_tests.h"
#include "b_string_tests.h"
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
    short s;
  } b_test_struct;

  test_isalnum ();
  test_isalpha ();
  test_islower ();
  test_isupper ();
  test_isdigit ();
  test_isxdigit ();
  test_iscntrl ();
  test_isgraph ();
  test_isspace ();
  test_isprint ();
  test_ispunct ();
  test_tolower ();
  test_toupper ();

  b_assert (!b_errno);
  b_errno = B_EDOM;
  b_assert (b_errno == 33);
  b_errno = B_ERANGE;
  b_assert (b_errno == 34);

  b_assert (!B_NULL);
  b_assert (b_offsetof (b_test_struct, i) == 0);
  b_assert (b_offsetof (b_test_struct, c) == sizeof (int));
  b_assert (b_offsetof (b_test_struct, f) == sizeof (int) + sizeof (int));
  b_assert (b_offsetof (b_test_struct, s)
            == sizeof (int) + sizeof (int) + sizeof (float));

  test_qsort_b_bsearch ();

  test_atoi ();
  test_atol ();

  test_strcpy ();
  test_strncpy ();
  test_strcat ();
  test_strncat ();
  test_strlen ();
  test_strcmp ();
  test_strncmp ();
  test_strchr ();
  test_strrchr ();
  test_strspn ();
  test_strcspn ();
  test_strpbrk ();
  test_strstr ();
  test_strtok ();
  test_memchr ();
  test_memcmp ();
  test_memset ();
  test_memcpy ();
  test_memmove ();
  test_strerror ();

  test_malloc ();
  test_calloc ();
  test_realloc ();

  return B_EXIT_SUCCESS;
}
