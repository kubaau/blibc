#ifndef B_STDLIB_H
#define B_STDLIB_H

#define B_EXIT_SUCCESS 0
#define B_EXIT_FAILURE 1

#ifndef B_SIZE_T
#define B_SIZE_T
typedef unsigned long b_size_t;
#endif /* B_SIZE_T */

#ifndef B_NULL
#define B_NULL 0
#endif /* B_NULL */

#define RAND_MAX 2147483647

void b_abort (void);

void b_qsort (void *ptr, b_size_t count, b_size_t size,
              int (*comp) (const void *, const void *));
void *b_bsearch (const void *key, const void *ptr, b_size_t count,
                 b_size_t size, int (*comp) (const void *, const void *));

int b_atoi (const char *str);
long b_atol (const char *str);

void *b_malloc (b_size_t size);
void *b_calloc (b_size_t num, b_size_t size);
void *b_realloc (void *ptr, b_size_t new_size);
void b_free (void *ptr);
void b_free_sized (void *ptr, b_size_t size);
void b_free_aligned_sized (void *ptr, b_size_t alignment, b_size_t size);
void *b_aligned_alloc (b_size_t alignment, b_size_t size);

int b_abs (int n);
long b_labs (long n);

typedef struct
{
  int quot;
  int rem;
} b_div_t;

typedef struct
{
  long quot;
  long rem;
} b_ldiv_t;

b_div_t b_div (int x, int y);
b_ldiv_t b_ldiv (long x, long y);

int b_rand ();
void b_srand (unsigned seed);

#endif /* B_STDLIB_H */
