#include "b_inttypes.h"

b_intmax_t
b_imaxabs (b_intmax_t n)
{
  return b_labs (n);
}

b_imaxdiv_t
b_imaxdiv (b_intmax_t x, b_intmax_t y)
{
  return b_ldiv (x, y);
}
