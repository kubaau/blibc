#ifndef B_STDBIT_H
#define B_STDBIT_H

#include "b_stdbool.h"

unsigned int b_stdc_leading_zeros_uc (unsigned char value);
unsigned int b_stdc_leading_ones_uc (unsigned char value);
unsigned int b_stdc_trailing_zeros_uc (unsigned char value);
unsigned int b_stdc_trailing_ones_uc (unsigned char value);
unsigned int b_stdc_first_leading_zero_uc (unsigned char value);
unsigned int b_stdc_first_leading_one_uc (unsigned char value);
unsigned int b_stdc_first_trailing_zero_uc (unsigned char value);
unsigned int b_stdc_first_trailing_one_uc (unsigned char value);
unsigned int b_stdc_count_zeros_uc (unsigned char value);
unsigned int b_stdc_count_ones_uc (unsigned char value);
b_bool b_stdc_has_single_bit_uc (unsigned char value);
unsigned int b_stdc_bit_width_uc (unsigned char value);
unsigned char b_stdc_bit_floor_uc (unsigned char value);
unsigned char b_stdc_bit_ceil_uc (unsigned char value);

#endif /* B_STDBIT_H */
