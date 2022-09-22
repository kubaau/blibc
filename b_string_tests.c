#include "b_string.h"

#include "b_assert.h"
#include "b_errno.h"
#include "b_stdlib.h"

#define B_INTERNAL_STREQ(lhs, rhs) (b_strcmp (lhs, rhs) == 0)

void
b_test_strcpy (void)
{
  char buf[10];

  b_assert (b_strcpy (buf, "abc") == buf);
  b_assert (B_INTERNAL_STREQ (buf, "abc"));
  b_assert (b_strcpy (buf, "   abc") == buf);
  b_assert (B_INTERNAL_STREQ (buf, "   abc"));
  b_assert (b_strcpy (buf, "a123bc") == buf);
  b_assert (B_INTERNAL_STREQ (buf, "a123bc"));
  b_assert (b_strcpy (buf, "") == buf);
  b_assert (B_INTERNAL_STREQ (buf, ""));
  b_assert (b_strcpy (buf, "123456789") == buf);
  b_assert (B_INTERNAL_STREQ (buf, "123456789"));
}

void
b_test_strncpy (void)
{
  char buf[10];
  int i;

#define B_INTERNAL_STRNEQ(lhs, rhs, size) (b_strncmp (lhs, rhs, size) == 0)
  b_assert (b_strncpy (buf, "abc", 4) == buf);
  b_assert (B_INTERNAL_STRNEQ (buf, "abc", 4));
  b_assert (b_strncpy (buf, "   abc", 4) == buf);
  b_assert (B_INTERNAL_STRNEQ (buf, "   abc", 4));
  b_assert (b_strncpy (buf, "a123bc", 4) == buf);
  b_assert (B_INTERNAL_STRNEQ (buf, "a123bc", 4));
  b_assert (b_strncpy (buf, "", 4) == buf);
  for (i = 0; i < 4; ++i)
    b_assert (buf[i] == 0);
  b_assert (B_INTERNAL_STRNEQ (buf, "", 4));
  b_assert (b_strncpy (buf, "123456789", 4) == buf);
  b_assert (B_INTERNAL_STRNEQ (buf, "123456789", 4));
}

void
b_test_strcat (void)
{
  char buf[10] = "abc";

  b_strcat (buf, "def");
  b_assert (B_INTERNAL_STREQ (buf, "abcdef"));
  b_strcat (buf, "g");
  b_assert (B_INTERNAL_STREQ (buf, "abcdefg"));
  b_strcat (buf, "");
  b_assert (B_INTERNAL_STREQ (buf, "abcdefg"));
}

void
b_test_strncat (void)
{
  char buf[10] = "abc";

  b_strncat (buf, "def", 2);
  b_assert (B_INTERNAL_STREQ (buf, "abcde"));
  b_strncat (buf, "g", 3);
  b_assert (B_INTERNAL_STREQ (buf, "abcdeg"));
  b_strncat (buf, "", 0);
  b_assert (B_INTERNAL_STREQ (buf, "abcdeg"));
}

void
b_test_strlen (void)
{
  b_assert (b_strlen ("") == 0);
  b_assert (b_strlen ("a") == 1);
  b_assert (b_strlen ("abc") == 3);
  b_assert (b_strlen ("  abc") == 5);
  b_assert (b_strlen ("\t\n\rabc") == 6);
  b_assert (b_strlen ("abc\0def") == 3);
}

void
b_test_strcmp (void)
{
  b_assert (b_strcmp ("abc", "abc") == 0);
  b_assert (b_strcmp ("", "") == 0);
  b_assert (b_strcmp ("   abc", "   abc") == 0);
  b_assert (b_strcmp ("\t\n\t", "\t\n\t") == 0);
  b_assert (b_strcmp ("abc", "aaa") == 1);
  b_assert (b_strcmp ("abc", "bbc") == -1);
  b_assert (b_strcmp ("a", "aaa") == -1);
  b_assert (b_strcmp ("aaa", "a") == 1);
}

void
b_test_strncmp (void)
{
  b_assert (b_strncmp ("abc", "abc", 3) == 0);
  b_assert (b_strncmp ("", "", 3) == 0);
  b_assert (b_strncmp ("   abc", "   abc", 3) == 0);
  b_assert (b_strncmp ("\t\n\t", "\t\n\t", 3) == 0);
  b_assert (b_strncmp ("abc", "aaa", 3) == 1);
  b_assert (b_strncmp ("abc", "bbc", 3) == -1);
  b_assert (b_strncmp ("a", "aaa", 3) == -1);
  b_assert (b_strncmp ("aaa", "a", 3) == 1);
  b_assert (b_strncmp ("aaaa", "aaab", 3) == 0);
}

void
b_test_strchr (void)
{
  const char *str = "abcdefabcdef\0abcdefg";

  b_assert (b_strchr (str, 'a') - str == 0);
  b_assert (b_strchr (str, 'c') - str == 2);
  b_assert (b_strchr (str, 'f') - str == 5);
  b_assert (b_strchr (str, B_NULL) - str == 12);
  b_assert (b_strchr (str, 'g') == B_NULL);
}

void
b_test_strrchr (void)
{
  const char *str = "abcdefabcdef\0abcdefg";

  b_assert (b_strrchr (str, 'a') - str == 6);
  b_assert (b_strrchr (str, 'c') - str == 8);
  b_assert (b_strrchr (str, 'f') - str == 11);
  b_assert (b_strrchr (str, B_NULL) - str == 12);
  b_assert (b_strrchr (str, 'g') == B_NULL);
}

void
b_test_strspn (void)
{
  const char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";
  const char *str1 = "abcde312$#@";
  const char *str2 = "abcde312$#@qwertyuiop";
  const char *str3 = "312$#@";
  const char *str4 = "31f2$#@";
  const char *str5 = "";

  b_assert (b_strspn (str1, low_alpha) == 5);
  b_assert (b_strspn (str2, low_alpha) == 10);
  b_assert (b_strspn (str3, low_alpha) == 0);
  b_assert (b_strspn (str4, low_alpha) == 1);
  b_assert (b_strspn (str5, low_alpha) == 0);
}

void
b_test_strcspn (void)
{
  const char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";
  const char *str1 = "abcde312$#@";
  const char *str2 = "abcde312$#@qwertyuiop";
  const char *str3 = "312$#@";
  const char *str4 = "31f2$#@";
  const char *str5 = "";

  b_assert (b_strcspn (str1, low_alpha) == 6);
  b_assert (b_strcspn (str2, low_alpha) == 6);
  b_assert (b_strcspn (str3, low_alpha) == 6);
  b_assert (b_strcspn (str4, low_alpha) == 4);
  b_assert (b_strcspn (str5, low_alpha) == 0);
}

void
b_test_strpbrk (void)
{
  const char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";
  const char *str1 = "abcde312$#@";
  const char *str2 = "abcde312$#@qwertyuiop";
  const char *str3 = "312$#@";
  const char *str4 = "31f2$#@";
  const char *str5 = "";

  b_assert (b_strpbrk (str1, low_alpha) - str1 == 0);
  b_assert (b_strpbrk (str2, low_alpha) - str2 == 0);
  b_assert (b_strpbrk (str3, low_alpha) == B_NULL);
  b_assert (b_strpbrk (str4, low_alpha) - str4 == 2);
  b_assert (b_strpbrk (str5, low_alpha) == B_NULL);
}

void
b_test_strstr (void)
{
  const char *str1 = "abcde312$#@";
  const char *str2 = "";

  b_assert (b_strstr (str1, str1) == str1);
  b_assert (b_strstr (str1, "") == str1);
  b_assert (b_strstr (str2, "") == str2);
  b_assert (b_strstr (str1, "abcde") - str1 == 0);
  b_assert (b_strstr (str1, "c") - str1 == 2);
  b_assert (b_strstr (str1, "cde312") - str1 == 2);
  b_assert (b_strstr (str1, "abcdef") == B_NULL);
}

void
b_test_strtok (void)
{
  const char *end_str1 = "A\0bird\0came\0down\0the\0walk";
  const char *end_str2 = "A\0bird/came\0down\0the\0walk";
  char str1[] = "A bird came down the walk";
  char str2[] = "A bird/came-down the$walk";
  char *token;
  b_size_t i;

  token = b_strtok (str1, " ");
  b_assert (B_INTERNAL_STREQ (token, "A"));
  token = b_strtok (B_NULL, " ");
  b_assert (B_INTERNAL_STREQ (token, "bird"));
  token = b_strtok (B_NULL, " ");
  b_assert (B_INTERNAL_STREQ (token, "came"));
  token = b_strtok (B_NULL, " ");
  b_assert (B_INTERNAL_STREQ (token, "down"));
  token = b_strtok (B_NULL, " ");
  b_assert (B_INTERNAL_STREQ (token, "the"));
  token = b_strtok (B_NULL, " ");
  b_assert (B_INTERNAL_STREQ (token, "walk"));
  b_assert (b_strtok (B_NULL, " ") == B_NULL);
  for (i = 0; i < sizeof (str1); ++i)
    b_assert (str1[i] == end_str1[i]);

  token = b_strtok (str2, " $-/");
  b_assert (B_INTERNAL_STREQ (token, "A"));
  token = b_strtok (B_NULL, "-");
  b_assert (B_INTERNAL_STREQ (token, "bird/came"));
  token = b_strtok (B_NULL, " ");
  b_assert (B_INTERNAL_STREQ (token, "down"));
  token = b_strtok (B_NULL, " $-/");
  b_assert (B_INTERNAL_STREQ (token, "the"));
  token = b_strtok (B_NULL, " $-/");
  b_assert (B_INTERNAL_STREQ (token, "walk"));
  b_assert (b_strtok (B_NULL, " ") == B_NULL);
  for (i = 0; i < sizeof (str2); ++i)
    b_assert (str2[i] == end_str2[i]);
}

void
b_test_strdup (void)
{
  char *str;
  str = b_strdup ("abc");
  b_assert (B_INTERNAL_STREQ (str, "abc"));
  b_free (str);
  str = b_strdup ("");
  b_assert (B_INTERNAL_STREQ (str, ""));
  b_free (str);
}

void
b_test_strndup (void)
{
  char *str;
  str = b_strndup ("abc", 2);
  b_assert (B_INTERNAL_STREQ (str, "ab"));
  b_free (str);
  str = b_strndup ("abc", 5);
  b_assert (B_INTERNAL_STREQ (str, "abc"));
  b_free (str);
  str = b_strndup ("", 0);
  b_assert (B_INTERNAL_STREQ (str, ""));
  b_free (str);
  str = b_strndup ("", 5);
  b_assert (B_INTERNAL_STREQ (str, ""));
  b_free (str);
}

void
b_test_memchr (void)
{
  const char str[] = "abcdef";
  const int i = 0x1234;

  b_assert ((const char *)b_memchr (str, 'a', sizeof (str)) - str == 0);
  b_assert ((const char *)b_memchr (str, 'c', sizeof (str)) - str == 2);
  b_assert ((const char *)b_memchr (str, 'f', sizeof (str)) - str == 5);
  b_assert ((const char *)b_memchr (str, 'f', sizeof (str) - 1) - str == 5);
  b_assert ((const char *)b_memchr (str, 'f', sizeof (str) - 2) == B_NULL);
  b_assert ((const char *)b_memchr (str, 'g', sizeof (str)) == B_NULL);

  b_assert ((const char *)b_memchr (&i, 0x12, sizeof (i)) - (const char *)&i
            == 1);
  b_assert ((const char *)b_memchr (&i, 0x34, sizeof (i)) - (const char *)&i
            == 0);
}

void
b_test_memcmp (void)
{
  const char str1[] = "abcdef";
  const char str2[] = "abcdefg";
  const char str3[] = "abcdeg";
  const char str4[] = "abcdee";
  const char str5[] = "abcde";
  const char str6[] = "";
  const int i1 = 42;
  const int i2 = 41;
  const int i3 = 43;

  b_assert (b_memcmp (str1, str1, sizeof (str1)) == 0);
  b_assert (b_memcmp (str1, str1, sizeof (str1) - 1) == 0);
  b_assert (b_memcmp (str1, str2, sizeof (str1) - 1) == 0);
  b_assert (b_memcmp (str1, str3, sizeof (str1)) == -1);
  b_assert (b_memcmp (str1, str4, sizeof (str1)) == 1);
  b_assert (b_memcmp (str1, str5, sizeof (str1)) == 1);
  b_assert (b_memcmp (str1, str6, 1) == 1);
  b_assert (b_memcmp (str1, str6, 0) == 0);
  b_assert (b_memcmp (&i1, &i1, sizeof (int)) == 0);
  b_assert (b_memcmp (&i1, &i2, sizeof (int)) == 1);
  b_assert (b_memcmp (&i1, &i3, sizeof (int)) == -1);
}

void
b_test_memset (void)
{
  char buf[10];
  int i;

  b_assert (b_memset (buf, 0, sizeof (buf)) == buf);
  b_assert (b_memset (buf, 'a', 3) == buf);
  b_assert (B_INTERNAL_STREQ (buf, "aaa"));
  b_assert (b_memset (buf, 'a', 5) == buf);
  b_assert (B_INTERNAL_STREQ (buf, "aaaaa"));
  b_assert (b_memset (buf, 'b', 2) == buf);
  b_assert (B_INTERNAL_STREQ (buf, "bbaaa"));
  b_assert (b_memset (buf + 4, 'c', 3) == buf + 4);
  b_assert (B_INTERNAL_STREQ (buf, "bbaaccc"));
  b_assert (b_memset (buf, 'd', sizeof (buf) - 1) == buf);
  b_assert (B_INTERNAL_STREQ (buf, "ddddddddd"));

  b_assert (b_memset (&i, 0, sizeof (int)) == &i);
  b_assert (i == 0);
  b_assert (b_memset (&i, 0x42, sizeof (int)) == &i);
  b_assert (i == 0x42424242);
}

void
b_test_memcpy (void)
{
  const char *str = "abcdef";
  char buf[10] = { 0 };

  b_assert (b_memcpy (buf, str, b_strlen (str)) == buf);
  b_assert (B_INTERNAL_STREQ (buf, str));
  b_assert (b_memcpy (buf + 1, str, 3) == buf + 1);
  b_assert (B_INTERNAL_STREQ (buf, "aabcef"));
  b_assert (b_memcpy (buf + 3, str + 2, 2) == buf + 3);
  b_assert (B_INTERNAL_STREQ (buf, "aabcdf"));
}

void
b_test_memmove (void)
{
  const char *str = "abcdef";
  char buf[10] = { 0 };

  b_assert (b_memmove (buf, str, b_strlen (str)) == buf);
  b_assert (B_INTERNAL_STREQ (buf, str));
  b_assert (b_memmove (buf + 1, str, 3) == buf + 1);
  b_assert (B_INTERNAL_STREQ (buf, "aabcef"));
  b_assert (b_memmove (buf + 3, str + 2, 2) == buf + 3);
  b_assert (B_INTERNAL_STREQ (buf, "aabcdf"));

  b_assert (b_memmove (buf, buf + 1, b_strlen (buf)) == buf);
  b_assert (B_INTERNAL_STREQ (buf, "abcdf"));
}

void
b_test_memccpy (void)
{
  char buf[1000];
  const char *const buf_end = buf + sizeof buf;
  char *ptr;

  b_assert (b_memccpy (buf, "abc", 0, 4) == buf + 4);
  b_assert (B_INTERNAL_STRNEQ (buf, "abc", 4));
  b_assert (b_memccpy (buf, "   abc", 0, 4) == B_NULL);
  b_assert (B_INTERNAL_STRNEQ (buf, "   abc", 4));
  b_assert (b_memccpy (buf, "a123bc", 0, 4) == B_NULL);
  b_assert (B_INTERNAL_STRNEQ (buf, "a123bc", 4));
  b_assert (b_memccpy (buf, "", 0, 4) == buf + 1);
  b_assert (B_INTERNAL_STRNEQ (buf, "", 4));
  b_assert (b_memccpy (buf, "123456789", 0, 4) == B_NULL);
  b_assert (B_INTERNAL_STRNEQ (buf, "123456789", 4));
  b_assert (b_memccpy (buf, "123456789", '6', 10) == buf + 6);
  b_assert (B_INTERNAL_STRNEQ (buf, "123456789", 6));
#undef B_INTERNAL_STRNEQ
  ptr = b_memccpy (buf, "John, ", 0, sizeof buf);
  ptr = b_memccpy (ptr - 1, "Paul, ", 0, buf_end - ptr);
  ptr = b_memccpy (ptr - 1, "George, ", 0, buf_end - ptr);
  ptr = b_memccpy (ptr - 1, "Joel ", 0, buf_end - ptr);
  b_assert (B_INTERNAL_STREQ (buf, "John, Paul, George, Joel "));
}

void
b_test_strerror (void)
{
  b_assert (B_INTERNAL_STREQ (b_strerror (B_EDOM), "B_EDOM"));
  b_assert (B_INTERNAL_STREQ (b_strerror (B_ERANGE), "B_ERANGE"));
  b_assert (B_INTERNAL_STREQ (b_strerror (0), "B_EUNKNOWN"));
}
