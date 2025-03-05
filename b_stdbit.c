#include "b_stdbit.h"

#include "b_limits.h"

#define DEFINE_LEADING_MASK                                                   \
  unsigned char mask = 1 << (sizeof (unsigned char) * B_CHAR_BIT - 1)

#define DEFINE_TRAILING_MASK unsigned char mask = 1

unsigned int
b_stdc_first_leading_one_uc (unsigned char value)
{
  unsigned int ret;
  DEFINE_LEADING_MASK;
  for (ret = 1; ret <= sizeof (unsigned char) * B_CHAR_BIT; ++ret, mask >>= 1)
    if (mask & value)
      return ret;
  return 0;
}

unsigned int
b_stdc_first_leading_zero_uc (unsigned char value)
{
  return b_stdc_first_leading_one_uc (~value);
}

unsigned int
b_stdc_first_trailing_one_uc (unsigned char value)
{
  unsigned int ret;
  DEFINE_TRAILING_MASK;
  for (ret = 1; ret <= sizeof (unsigned char) * B_CHAR_BIT; ++ret, mask <<= 1)
    if (mask & value)
      return ret;
  return 0;
}

unsigned int
b_stdc_first_trailing_zero_uc (unsigned char value)
{
  return b_stdc_first_trailing_one_uc (~value);
}

unsigned int
b_stdc_leading_ones_uc (unsigned char value)
{
  const unsigned int first_leading_zero = b_stdc_first_leading_zero_uc (value);
  return first_leading_zero ? first_leading_zero - 1 : B_CHAR_BIT;

  /*
  while (mask & value)
    {
      ++ret;
      if (!(mask >>= 1))
        break;
    }
  return ret;
  */
}

unsigned int
b_stdc_leading_zeros_uc (unsigned char value)
{
  return b_stdc_leading_ones_uc (~value);
}

unsigned int
b_stdc_trailing_ones_uc (unsigned char value)
{
  const unsigned int first_trailing_zero
      = b_stdc_first_trailing_zero_uc (value);
  return first_trailing_zero ? first_trailing_zero - 1 : B_CHAR_BIT;

  /*
  while (mask & value)
    {
      ++ret;
      if (!(mask <<= 1))
        break;
    }
  return ret;
  */
}

unsigned int
b_stdc_trailing_zeros_uc (unsigned char value)
{
  return b_stdc_trailing_ones_uc (~value);
}

unsigned int
b_stdc_count_ones_uc (unsigned char value)
{
  unsigned int ret = 0;
  DEFINE_TRAILING_MASK;
  while (mask)
    {
      if (mask & value)
        ++ret;
      mask <<= 1;
    }
  return ret;
}

unsigned int
b_stdc_count_zeros_uc (unsigned char value)
{
  return b_stdc_count_ones_uc (~value);
}

b_bool
b_stdc_has_single_bit_uc (unsigned char value)
{
  return value && !(value & (value - 1));
}

unsigned int
b_stdc_bit_width_uc (unsigned char value)
{
  return value ? B_CHAR_BIT - b_stdc_leading_zeros_uc (value) : 1;
}

unsigned char
b_stdc_bit_floor_uc (unsigned char value)
{
  DEFINE_TRAILING_MASK;
  while (mask)
    {
      if (mask > value)
        return mask >> 1;
      if (mask == value)
        return mask;
      mask <<= 1;
    }
  return 1 << (B_CHAR_BIT - 1);

  /*
  const unsigned int first_leading_one
      = b_stdc_first_leading_one_uc (value);
  return first_leading_one ? 1 << (B_CHAR_BIT - first_leading_one) : 0;
  */
}

unsigned char
b_stdc_bit_ceil_uc (unsigned char value)
{
  DEFINE_TRAILING_MASK;
  while (mask)
    {
      if (mask >= value)
        return mask;
      mask <<= 1;
    }
  return 0;
}
