#ifndef B_STDINT_H
#define B_STDINT_H

typedef char b_int8_t;
typedef short b_int16_t;
typedef int b_int32_t;
typedef long b_int64_t;

typedef b_int8_t b_int_fast8_t;
typedef b_int16_t b_int_fast16_t;
typedef b_int32_t b_int_fast32_t;
typedef b_int64_t b_int_fast64_t;

typedef b_int8_t b_int_least8_t;
typedef b_int16_t b_int_least16_t;
typedef b_int32_t b_int_least32_t;
typedef b_int64_t b_int_least64_t;

typedef b_int64_t b_intmax_t;

typedef b_int64_t b_intptr_t;

typedef unsigned char b_uint8_t;
typedef unsigned short b_uint16_t;
typedef unsigned int b_uint32_t;
typedef unsigned long b_uint64_t;

typedef b_uint8_t b_uint_fast8_t;
typedef b_uint16_t b_uint_fast16_t;
typedef b_uint32_t b_uint_fast32_t;
typedef b_uint64_t b_uint_fast64_t;

typedef b_uint8_t b_uint_least8_t;
typedef b_uint16_t b_uint_least16_t;
typedef b_uint32_t b_uint_least32_t;
typedef b_uint64_t b_uint_least64_t;

typedef b_uint64_t b_uintmax_t;

typedef b_uint64_t b_uintptr_t;

#define INT8_MIN -128
#define INT16_MIN -32768
#define INT32_MIN -2147483648
#define INT64_MIN -9223372036854775808

#define INT_FAST8_MIN INT8_MIN
#define INT_FAST16_MIN INT16_MIN
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST64_MIN INT64_MIN

#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST64_MIN INT64_MIN

#define INTPTR_MIN INT64_MIN

#define INTMAX_MIN INT64_MIN

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807

#define INT_FAST8_MAX INT8_MAX
#define INT_FAST16_MAX INT16_MAX
#define INT_FAST32_MAX INT32_MAX
#define INT_FAST64_MAX INT64_MAX

#define INT_LEAST8_MAX INT8_MAX
#define INT_LEAST16_MAX INT16_MAX
#define INT_LEAST32_MAX INT32_MAX
#define INT_LEAST64_MAX INT64_MAX

#define INTPTR_MAX INT64_MAX

#define INTMAX_MAX INT64_MAX

#define UINT8_MAX 255
#define UINT16_MAX 65535
#define UINT32_MAX 4294967295
#define UINT64_MAX 18446744073709551615

#define UINT_FAST8_MAX UINT8_MAX
#define UINT_FAST16_MAX UINT16_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define UINT_LEAST8_MAX UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define UINTPTR_MAX UINT64_MAX

#define UINTMAX_MAX UINT64_MAX

#define INT8_C(n) (b_int8_t)(n)
#define INT16_C(n) (b_int16_t)(n)
#define INT32_C(n) (b_int32_t)(n)
#define INT64_C(n) (b_int64_t)(n)

#define INTMAX_C(n) (b_intmax_t)(n)

#define UINT8_C(n) (b_uint8_t)(n)
#define UINT16_C(n) (b_uint16_t)(n)
#define UINT32_C(n) (b_uint32_t)(n)
#define UINT64_C(n) (b_uint64_t)(n)

#define UINTMAX_C(n) (b_uintmax_t)(n)

#define RSIZE_MAX UINT64_MAX

#endif /* B_STDINT_H */
