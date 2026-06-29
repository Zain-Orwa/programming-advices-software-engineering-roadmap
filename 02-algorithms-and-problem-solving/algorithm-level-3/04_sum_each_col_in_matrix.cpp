#include <iostream>
#include <iomanip>
#include <ctime>

int	RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1) + From);
}

void	FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
		for (short j  = 0; j < Cols; j++)
			arr[i][j] = RandomNumber(1, 100);
}



void	PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{
		for (short j  = 0; j < Cols; j++)
			std::cout << arr[i][j] << "		";
		std::cout << "\n";
	}
	
}

int	ColSum(int arr[3][3], short Rows, short ColNumber)
{
	int	Sum = 0;
	for (short i = 0; i < Rows; i++)
	{
		Sum += arr[i][ColNumber]; 
	}
	return (Sum);
}

void	PrintEachColSum(int arr[3][3], short Rows, short Cols)
{
	std::cout << "\nThe following is sum of each Col in the matrix:\n";
	for (short j = 0; j < Cols; j++)
	{
		std::cout << " Col " << j + 1 << " Sum "<< ColSum(arr, Rows, j) << std::endl;
	}
}


int main(void)
{
	srand((unsigned)time(NULL));

	int arr[3][3];

	FillMatrixWithRandomNumbers(arr, 3, 3);
	std::cout << "\nThe following is 3x3 random matrix:\n";
	PrintMatrix(arr, 3, 3);

	PrintEachColSum(arr, 3, 3);

	return (0);
}