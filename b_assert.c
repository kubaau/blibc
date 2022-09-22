#include "b_string.h"

#include <unistd.h>

static char *b_internal_itoa ();

void
b_assertfailed (const char *file, int line, const char *condition)
{
  char buf[1024] = { 0 };
  char itoa_buf[10];
  void b_abort ();

  b_internal_itoa (itoa_buf, line);

  b_strcat (buf, "assertion failed: ");
  b_strcat (buf, file);
  b_strcat (buf, "(");
  b_strcat (buf, itoa_buf);
  b_strcat (buf, ")");
  b_strcat (buf, ": ");
  b_strcat (buf, condition);
  b_strcat (buf, "\n");

  (void)-(write (2, buf, b_strlen (buf)));
  /*b_abort ();*/
}

static char *
b_internal_strrev (char *dest)
{
  const b_size_t len = b_strlen (dest);
  const b_size_t half_len = len / 2;
  const b_size_t last = len - 1;
  b_size_t i;
  b_size_t j;
  char temp;

  for (i = 0; i < half_len; ++i)
    {
      temp = dest[i];
      j = last - i;
      dest[i] = dest[j];
      dest[j] = temp;
    }
  return dest;
}

static char *
b_internal_itoa (char *dest, int i)
{
  char *dest_runner = dest;

  if (i == 0)
    {
      *dest_runner++ = '0';
      *dest_runner = B_NULL;
      return dest;
    }

  if (i < 0)
    {
      *dest_runner++ = '-';
    }

  while (i)
    {
      *dest_runner++ = '0' + i % 10;
      i /= 10;
    }

  *dest_runner = B_NULL;
  b_internal_strrev (i >= 0 ? dest : dest + 1);
  return dest;
}
