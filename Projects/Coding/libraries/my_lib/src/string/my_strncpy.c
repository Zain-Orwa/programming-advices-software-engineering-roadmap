#include "my_string.h"

/*
** Copies up to num bytes from str_src to str_dst.
** If str_src is shorter than num, the rest is filled with '\0'.
** Returns str_dst.
*/
char	*my_strncpy(char *str_dst, const char *str_src, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && str_src[i] != '\0')
	{
		str_dst[i] = str_src[i];
		i++;
	}
	while (i < num)
	{
		str_dst[i] = '\0';
		i++;
	}
	return (str_dst);
}

