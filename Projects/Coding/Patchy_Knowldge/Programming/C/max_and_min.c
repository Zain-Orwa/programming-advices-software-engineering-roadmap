/* max and min array in c*/
#include <stdio.h>

int	main(void)
{
	int hey[] = {9, 72, 420, 1, 69};
	int max = hey[0];
	
	for (int femboy = 1; femboy < 5; femboy++)
	{
		if (max < hey[femboy]) //min: max > hey[femboy];  
			max = hey[femboy];
	}
	printf("%d\n", max);

	return (0);
}

