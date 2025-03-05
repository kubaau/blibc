#include "b_stdbit.h"

#include "b_assert.h"
#include "b_stddef.h"

void
b_test_stdc_leading_zeros (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_leading_zeros;

  b_assert (f (0) == 8);
  b_assert (f (1) == 7);
  b_assert (f (2) == 6);
  b_assert (f (3) == 6);
  b_assert (f (4) == 5);
  b_assert (f (7) == 5);
  b_assert (f (8) == 4);
  b_assert (f (0xFF) == 0);
  b_assert (f (0x80) == 0);
  b_assert (f (0x70) == 1);
  b_assert (f (0x30) == 2);
  b_assert (f (0x20) == 2);
  b_assert (f (0x10) == 3);
  b_assert (f (0x0F) == 4);
}

void
b_test_stdc_leading_ones (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_leading_ones;

  b_assert (f (0x80) == 1);
  b_assert (f (0xB0) == 1);
  b_assert (f (0xC0) == 2);
  b_assert (f (0xD0) == 2);
  b_assert (f (0xE0) == 3);
  b_assert (f (0xF0) == 4);
  b_assert (f (0xF8) == 5);
  b_assert (f (0xFC) == 6);
  b_assert (f (0xFE) == 7);
  b_assert (f (0xFF) == 8);
  b_assert (f (0) == 0);
  b_assert (f (0x7F) == 0);
}

void
b_test_stdc_trailing_zeros (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_trailing_zeros;

  b_assert (f (0) == 8);
  b_assert (f (1) == 0);
  b_assert (f (2) == 1);
  b_assert (f (3) == 0);
  b_assert (f (4) == 2);
  b_assert (f (7) == 0);
  b_assert (f (8) == 3);
  b_assert (f (0xF) == 0);
  b_assert (f (0x10) == 4);
  b_assert (f (0x11) == 0);
  b_assert (f (0x12) == 1);
  b_assert (f (0x13) == 0);
  b_assert (f (0x20) == 5);
  b_assert (f (0x40) == 6);
  b_assert (f (0x80) == 7);
}

void
b_test_stdc_trailing_ones (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_trailing_ones;

  b_assert (f (0) == 0);
  b_assert (f (1) == 1);
  b_assert (f (2) == 0);
  b_assert (f (3) == 2);
  b_assert (f (4) == 0);
  b_assert (f (7) == 3);
  b_assert (f (8) == 0);
  b_assert (f (0xF) == 4);
  b_assert (f (0x10) == 0);
  b_assert (f (0x11) == 1);
  b_assert (f (0x12) == 0);
  b_assert (f (0x13) == 2);
  b_assert (f (0x1F) == 5);
  b_assert (f (0x3F) == 6);
  b_assert (f (0x7F) == 7);
  b_assert (f (0xFF) == 8);
}

void
b_test_stdc_first_leading_zero (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_first_leading_zero;

  b_assert (f (0) == 1);
  b_assert (f (1) == 1);
  b_assert (f (2) == 1);
  b_assert (f (0x70) == 1);
  b_assert (f (0x80) == 2);
  b_assert (f (0xC0) == 3);
  b_assert (f (0xE0) == 4);
  b_assert (f (0xF0) == 5);
  b_assert (f (0xF8) == 6);
  b_assert (f (0xFC) == 7);
  b_assert (f (0xFE) == 8);
  b_assert (f (0xFF) == 0);
}

void
b_test_stdc_first_leading_one (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_first_leading_one;

  b_assert (f (0) == 0);
  b_assert (f (1) == 8);
  b_assert (f (2) == 7);
  b_assert (f (4) == 6);
  b_assert (f (8) == 5);
  b_assert (f (0x10) == 4);
  b_assert (f (0x20) == 3);
  b_assert (f (0x40) == 2);
  b_assert (f (0x80) == 1);
  b_assert (f (0xFF) == 1);
}

void
b_test_stdc_first_trailing_zero (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_first_trailing_zero;

  b_assert (f (0) == 1);
  b_assert (f (1) == 2);
  b_assert (f (2) == 1);
  b_assert (f (3) == 3);
  b_assert (f (4) == 1);
  b_assert (f (7) == 4);
  b_assert (f (8) == 1);
  b_assert (f (0xF) == 5);
  b_assert (f (0x1F) == 6);
  b_assert (f (0x3F) == 7);
  b_assert (f (0x7F) == 8);
  b_assert (f (0xFF) == 0);
}

void
b_test_stdc_first_trailing_one (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_first_trailing_one;

  b_assert (f (0) == 0);
  b_assert (f (1) == 1);
  b_assert (f (2) == 2);
  b_assert (f (3) == 1);
  b_assert (f (4) == 3);
  b_assert (f (7) == 1);
  b_assert (f (8) == 4);
  b_assert (f (0x10) == 5);
  b_assert (f (0x20) == 6);
  b_assert (f (0x40) == 7);
  b_assert (f (0x80) == 8);
}

void
b_test_stdc_count_zeros (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_count_zeros;

  b_assert (f (0) == 8);
  b_assert (f (1) == 7);
  b_assert (f (2) == 7);
  b_assert (f (3) == 6);
  b_assert (f (4) == 7);
  b_assert (f (7) == 5);
  b_assert (f (8) == 7);
  b_assert (f (0xF) == 4);
  b_assert (f (0x1F) == 3);
  b_assert (f (0x3F) == 2);
  b_assert (f (0xFE) == 1);
  b_assert (f (0x7F) == 1);
  b_assert (f (0xFF) == 0);
}

void
b_test_stdc_count_ones (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_count_ones;

  b_assert (f (0) == 0);
  b_assert (f (1) == 1);
  b_assert (f (2) == 1);
  b_assert (f (3) == 2);
  b_assert (f (4) == 1);
  b_assert (f (7) == 3);
  b_assert (f (8) == 1);
  b_assert (f (0xF) == 4);
  b_assert (f (0x1F) == 5);
  b_assert (f (0x3F) == 6);
  b_assert (f (0xFE) == 7);
  b_assert (f (0x7F) == 7);
  b_assert (f (0xFF) == 8);
}

void
b_test_stdc_has_single_bit (void)
{
  b_bool (*const f) (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_has_single_bit;

  b_assert (f (0) == 0);
  b_assert (f (1) == 1);
  b_assert (f (2) == 1);
  b_assert (f (3) == 0);
  b_assert (f (4) == 1);
  b_assert (f (7) == 0);
  b_assert (f (8) == 1);
  b_assert (f (0x10) == 1);
  b_assert (f (0x20) == 1);
  b_assert (f (0x40) == 1);
  b_assert (f (0x80) == 1);
  b_assert (f (0xFF) == 0);
}

void
b_test_stdc_bit_width (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_bit_width;

  b_assert (f (0) == 1);
  b_assert (f (1) == 1);
  b_assert (f (2) == 2);
  b_assert (f (3) == 2);
  b_assert (f (4) == 3);
  b_assert (f (7) == 3);
  b_assert (f (8) == 4);
  b_assert (f (0x10) == 5);
  b_assert (f (0x20) == 6);
  b_assert (f (0x40) == 7);
  b_assert (f (0x80) == 8);
  b_assert (f (0xFF) == 8);
}

void
b_test_stdc_bit_floor (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_bit_floor;

  b_assert (f (0) == 0);
  b_assert (f (1) == 1);
  b_assert (f (2) == 2);
  b_assert (f (3) == 2);
  b_assert (f (4) == 4);
  b_assert (f (7) == 4);
  b_assert (f (8) == 8);
  b_assert (f (16) == 16);
  b_assert (f (17) == 16);
  b_assert (f (128) == 128);
  b_assert (f (0xFF) == 128);
}

void
b_test_stdc_bit_ceil (void)
{
  B_STDBIT_GENERIC_RETURN_TYPE (*const f)
  (B_STDBIT_GENERIC_VALUE_TYPE) = b_stdc_bit_ceil;

  b_assert (f (0) == 1);
  b_assert (f (1) == 1);
  b_assert (f (2) == 2);
  b_assert (f (3) == 4);
  b_assert (f (4) == 4);
  b_assert (f (7) == 8);
  b_assert (f (8) == 8);
  b_assert (f (16) == 16);
  b_assert (f (17) == 32);
  b_assert (f (128) == 128);
  b_assert (f (0xFF) == 0);
}
