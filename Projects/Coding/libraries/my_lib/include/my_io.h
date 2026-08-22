#ifndef MY_IO_H
#define MY_IO_H

#include <unistd.h>

/* io */
void    my_putchar(char c);
void    my_putstr(const char *str);
void    my_putendl(const char *str);
void    my_putnbr(int num);
void 		my_putnbr_base(int num, const char *base);

#endif

