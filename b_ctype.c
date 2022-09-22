#define B_INTERNAL_IS_BETWEEN(ch, ch1, ch2) ((ch) >= (ch1) && (ch) <= (ch2))

int
b_islower (int ch)
{
  return B_INTERNAL_IS_BETWEEN (ch, 'a', 'z');
}

int
b_isupper (int ch)
{
  return B_INTERNAL_IS_BETWEEN (ch, 'A', 'Z');
}

int
b_isdigit (int ch)
{
  return B_INTERNAL_IS_BETWEEN (ch, '0', '9');
}

int
b_isalpha (int ch)
{
  return b_isupper (ch) || b_islower (ch);
}

int
b_isalnum (int ch)
{
  return b_isdigit (ch) || b_isalpha (ch);
}

int
b_tolower (int ch)
{
  return ch | 32;
}

int
b_toupper (int ch)
{
  return ch & ~32;
}

int
b_isxdigit (int ch)
{
  return b_isdigit (ch) || B_INTERNAL_IS_BETWEEN (b_tolower (ch), 'a', 'f');
}

int
b_iscntrl (int ch)
{
  return ((ch + 1) & 0x7F) <= ' ';
}

int
b_isgraph (int ch)
{
  return B_INTERNAL_IS_BETWEEN (ch, '!', '~');
}

int
b_isspace (int ch)
{
  return ch == ' ' || B_INTERNAL_IS_BETWEEN (ch, '\t', '\r');
}

int
b_isblank (int ch)
{
  return ch == '\t' || ch == ' ';
}

int
b_isprint (int ch)
{
  return B_INTERNAL_IS_BETWEEN (ch, ' ', '~');
}

int
b_ispunct (int ch)
{
  return b_isgraph (ch) && !b_isalnum (ch);
}
