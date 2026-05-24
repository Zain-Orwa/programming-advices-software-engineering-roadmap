
#include <cstdlib>

int	RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1) + From);
}

void	FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
		for (short j = 0; j < Cols; j++)
			arr[i][j] = RandomNumber(1, 100);
}

void	PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{	
		for (short j = 0; j < Cols; j++)
			std::cout << std::setw(3) << arr[i][j] << "		";
		std::cout << "\n";
	}
}

void	SumAndPrintEachColInMatrix(int arr[3][3], short Rows, short Cols)
{
	int sum;

	for (short i = 0; i < Rows; i++)
	{
		sum = 0;
		for (short j = 0; j < Cols; j++)
		{
			sum += arr[j][i];	
		}
		std::cout << "Col " << i + 1 << " Sum = " << sum << std::endl; 
	}
}

int main(void)
{
	//seed the random number generator, only once
	srand((unsigned)time(NULL));
	
	int arr[3][3];

	FillMatrixWithRandomNumbers(arr, 3, 3);

	std::cout << "\n The following is a 3x3 random matrix:\n";
	PrintMatrix(arr, 3, 3);

	std::cout << "\nThe following are the sum of each column int the matrix:\n";
	SumAndPrintEachColInMatrix(arr, 3, 3);

	return (0);
}
