#ifndef B_TIME_H
#define B_TIME_H

#ifndef B_SIZE_T
#define B_SIZE_T
typedef unsigned long b_size_t;
#endif /* B_SIZE_T */

#ifndef B_NULL
#define B_NULL 0
#endif /* B_NULL */

typedef unsigned long b_time_t;

typedef struct b_timespec
{
  b_time_t tv_sec;
  long tv_nsec;
} b_timespec;

typedef struct
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
} tm;

#endif /* B_TIME_H */
