#include "b_stdlib.h"

#include "b_ctype.h"
#include "b_string.h"

typedef int (*b_comp) (const void *, const void *);

#define B_ELEMENT_AT(ptr, size, index) ((char *)(ptr) + (size) * (index))

static void
b_swap (void *a, void *b, b_size_t size)
{
  char temp[1024];

  b_memcpy (temp, a, size);
  b_memcpy (a, b, size);
  b_memcpy (b, temp, size);
}

static int
b_partition (void *ptr, b_size_t size, int first, int last, b_comp comp)
{
  char *pivot;
  int i;
  int j;

  if (last - first < 1)
    return first;

  pivot = B_ELEMENT_AT (ptr, size, last);
  i = first;

  for (j = first; j != last; ++j)
    if (comp (B_ELEMENT_AT (ptr, size, j), pivot) <= 0)
      b_swap (B_ELEMENT_AT (ptr, i++, size), B_ELEMENT_AT (ptr, j, size),
              size);
  b_swap (B_ELEMENT_AT (ptr, i, size), pivot, size);
  return i;
}

static void
b_quicksort (void *ptr, b_size_t size, int first, int last, b_comp comp)
{
  if (first < last)
    {
      const int q = b_partition (ptr, size, first, last, comp);
      b_quicksort (ptr, size, first, q - 1, comp);
      b_quicksort (ptr, size, q + 1, last, comp);
    }
}
/*
template <typename It>
void quickSort(It begin, It end)
{
    using namespace std;

    if (distance(begin, end) > 1)
    {
        const auto q = partition(begin, end);
        quickSort(begin, q);
        quickSort(q, end); //
????????????????????????????????????????????????????????????????????????
    }
}
*/
void
b_qsort (void *ptr, b_size_t count, b_size_t size, b_comp comp)
{
  b_quicksort (ptr, size, 0, count - 1, comp);
}

void *
b_bsearch (const void *key, const void *ptr, b_size_t count, b_size_t size,
           b_comp comp)
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

  for (; *str; ++str)
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
    }

  return sign_set == -1 ? -ret : ret;
}

static char b_membuf[1024];
static char *b_membuf_end = b_membuf + sizeof (b_membuf);
static char *b_memrover = b_membuf;

void *
b_malloc_impl (b_size_t size, b_size_t al)
{
  char *ret = b_memrover;

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

  if (ret + size >= b_membuf_end)
    {
      return B_NULL;
    }

  b_memrover = ret + size;
  return ret;
}

static b_size_t
b_alignof (b_size_t size)
{
  return size >= 16 ? 16 : size >= 8 ? 8 : size >= 4 ? 4 : size >= 2 ? 2 : 1;
}

void *
b_malloc (b_size_t size)
{
  return b_malloc_impl (size, b_alignof (size));
}

void *
b_calloc (b_size_t num, b_size_t size)
{
  const b_size_t total = num * size;

  void *ret = b_malloc_impl (total, b_alignof (size));
  return ret ? b_memset (ret, 0, total) : ret;
}

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
