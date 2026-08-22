#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>

/* string */
size_t  my_strlen(const char *str);
char    *my_strcpy(char *dst, const char *src);
char    *my_strncpy(char *dst, const char *src, size_t num);
size_t  my_strlcpy(char *dst, const char *src, size_t size);
int     my_strcmp(const char *str1, const char *str2);
int     my_strncmp(const char *str1, const char *str2, size_t num);
char    *my_strstr(const char *haystack, const char *needle);
char    *my_strcat(char *dst, const char *src);
char    *my_strncat(char *dst, const char *src, size_t num);
int     my_atoi(const char *str);
int     my_atoi_base(const char *str, const char *base);
size_t  my_strlcat(char *dst, const char *src, size_t size);
int     my_str_is_alpha(const char *str);
int     my_str_is_numeric(const char *str);
int     my_str_is_lowercase(const char *str);
int     my_str_is_uppercase(const char *str);
int     my_str_is_printable(const char *str);
char 		*my_str_to_uppercase(char *str);
char 		*my_str_to_lowercase(char *str);
char    *my_str_capitalize(char *str);


#endif 
