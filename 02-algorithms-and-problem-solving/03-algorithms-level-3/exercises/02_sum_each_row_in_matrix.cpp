#include <iostream>
#include <iomanip>
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

void	SumMatrixRows(int arr[3][3], int sum[3], short Rows, short Cols)
{

	for (short i = 0; i < Rows; i++)
	{
		sum[i] = 0;
		for (short j = 0; j < Cols; j++)
			sum[i] += arr[i][j];	
	}
}

void	PrintRowSum(int arr[], short size)
{
	for (short i = 0; i < size; i++)
		std::cout << "Row " << i + 1 << " Sum = " << arr[i] << "\n";
}

int main(void)
{
	//seed the random number generator, only once
	srand((unsigned)time(NULL));
	
	int arr[3][3];
	int sum[3] = {0};

	FillMatrixWithRandomNumbers(arr, 3, 3);

	std::cout << "\n The following is a 3x3 random matrix:\n";
	PrintMatrix(arr, 3, 3);

	SumMatrixRows(arr, sum, 3, 3);

	std::cout << "\n The following are the sum of each row int the matrix:\n";
	PrintRowSum(sum, 3);
	

	return (0);
}
