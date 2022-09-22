#ifndef B_ERRNO_H
#define B_ERRNO_H

extern int b_internal_errno;
#define b_errno b_internal_errno

#define B_EINTR 4
#define B_ENOMEM 12
#define B_EBUSY 16
#define B_EDOM 33
#define B_ERANGE 34
#define B_EDEADLK 35
#define B_ETIMEDOUT 110

typedef int b_errno_t;

#endif /* B_ERRNO_H */
