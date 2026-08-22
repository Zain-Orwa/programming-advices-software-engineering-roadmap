#include "my_io.h"

void	my_putnbr(int num)
{
	long	nb;

	nb = num;
	if (nb < 0)
	{
		my_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		my_putnbr((int)(nb / 10));
	my_putchar((char)('0' + (nb % 10)));
}

