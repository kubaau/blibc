#ifndef B_STRING_H
#define B_STRING_H

#ifndef B_SIZE_T
#define B_SIZE_T
typedef unsigned long b_size_t;
#endif /* B_SIZE_T */

#ifndef B_NULL
#define B_NULL 0
#endif /* B_NULL */

char *b_strcpy (char *dest, const char *src);
char *b_strncpy (char *dest, const char *src, b_size_t count);
char *b_strcat (char *dest, const char *src);
char *b_strncat (char *dest, const char *src, b_size_t count);
char *b_strdup (const char *src);
char *b_strndup (const char *src, b_size_t size);

b_size_t b_strlen (const char *str);
int b_strcmp (const char *lhs, const char *rhs);
int b_strncmp (const char *lhs, const char *rhs, b_size_t count);
char *b_strchr (const char *str, int ch);
char *b_strrchr (const char *str, int ch);
b_size_t b_strspn (const char *dest, const char *src);
b_size_t b_strcspn (const char *dest, const char *src);
char *b_strpbrk (const char *dest, const char *breakset);
char *b_strstr (const char *str, const char *substr);
char *b_strtok (char *str, const char *delim);

void *b_memchr (const void *ptr, int ch, b_size_t count);
int b_memcmp (const void *lhs, const void *rhs, b_size_t count);
void *b_memset (void *dest, int ch, b_size_t count);
void *b_memcpy (void *dest, const void *src, b_size_t count);
void *b_memmove (void *dest, const void *src, b_size_t count);
void *b_memccpy (void *dest, const void *src, int c, b_size_t count);

char *b_strerror (int errnum);

#endif /* B_STRING_H */
