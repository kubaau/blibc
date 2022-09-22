#ifndef B_THREADS_H
#define B_THREADS_H

struct b_timespec;

#define _GNU_SOURCE
#include <pthread.h>
#undef _GNU_SOURCE

typedef pthread_t b_thrd_t;
typedef int (*b_thrd_start_t) (void *);

int b_thrd_create (b_thrd_t *thr, b_thrd_start_t func, void *arg);
int b_thrd_equal (b_thrd_t lhs, b_thrd_t rhs);
b_thrd_t b_thrd_current (void);
int b_thrd_sleep (const struct b_timespec *duration,
                  struct b_timespec *remaining);
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

typedef pthread_mutex_t b_mtx_t;

int b_mtx_init (b_mtx_t *mutex, int type);
int b_mtx_lock (b_mtx_t *mutex);
int b_mtx_timedlock (b_mtx_t *mutex, const struct b_timespec *time_point);
int b_mtx_trylock (b_mtx_t *mutex);
int b_mtx_unlock (b_mtx_t *mutex);
void b_mtx_destroy (b_mtx_t *mutex);

enum
{
  b_mtx_plain,
  b_mtx_recursive,
  b_mtx_timed
};

typedef pthread_once_t b_once_flag;
void b_call_once (b_once_flag *flag, void (*func) (void));
#define B_ONCE_FLAG_INIT PTHREAD_ONCE_INIT

typedef pthread_cond_t b_cnd_t;

int b_cnd_init (b_cnd_t *cond);
int b_cnd_signal (b_cnd_t *cond);
int b_cnd_broadcast (b_cnd_t *cond);
int b_cnd_wait (b_cnd_t *cond, b_mtx_t *mutex);
int b_cnd_timedwait (b_cnd_t *cond, b_mtx_t *mutex,
                     const struct b_timespec *time_point);
void b_cnd_destroy (b_cnd_t *cond);

typedef pthread_key_t b_tss_t;
#define B_TSS_DTOR_ITERATIONS PTHREAD_DESTRUCTOR_ITERATIONS
typedef void (*b_tss_dtor_t) (void *);

int b_tss_create (b_tss_t *tss_key, b_tss_dtor_t destructor);
void *b_tss_get (b_tss_t tss_key);
int b_tss_set (b_tss_t tss_id, void *val);
void b_tss_delete (b_tss_t tss_id);

#endif /* B_THREADS_H */
