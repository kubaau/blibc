#include "b_stdlib.h"

#include "b_ctype.h"
#include "b_string.h"

typedef int (*b_internal_comp) (const void *, const void *);
static void b_internal_quicksort ();
static void *b_internal_alloc ();

void
b_qsort (void *ptr, b_size_t count, b_size_t size, b_internal_comp comp)
{
  b_internal_quicksort (ptr, size, 0, count - 1, comp);
}

void *
b_bsearch (const void *key, const void *ptr, b_size_t count, b_size_t size,
           b_internal_comp comp)
{
  const b_size_t half = count / 2;
  const char *mid = (const char *)ptr + half * size;
  const int cmp = comp (key, mid);

  if (!cmp)
    {
      return (void *)mid;
    }

  if (cmp < 0)
    {
      return b_bsearch (key, ptr, half - 1, size, comp);
    }

  return b_bsearch (key, mid + size, half - 1, size, comp);
}

int
b_atoi (const char *str)
{
  return b_atol (str);
}

long
b_atol (const char *str)
{
  int sign_set = 0;
  long ret = 0;

  while (b_isspace (*str))
    {
      ++str;
    }

  while (*str)
    {
      if (*str == '+')
        {
          if (sign_set == -1)
            {
              return 0;
            }
          sign_set = 1;
        }
      else if (*str == '-')
        {
          if (sign_set == 1)
            {
              return 0;
            }
          sign_set = -1;
        }
      else if (b_isdigit (*str))
        {
          ret = ret * 10 + (*str - '0');
        }
      else
        {
          break;
        }
      ++str;
    }

  return sign_set == -1 ? -ret : ret;
}

#define B_INTERNAL_ALIGNOF(size)                                              \
  (size >= 16 ? 16 : size >= 8 ? 8 : size >= 4 ? 4 : size >= 2 ? 2 : 1)
void *
b_malloc (b_size_t size)
{
  return b_internal_alloc (size, B_INTERNAL_ALIGNOF (size));
}

void *
b_calloc (b_size_t num, b_size_t size)
{
  const b_size_t total = num * size;

  void *ret = b_internal_alloc (total, B_INTERNAL_ALIGNOF (size));
  return ret ? b_memset (ret, 0, total) : ret;
}
#undef B_INTERNAL_ALIGNOF

void *
b_realloc (void *ptr, b_size_t new_size)
{
  if (!ptr)
    {
      return b_malloc (new_size);
    }

  b_free (ptr);
  return b_malloc (new_size);
}

void
b_free (void *ptr)
{
  if (!ptr)
    {
      return;
    }
}

static void
b_internal_swap (void *a, void *b, b_size_t size)
{
  char temp[1024];

  b_memcpy (temp, a, size);
  b_memcpy (a, b, size);
  b_memcpy (b, temp, size);
}

static int
b_internal_partition (void *ptr, b_size_t size, int first, int last,
                      b_internal_comp comp)
{
  char *pivot;
  int i;
  int j;

  if (last - first < 1)
    return first;

#define B_INTERNAL_ELEMENT_AT(ptr, size, index)                               \
  ((char *)(ptr) + (size) * (index))
  pivot = B_INTERNAL_ELEMENT_AT (ptr, size, last);
  i = first;

  for (j = first; j != last; ++j)
    if (comp (B_INTERNAL_ELEMENT_AT (ptr, size, j), pivot) <= 0)
      b_internal_swap (B_INTERNAL_ELEMENT_AT (ptr, i++, size),
                       B_INTERNAL_ELEMENT_AT (ptr, j, size), size);
  b_internal_swap (B_INTERNAL_ELEMENT_AT (ptr, i, size), pivot, size);
#undef B_INTERNAL_ELEMENT_AT
  return i;
}

static void
b_internal_quicksort (void *ptr, b_size_t size, int first, int last,
                      b_internal_comp comp)
{
  if (first < last)
    {
      const int q = b_internal_partition (ptr, size, first, last, comp);
      b_internal_quicksort (ptr, size, first, q - 1, comp);
      b_internal_quicksort (ptr, size, q + 1, last, comp);
    }
}

static void *
b_internal_alloc (b_size_t size, b_size_t al)
{
  static char buf[1024];
  static const char *const buf_end = (const char *)buf + sizeof (buf);
  static const char *rover = (const char *)buf;
  const char *ret = rover;

  if (!size)
    {
      size = 1;
    }

  if (al > 1)
    {
      while ((b_size_t)ret % al != 0)
        {
          ++ret;
        }
    }

  if (ret + size >= buf_end)
    {
      return B_NULL;
    }

  rover = ret + size;
  return (void *)ret;
}
