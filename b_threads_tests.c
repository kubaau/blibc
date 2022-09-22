#include "b_threads.h"

#include "b_assert.h"
#include "b_time.h"

static b_mtx_t b_internal_mtx;
static int b_internal_tfunc (void *);

void
b_test_threads (void)
{
  b_thrd_t t[10];
  int total = 0;
  int i;

  b_mtx_init (&b_internal_mtx, b_mtx_plain);

  for (i = 0; i < 10; ++i)
    {
      b_thrd_create (t + i, b_internal_tfunc, &total);
    }

  for (i = 0; i < 10; i++)
    {
      b_thrd_join (t[i], B_NULL);
    }

  pthread_mutex_destroy (&b_internal_mtx);
  b_assert (total == 10000);
}

static int
b_internal_tfunc (void *arg)
{
  int *num = (int *)arg;
  struct b_timespec dur;
  int i;

  for (i = 0; i < 1000; ++i)
    {
      b_mtx_lock (&b_internal_mtx);
      ++*num;
      b_mtx_unlock (&b_internal_mtx);

      dur.tv_sec = 0;  /*1;*/
      dur.tv_nsec = 1; /*999999999;*/
      b_thrd_sleep (&dur, B_NULL);
    }

  return 0;
}
