#include "b_string.h"

#include "b_errno.h"
#include "b_limits.h"
#include "b_stdlib.h"

static char *b_internal_strcat ();
static int b_internal_strcmp ();
static b_size_t b_internal_strspn (const char *dest, const char *src,
                                   char contains);

char *
b_strcpy (char *dest, const char *src)
{
  const char *src_runner = src;
  char *dest_runner = dest;

  while (1)
    {
      *dest_runner = *src_runner++;
      if (!*dest_runner++)
        {
          break;
        }
    }
  return dest;
}

char *
b_strncpy (char *dest, const char *src, b_size_t count)
{
  const char *src_runner = src;
  char *dest_runner = dest;

  while (count)
    {
      *dest_runner = *src_runner;
      if (!*dest_runner++)
        {
          break;
        }
      ++src_runner;
      --count;
    }
  while (count--)
    {
      *dest_runner++ = 0;
    }
  return dest;
}

char *
b_strcat (char *dest, const char *src)
{
  return b_internal_strcat (dest, src, B_NULL);
}

char *
b_strncat (char *dest, const char *src, b_size_t count)
{
  return b_internal_strcat (dest, src, &count);
}

b_size_t
b_strlen (const char *str)
{
  const char *runner = str;
  b_size_t ret = 0;

  while (*runner++)
    {
      ++ret;
    }
  return ret;
}

int
b_strcmp (const char *lhs, const char *rhs)
{
  return b_internal_strcmp (lhs, rhs, B_NULL);
}

int
b_strncmp (const char *lhs, const char *rhs, b_size_t count)
{
  return b_internal_strcmp (lhs, rhs, &count);
}

char *
b_strchr (const char *str, int ch)
{
  const char *runner = str;

  while (*runner && *runner != ch)
    {
      ++runner;
    }
  return (*runner || !ch) ? (char *)runner : B_NULL;
}

char *
b_strrchr (const char *str, int ch)
{
  const char *ret = B_NULL;
  const char *runner = str;

  while (*runner)
    {
      if (*runner == ch)
        {
          ret = runner;
        }
      ++runner;
    }
  return ch ? (char *)ret : (char *)runner;
}

b_size_t
b_strspn (const char *dest, const char *src)
{
  return b_internal_strspn (dest, src, 1);
}

b_size_t
b_strcspn (const char *dest, const char *src)
{
  return b_internal_strspn (dest, src, 0);
}

char *
b_strpbrk (const char *dest, const char *breakset)
{
  const char *breakset_runner = breakset;
  char check[B_CHAR_MAX + 1] = { 0 };
  const char *dest_runner = dest;

  while (*breakset_runner)
    {
      check[(short)*breakset_runner++] = 1;
    }

  while (*dest_runner)
    {
      if (check[(short)*dest_runner])
        {
          return (char *)dest_runner;
        }
      ++dest_runner;
    }
  return B_NULL;
}

char *
b_strstr (const char *str, const char *substr)
{
  const char *substr_runner = substr;
  const char *str_runner = str;
  char *ret = (char *)str;

  if (str == substr || !*substr)
    {
      return (char *)str;
    }

  while (*str_runner)
    {
      if (*str_runner == *substr_runner)
        {
          if (!*(++substr_runner))
            {
              return ret;
            }
          ++str_runner;
        }
      else
        {
          ret = (char *)++str_runner;
          substr_runner = substr;
        }
    }
  return B_NULL;
}

char *
b_strtok (char *str, const char *delim)
{
  char check[B_CHAR_MAX + 1] = { 0 };
  const char *delim_runner = delim;
  static char *token = B_NULL;
  char *str_runner;
  char *ret;

  if (str)
    {
      token = str;
    }

  if (!token)
    {
      return B_NULL;
    }

  ret = token;
  str_runner = token;

  while (*delim_runner)
    {
      check[(short)*delim_runner++] = 1;
    }

  while (*str_runner)
    {
      if (check[(short)*str_runner])
        {
          *str_runner++ = B_NULL;
          token = str_runner;
          return ret;
        }
      ++str_runner;
    }
  token = B_NULL;
  return ret;
}

char *
b_strdup (const char *src)
{
  const b_size_t src_len_with_null = b_strlen (src) + 1;
  char *ret = b_malloc (src_len_with_null);
  b_memcpy (ret, src, src_len_with_null);
  return ret;
}

char *
b_strndup (const char *src, b_size_t size)
{
  const b_size_t src_len_with_null = b_strlen (src) + 1;
  const b_size_t size_with_null = size + 1;
  char *ret;

  if (src_len_with_null <= size_with_null)
    {
      ret = b_malloc (src_len_with_null);
      b_memcpy (ret, src, src_len_with_null);
    }
  else
    {
      ret = b_malloc (size_with_null);
      b_memcpy (ret, src, size);
      ret[size] = 0;
    }
  return ret;
}

void *
b_memchr (const void *ptr, int ch, b_size_t count)
{
  const char *ptr_runner = (const char *)ptr;

  while (count--)
    {
      if (*ptr_runner == ch)
        {
          return (void *)ptr_runner;
        }
      else
        {
          ++ptr_runner;
        }
    }
  return B_NULL;
}

int
b_memcmp (const void *lhs, const void *rhs, b_size_t count)
{
  const char *lhs_runner = (const char *)lhs;
  const char *rhs_runner = (const char *)rhs;

  while (count--)
    {
      if (*lhs_runner < *rhs_runner)
        {
          return -1;
        }
      if (*lhs_runner > *rhs_runner)
        {
          return 1;
        }
      ++lhs_runner;
      ++rhs_runner;
    }
  return 0;
}

void *
b_memset (void *dest, int ch, b_size_t count)
{
  char *dest_runner = (char *)dest;

  while (count--)
    {
      *dest_runner++ = ch;
    }
  return dest;
}

void *
b_memcpy (void *dest, const void *src, b_size_t count)
{
  const char *src_runner = (const char *)src;
  char *dest_runner = (char *)dest;

  while (count--)
    {
      *dest_runner++ = *src_runner++;
    }
  return dest;
}

void *
b_memmove (void *dest, const void *src, b_size_t count)
{
  char buf[1024];

  b_memcpy (buf, src, count);
  b_memcpy (dest, buf, count);
  return dest;
}

void *
b_memccpy (void *dest, const void *src, int c, b_size_t count)
{
  const char *src_runner = src;
  char *dest_runner = dest;

  while (count--)
    {
      *dest_runner = *src_runner;
      if (*dest_runner == c)
        {
          return ++dest_runner;
        }
      ++dest_runner;
      ++src_runner;
    }
  return B_NULL;
}

char *
b_strerror (int errnum)
{
  switch (errnum)
    {
    case B_EDOM:
      return "B_EDOM";
    case B_ERANGE:
      return "B_ERANGE";
    default:
      return "B_EUNKNOWN";
    }
}

static char *
b_internal_strcat (char *dest, const char *src, b_size_t *const count)
{
  const char *src_runner = src;
  char *dest_runner = dest;

  if (count && !*count)
    {
      return dest;
    }

  while (*dest_runner)
    {
      ++dest_runner;
    }

  while (!count || (*count)--)
    {
      *dest_runner = *src_runner++;
      if (!*dest_runner++)
        {
          return dest;
        }
    }

  return dest;
}

static int
b_internal_strcmp (const char *lhs, const char *rhs, b_size_t *const count)
{
  const char *lhs_runner = lhs;
  const char *rhs_runner = rhs;

  while (!count || (*count)--)
    {
      if (!*lhs_runner)
        {
          return *rhs_runner ? -1 : 0;
        }
      if (!*rhs_runner || *lhs_runner > *rhs_runner)
        {
          return 1;
        }
      if (*lhs_runner < *rhs_runner)
        {
          return -1;
        }
      ++lhs_runner;
      ++rhs_runner;
    }
  return 0;
}

static b_size_t
b_internal_strspn (const char *dest, const char *src, char contains)
{
  const char *dest_runner = dest;
  const char *src_runner = src;
  char check[B_CHAR_MAX + 1];
  b_size_t curr = 0;
  b_size_t ret = 0;

  b_memset (check, !contains, sizeof (check));
  while (*src_runner)
    {
      check[(short)*src_runner++] = contains;
    }

  while (*dest_runner)
    {
      if (check[(short)*dest_runner++])
        {
          ++curr;
        }
      else
        {
          if (curr > ret)
            {
              ret = curr;
            }
          curr = 0;
        }
    }

  return curr > ret ? curr : ret;
}
