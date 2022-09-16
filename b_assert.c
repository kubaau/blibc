#include "b_assert.h"

#include "b_stdlib.h"
#include "b_string.h"

#include <unistd.h>

static char *
b_strrev (char *dest)
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
b_itoa (char *dest, int i)
{
  char *dest_runner = dest;

  if (i == 0)
    {
      *dest_runner = '0';
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

  if (i < 0)
    {
      b_strrev (dest + 1);
    }
  else
    {
      b_strrev (dest);
    }
  return dest;
}

void
b_assertfailed (const char *file, int line, const char *condition)
{
  char itoa_buf[10] = { 0 };
  char buf[1024] = { 0 };

  b_itoa (itoa_buf, line);

  b_strcat (buf, "assertion failed: ");
  b_strcat (buf, file);
  b_strcat (buf, "(");
  b_strcat (buf, itoa_buf);
  b_strcat (buf, ")");
  b_strcat (buf, ": ");
  b_strcat (buf, condition);
  b_strcat (buf, "\n");

  if (write (2, buf, b_strlen (buf)))
    {
    }
  b_abort ();
}
