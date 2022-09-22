#include "b_stdlib.h"

#include "b_ctype.h"
#include "b_stddef.h"
#include "b_string.h"

typedef int (*b_internal_comp) (const void *, const void *);
static void b_internal_quicksort ();

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

typedef struct b_internal_memblock
{
  b_size_t size;
  struct b_internal_memblock *next;
  char free;
} b_internal_memblock;

void *
b_malloc (b_size_t size)
{
  return b_aligned_alloc (sizeof (b_max_align_t), size);
}

void *
b_calloc (b_size_t num, b_size_t size)
{
  const b_size_t total = num * size;

  void *ret = b_malloc (total);
  return ret ? b_memset (ret, 0, total) : ret;
}

void *
b_realloc (void *ptr, b_size_t new_size)
{
  b_internal_memblock *memblock;
  void *ret;

  if (!ptr)
    {
      return b_malloc (new_size);
    }

  memblock = (b_internal_memblock *)ptr - 1;
  if (memblock->size >= new_size)
    {
      return ptr;
    }

  ret = b_malloc (new_size);

  if (!ret)
    {
      return B_NULL;
    }

  b_memcpy (ret, ptr, memblock->size);
  b_free (ptr);
  return ret;
}

void
b_free (void *ptr)
{
  b_internal_memblock *memblock;

  if (!ptr)
    {
      return;
    }

  memblock = (b_internal_memblock *)ptr - 1;
  memblock->free = 1;
}

void
b_free_sized (void *ptr, b_size_t size)
{
  (void)size;
  b_free (ptr);
}

void
b_free_aligned_sized (void *ptr, b_size_t alignment, b_size_t size)
{
  (void)alignment;
  (void)size;
  b_free (ptr);
}

void *
b_aligned_alloc (b_size_t alignment, b_size_t size)
{
#define B_INTERNAL_SBRK_FAILED(result) ((result) == (void *)-1)
#define B_INTERNAL_ALIGNMENT_REMAINDER(ptr, alignment)                        \
  ((b_size_t)(ptr) % (alignment))
  void *sbrk ();

  static b_internal_memblock *base;
  b_size_t size_with_header;
  b_internal_memblock *prev;
  b_internal_memblock *ret;
  b_size_t al_remainder;
  b_size_t req_size;

  if (!base)
    {
      if (B_INTERNAL_SBRK_FAILED (base = sbrk (sizeof (*base))))
        {
          return base = B_NULL;
        }
      else
        {
          b_memset (base, 0, sizeof (*base));
        }
    }

  for (ret = base, prev = ret; ret; prev = ret, ret = ret->next)
    {
      if (!ret->free)
        {
          continue;
        }
      if (ret->size < size)
        {
          continue;
        }
      if (B_INTERNAL_ALIGNMENT_REMAINDER (ret + 1, alignment))
        {
          continue;
        }
      ret->free = 0;
      return ret + 1;
    }

  ret = sbrk (0);
  size_with_header = size + sizeof (b_internal_memblock);
  req_size = size_with_header;
  if ((al_remainder = B_INTERNAL_ALIGNMENT_REMAINDER (ret + 1, alignment)))
    {
      req_size += alignment - al_remainder;
    }
  if (B_INTERNAL_SBRK_FAILED (sbrk (req_size)))
    {
      return B_NULL;
    }
  ret = (b_internal_memblock *)((char *)ret + req_size - size_with_header);

  prev->next = ret;
  ret->size = size;
  ret->next = B_NULL;
  ret->free = 0;
  return ret + 1;
#undef B_INTERNAL_ALIGNMENT_REMAINDER
#undef B_INTERNAL_SBRK_FAILED
}

#define B_INTERNAL_ABS(n) (n >= 0 ? n : -n)
int
b_abs (int n)
{
  return B_INTERNAL_ABS (n);
}

long
b_labs (long n)
{
  return B_INTERNAL_ABS (n);
}
#undef B_INTERNAL_ABS

#define B_INTERNAL_DIV(type)                                                  \
  type ret;                                                                   \
  ret.quot = x / y;                                                           \
  ret.rem = x % y;                                                            \
  return ret;

b_div_t
b_div (int x, int y)
{
  B_INTERNAL_DIV (b_div_t);
}

b_ldiv_t
b_ldiv (long x, long y)
{
  B_INTERNAL_DIV (b_ldiv_t);
}
#undef B_INTERNAL_DIV

static unsigned b_internal_seed = 1;

int
b_rand ()
{
  return b_internal_seed++;
}

void
b_srand (unsigned seed)
{
  b_internal_seed = seed;
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
