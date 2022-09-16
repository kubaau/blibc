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

#endif /* B_STDLIB_H */
