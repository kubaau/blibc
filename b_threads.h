#ifndef B_THREADS_H
#define B_THREADS_H

typedef int b_thrd_t;
typedef int (*b_thrd_start_t) (void *);

int b_thrd_create (b_thrd_t *thr, b_thrd_start_t func, void *arg);
int b_thrd_equal (b_thrd_t lhs, b_thrd_t rhs);
b_thrd_t b_thrd_current (void);
int b_thrd_sleep (const struct timespec *duration, struct timespec *remaining);
void b_thrd_yield (void);
void b_thrd_exit (int res);
int b_thrd_detach (b_thrd_t thr);
int b_thrd_join (b_thrd_t thr, int *res);

enum
{
  b_thrd_success,
  b_thrd_nomem,
  b_thrd_timedout,
  b_thrd_busy,
  b_thrd_error
};

#endif /* B_THREADS_H */
