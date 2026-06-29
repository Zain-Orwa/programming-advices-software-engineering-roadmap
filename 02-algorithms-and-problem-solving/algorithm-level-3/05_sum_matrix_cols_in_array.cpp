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

int	ColSum(int arr[3][3], short Rows,  short ColNumber)
{
	int	Sum = 0;
	for (short i = 0; i < Rows; i++)
	{
		Sum += arr[i][ColNumber]; 
	}
	return (Sum);
}

void	SumMatrixColsInArray(int arr[3][3],int arrSum[3], short Rows, short Cols)
{
	for (short j = 0; j < Cols; j ++)
		arrSum[j] = ColSum(arr, Rows, j);
}

void	PrintColsSumArray(int arr[3], short Rows)
{
	std::cout << "\nThe following is sum of each row in the matrix:\n";
	for (short i = 0; i < Rows; i++)
		std::cout << " Row " << i + 1 << " Sum = " << arr[i] << std::endl;
}


int main(void)
{
	srand((unsigned)time(NULL));

	int arr[3][3];
	int arrSum[3];

	FillMatrixWithRandomNumbers(arr, 3, 3);
	std::cout << "\nThe following is 3x3 random matrix:\n";
	PrintMatrix(arr, 3, 3);

	SumMatrixColsInArray(arr, arrSum, 3, 3);
	PrintColsSumArray(arrSum, 3);

	return (0);
}
