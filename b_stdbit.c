#include "b_stdbit.h"

#include "b_limits.h"

#define DEFINE_LEADING_MASK                                                   \
  B_STDBIT_GENERIC_VALUE_TYPE mask                                            \
      = 1 << (sizeof (B_STDBIT_GENERIC_VALUE_TYPE) * B_CHAR_BIT - 1)

#define DEFINE_TRAILING_MASK B_STDBIT_GENERIC_VALUE_TYPE mask = 1

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_first_leading_one (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  B_STDBIT_GENERIC_RETURN_TYPE ret;
  DEFINE_LEADING_MASK;
  for (ret = 1; ret <= sizeof (B_STDBIT_GENERIC_VALUE_TYPE) * B_CHAR_BIT;
       ++ret, mask >>= 1)
    if (mask & value)
      return ret;
  return 0;
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_first_leading_zero (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  return b_stdc_first_leading_one (~value);
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_first_trailing_one (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  B_STDBIT_GENERIC_RETURN_TYPE ret;
  DEFINE_TRAILING_MASK;
  for (ret = 1; ret <= sizeof (B_STDBIT_GENERIC_VALUE_TYPE) * B_CHAR_BIT;
       ++ret, mask <<= 1)
    if (mask & value)
      return ret;
  return 0;
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_first_trailing_zero (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  return b_stdc_first_trailing_one (~value);
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_leading_ones (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  const B_STDBIT_GENERIC_RETURN_TYPE first_leading_zero
      = b_stdc_first_leading_zero (value);
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

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_leading_zeros (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  return b_stdc_leading_ones (~value);
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_trailing_ones (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  const B_STDBIT_GENERIC_RETURN_TYPE first_trailing_zero
      = b_stdc_first_trailing_zero (value);
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

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_trailing_zeros (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  return b_stdc_trailing_ones (~value);
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_count_ones (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  B_STDBIT_GENERIC_RETURN_TYPE ret = 0;
  DEFINE_TRAILING_MASK;
  while (mask)
    {
      if (mask & value)
        ++ret;
      mask <<= 1;
    }
  return ret;
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_count_zeros (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  return b_stdc_count_ones (~value);
}

b_bool
b_stdc_has_single_bit (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  return value && !(value & (value - 1));
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_bit_width (B_STDBIT_GENERIC_VALUE_TYPE value)
{
  return value ? B_CHAR_BIT - b_stdc_leading_zeros (value) : 1;
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_bit_floor (B_STDBIT_GENERIC_VALUE_TYPE value)
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
  const B_STDBIT_GENERIC_RETURN_TYPE first_leading_one
      = b_stdc_first_leading_one (value);
  return first_leading_one ? 1 << (B_CHAR_BIT - first_leading_one) : 0;
  */
}

B_STDBIT_GENERIC_RETURN_TYPE
b_stdc_bit_ceil (B_STDBIT_GENERIC_VALUE_TYPE value)
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
