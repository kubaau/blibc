#include "b_ctype.h"

#include "b_assert.h"

void
b_test_isalnum (void)
{
  b_assert (!b_isalnum ('0' - 1));
  b_assert (b_isalnum ('0'));
  b_assert (b_isalnum ('9'));
  b_assert (!b_isalnum ('9' + 1));
  b_assert (!b_isalnum ('A' - 1));
  b_assert (b_isalnum ('A'));
  b_assert (b_isalnum ('Z'));
  b_assert (!b_isalnum ('Z' + 1));
  b_assert (!b_isalnum ('a' - 1));
  b_assert (b_isalnum ('a'));
  b_assert (b_isalnum ('z'));
  b_assert (!b_isalnum ('z' + 1));
}

void
b_test_isalpha (void)
{
  b_assert (!b_isalpha ('A' - 1));
  b_assert (b_isalpha ('A'));
  b_assert (b_isalpha ('Z'));
  b_assert (!b_isalpha ('Z' + 1));
  b_assert (!b_isalpha ('a' - 1));
  b_assert (b_isalpha ('a'));
  b_assert (b_isalpha ('z'));
  b_assert (!b_isalpha ('z' + 1));
}

void
b_test_islower (void)
{
  b_assert (!b_islower ('A' - 1));
  b_assert (!b_islower ('A'));
  b_assert (!b_islower ('Z'));
  b_assert (!b_islower ('Z' + 1));
  b_assert (!b_islower ('a' - 1));
  b_assert (b_islower ('a'));
  b_assert (b_islower ('z'));
  b_assert (!b_islower ('z' + 1));
}

void
b_test_isupper (void)
{
  b_assert (!b_isupper ('A' - 1));
  b_assert (b_isupper ('A'));
  b_assert (b_isupper ('Z'));
  b_assert (!b_isupper ('Z' + 1));
  b_assert (!b_isupper ('a' - 1));
  b_assert (!b_isupper ('a'));
  b_assert (!b_isupper ('z'));
  b_assert (!b_isupper ('z' + 1));
}

void
b_test_isdigit (void)
{
  b_assert (!b_isdigit ('0' - 1));
  b_assert (b_isdigit ('0'));
  b_assert (b_isdigit ('9'));
  b_assert (!b_isdigit ('9' + 1));
}

void
b_test_isxdigit (void)
{
  b_assert (!b_isxdigit ('0' - 1));
  b_assert (b_isxdigit ('0'));
  b_assert (b_isxdigit ('9'));
  b_assert (!b_isxdigit ('9' + 1));
  b_assert (!b_isxdigit ('A' - 1));
  b_assert (b_isxdigit ('A'));
  b_assert (b_isxdigit ('F'));
  b_assert (!b_isxdigit ('F' + 1));
  b_assert (!b_isxdigit ('a' - 1));
  b_assert (b_isxdigit ('a'));
  b_assert (b_isxdigit ('f'));
  b_assert (!b_isxdigit ('f' + 1));
}

void
b_test_iscntrl (void)
{
  b_assert (b_iscntrl (0));
  b_assert (b_iscntrl (31));
  b_assert (!b_iscntrl (32));
  b_assert (!b_iscntrl (126));
  b_assert (b_iscntrl (127));
}

void
b_test_isgraph (void)
{
  b_assert (!b_isgraph ('!' - 1));
  b_assert (b_isgraph ('!'));
  b_assert (b_isgraph ('~'));
  b_assert (!b_isgraph ('~' + 1));
}

void
b_test_isspace (void)
{
  b_assert (!b_isspace ('\t' - 1));
  b_assert (b_isspace ('\t'));
  b_assert (b_isspace ('\r'));
  b_assert (!b_isspace ('\r' + 1));
  b_assert (b_isspace (' '));
}

void
b_test_isblank (void)
{
  b_assert (!b_isblank ('\t' - 1));
  b_assert (b_isblank ('\t'));
  b_assert (!b_isblank ('\t' + 1));
  b_assert (!b_isblank (' ' - 1));
  b_assert (b_isblank (' '));
  b_assert (!b_isblank (' ') + 1);
}

void
b_test_isprint (void)
{
  b_assert (!b_isprint (' ' - 1));
  b_assert (b_isprint (' '));
  b_assert (b_isprint ('~'));
  b_assert (!b_isprint ('~' + 1));
}

void
b_test_ispunct (void)
{
  b_assert (!b_ispunct ('!' - 1));
  b_assert (b_ispunct ('!'));
  b_assert (b_ispunct ('/'));
  b_assert (!b_ispunct ('/' + 1));
  b_assert (!b_ispunct (':' - 1));
  b_assert (b_ispunct (':'));
  b_assert (b_ispunct ('@'));
  b_assert (!b_ispunct ('@' + 1));
  b_assert (!b_ispunct ('[' - 1));
  b_assert (b_ispunct ('['));
  b_assert (b_ispunct ('`'));
  b_assert (!b_ispunct ('`' + 1));
  b_assert (!b_ispunct ('{' - 1));
  b_assert (b_ispunct ('{'));
  b_assert (b_ispunct ('~'));
  b_assert (!b_ispunct ('~' + 1));
}

void
b_test_tolower (void)
{
  b_assert (b_tolower ('a') == 'a');
  b_assert (b_tolower ('A') == 'a');
  b_assert (b_tolower ('z') == 'z');
  b_assert (b_tolower ('Z') == 'z');
}

void
b_test_toupper (void)
{
  b_assert (b_toupper ('a') == 'A');
  b_assert (b_toupper ('A') == 'A');
  b_assert (b_toupper ('z') == 'Z');
  b_assert (b_toupper ('Z') == 'Z');
}
