#ifndef B_INTTYPES_H
#define B_INTTYPES_H

#include "b_stdint.h"
#include "b_stdlib.h"

typedef b_ldiv_t b_imaxdiv_t;

b_intmax_t b_imaxabs (b_intmax_t n);
b_imaxdiv_t b_imaxdiv (b_intmax_t x, b_intmax_t y);

#endif /* B_INTTYPES_H */
