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

struct b_timespec
{
  b_time_t tv_sec;
  long tv_nsec;
};

#endif /* B_TIME_H */
