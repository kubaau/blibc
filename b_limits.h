#ifndef B_LIMITS_H
#define B_LIMITS_H

#define B_BOOL_WIDTH 8
#define B_CHAR_BIT 8
#define B_MB_LEN_MAX 16
#define B_CHAR_WIDTH B_CHAR_BIT
#define B_CHAR_MIN -128
#define B_CHAR_MAX 127

#define B_SCHAR_WIDTH sizeof (char)
#define B_SHRT_WIDTH sizeof (short)
#define B_INT_WIDTH sizeof (int)
#define B_LONG_WIDTH sizeof (long)
#define B_LLONG_WIDTH B_LONG_WIDTH

#define B_SCHAR_MIN B_CHAR_MIN
#define B_SHRT_MIN -32768
#define B_INT_MIN -2147483648
#define B_LONG_MIN -9223372036854775808
#define B_LLONG_MIN B_LONG_MIN

#define B_SCHAR_MAX B_CHAR_MMAX
#define B_SHRT_MAX 32767
#define B_INT_MAX 2147483647
#define B_LONG_MAX 9223372036854775807
#define B_LLONG_MAX B_LONG_MAX

#define B_UCHAR_WIDTH sizeof (unsigned char)
#define B_USHRT_WIDTH sizeof (unsigned short)
#define B_UINT_WIDTH sizeof (unsigned)
#define B_ULONG_WIDTH sizeof (unsigned long)
#define B_ULLONG_WIDTH B_ULONG_WIDTH

#define B_UCHAR_MAX 255
#define B_USHRT_MAX 65535
#define B_UINT_MAX 4294967295
#define B_ULONG_MAX 18446744073709551615
#define B_ULLONG_MAX B_ULONG_MAX

#endif /* B_LIMITS_H */
