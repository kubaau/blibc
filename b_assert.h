#ifndef B_ASSERT_H
#define B_ASSERT_H

#ifdef B_NDEBUG
#define b_assert(condition) ((void)0)
#else
#define b_assert(condition)                                                   \
  if (condition)                                                              \
    {                                                                         \
    }                                                                         \
  else                                                                        \
    {                                                                         \
      void b_assertfailed ();                                                 \
      b_assertfailed (__FILE__, __LINE__, #condition);                        \
    }
#endif /* B_NDEBUG */

#endif /* B_ASSERT_H */
