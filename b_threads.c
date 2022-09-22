#include "b_threads.h"

#include "b_errno.h"
#include "b_time.h"

#include <errno.h>

int
b_thrd_create (b_thrd_t *thr, b_thrd_start_t func, void *arg)
{
#ifndef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
  const int res = pthread_create (thr, 0, (void *(*)(void *))func, arg);
#ifndef __clang__
#pragma GCC diagnostic pop
#endif
  return res == 0          ? b_thrd_success
         : res == B_ENOMEM ? b_thrd_nomem
                           : b_thrd_error;
}

int
b_thrd_equal (b_thrd_t lhs, b_thrd_t rhs)
{
  return pthread_equal (lhs, rhs);
}

b_thrd_t
b_thrd_current (void)
{
  return pthread_self ();
}

int
b_thrd_sleep (const struct b_timespec *duration, struct b_timespec *remaining)
{
  return nanosleep ((void *)duration, (void *)remaining) == 0 ? 0
         : (b_errno = errno) == B_EINTR                       ? -1
                                                              : -2;
}

void
b_thrd_yield (void)
{
  sched_yield ();
}

void
b_thrd_exit (int res)
{
  pthread_exit ((void *)(b_size_t)res);
}

int
b_thrd_detach (b_thrd_t thr)
{
  return pthread_detach (thr) == 0 ? b_thrd_success : b_thrd_error;
}

int
b_thrd_join (b_thrd_t thr, int *res)
{
  void *ret;
  if (pthread_join (thr, &ret) != 0)
    {
      return b_thrd_error;
    }
  if (res)
    {
      *res = (long)ret;
    }
  return b_thrd_success;
}

int
b_mtx_init (b_mtx_t *mutex, int type)
{
  pthread_mutexattr_t attr;
  int ret;

  pthread_mutexattr_init (&attr);

  if (type & b_mtx_timed)
    {
      pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_TIMED_NP);
    }
  if (type & b_mtx_recursive)
    {
      pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE);
    }

  ret = pthread_mutex_init (mutex, &attr) == 0 ? b_thrd_success : b_thrd_error;
  pthread_mutexattr_destroy (&attr);
  return ret;
}

int
b_mtx_lock (b_mtx_t *mutex)
{
  const int res = pthread_mutex_lock (mutex);
  return res == 0           ? b_thrd_success
         : res == B_EDEADLK ? b_thrd_busy
                            : b_thrd_error;
}

int
b_mtx_timedlock (b_mtx_t *mutex, const struct b_timespec *time_point)
{
  const int res
      = pthread_mutex_timedlock (mutex, (struct timespec *)time_point);
  return res == 0             ? b_thrd_success
         : res == B_ETIMEDOUT ? b_thrd_timedout
                              : b_thrd_error;
}

int
b_mtx_trylock (b_mtx_t *mutex)
{
  const int res = pthread_mutex_trylock (mutex);
  return res == 0         ? b_thrd_success
         : res == B_EBUSY ? b_thrd_busy
                          : b_thrd_error;
}

int
b_mtx_unlock (b_mtx_t *mutex)
{
  return pthread_mutex_unlock (mutex) == 0 ? b_thrd_success : b_thrd_error;
}

void
b_mtx_destroy (b_mtx_t *mutex)
{
  pthread_mutex_destroy (mutex);
}

void
b_call_once (b_once_flag *flag, void (*func) (void))
{
  pthread_once (flag, func);
}

int
b_cnd_init (b_cnd_t *cond)
{
  return pthread_cond_init (cond, B_NULL) == 0 ? b_thrd_success : b_thrd_error;
}

int
b_cnd_signal (b_cnd_t *cond)
{
  return pthread_cond_signal (cond) == 0 ? b_thrd_success : b_thrd_error;
}

int
b_cnd_broadcast (b_cnd_t *cond)
{
  return pthread_cond_broadcast (cond) == 0 ? b_thrd_success : b_thrd_error;
}

int
b_cnd_wait (b_cnd_t *cond, b_mtx_t *mutex)
{
  return pthread_cond_wait (cond, mutex) == 0 ? b_thrd_success : b_thrd_error;
}

int
b_cnd_timedwait (b_cnd_t *cond, b_mtx_t *mutex,
                 const struct b_timespec *time_point)
{
  const int res = pthread_cond_timedwait (cond, mutex,
                                          (const struct timespec *)time_point);
  return res == 0           ? b_thrd_success
         : res == ETIMEDOUT ? b_thrd_timedout
                            : b_thrd_error;
}

void
b_cnd_destroy (b_cnd_t *cond)
{
  pthread_cond_destroy (cond);
}

int
b_tss_create (b_tss_t *tss_key, b_tss_dtor_t destructor)
{
  return pthread_key_create (tss_key, destructor) == 0 ? b_thrd_success
                                                       : b_thrd_error;
}

void *
b_tss_get (b_tss_t tss_key)
{
  return pthread_getspecific (tss_key);
}

int
b_tss_set (b_tss_t tss_id, void *val)
{
  return pthread_setspecific (tss_id, val) == 0 ? b_thrd_success
                                                : b_thrd_error;
}

void
b_tss_delete (b_tss_t tss_id)
{
  pthread_key_delete (tss_id);
}
