#ifndef B_CTYPE_H
#define B_CTYPE_H

int b_isalnum (int ch);
int b_isalpha (int ch);
int b_islower (int ch);
int b_isupper (int ch);
int b_isdigit (int ch);
int b_isxdigit (int ch);
int b_iscntrl (int ch);
int b_isgraph (int ch);
int b_isspace (int ch);
int b_isblank (int ch);
int b_isprint (int ch);
int b_ispunct (int ch);

int b_tolower (int ch);
int b_toupper (int ch);

#endif /* B_CTYPE_H */
