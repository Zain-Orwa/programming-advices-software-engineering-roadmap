#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

/* IO Functions */
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);

/* String Functions */
size_t	ft_strlen(const char *str);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/* C00 Functions (you already have these) */

/* String Functions Part 2 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* Conversion Functions */
int		ft_atoi(const char *str);

#endif
