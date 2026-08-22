#include "libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	buffer[100];
	
	printf("=== Testing libft ===\n\n");
	
	// Test ft_strlen
	printf("ft_strlen(\"Hello\"): %zu\n", ft_strlen("Hello"));
	printf("strlen(\"Hello\"):    %zu\n\n", strlen("Hello"));
	
	// Test ft_strcpy
	ft_strcpy(buffer, "Hello World");
	printf("ft_strcpy: %s\n\n", buffer);
	
	// Test ft_strcmp
	printf("ft_strcmp(\"abc\", \"abc\"): %d\n", ft_strcmp("abc", "abc"));
	printf("strcmp(\"abc\", \"abc\"):    %d\n\n", strcmp("abc", "abc"));
	
	// Test IO functions
	printf("IO functions:\n");
	ft_putstr("ft_putstr: Hello from libft!\n");
	ft_putstr("ft_putnbr: ");
	ft_putnbr(42);
	ft_putchar('\n');
	
	return (0);
}
