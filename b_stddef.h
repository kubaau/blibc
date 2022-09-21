#ifndef B_STDDEF_H
#define B_STDDEF_H

#ifndef B_SIZE_T
#define B_SIZE_T
typedef unsigned long b_size_t;
#endif /* B_SIZE_T */

typedef long b_ptrdiff_t;

#ifndef B_NULL
#define B_NULL 0
#endif /* B_NULL */

#define b_offsetof(type, member) ((b_size_t) & (((type *)0)->member))

typedef b_size_t b_rsize_t;

typedef long double b_max_align_t;

#endif /* B_STDDEF_H */
