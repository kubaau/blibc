#ifndef B_ERRNO_H
#define B_ERRNO_H

extern int b_internal_errno;
#define b_errno b_internal_errno

#define B_EDOM 33
#define B_ERANGE 34

#endif /* B_ERRNO_H */
