#include <iostream>
#include <iomanip>


int	RandomNumber(int From, int To)
{
	return (rand() % (To - From) + From);
}

void	FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
		for (short j = 0; j < Cols; j++)
			arr[i][j] = RandomNumber(1, 10);
}

void	PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{	
		for (short j = 0; j < Cols; j++)
		{
			printf(" %0*d ", 2, arr[i][j]);
			//std::cout << std::setw(3) << arr[i][j] << "		";
		}
		std::cout << "\n";
	}
}

void	PrintMiddleRow(int arr[3][3], short Cols, short Rows)
{
	short MiddleRow;

	MiddleRow = Rows / 2;
	for (short i = 0; i < Cols; i++)
		printf(" %0*d ", 2, arr[MiddleRow][i]);
	printf("\n");
	
}

void	PrintMiddleCol(int arr[3][3], short Rows, short Cols)
{
	short MiddleCol;

	MiddleCol = Cols / 2;
	for (short i = 0; i < Rows; i++)
		printf(" %0*d \n", 2, arr[i][MiddleCol]);
}

int main(void)
{
	//seed the random number generator, only once
	srand((unsigned)time(NULL));
	
	int arr[3][3];

	FillMatrixWithRandomNumbers(arr, 3, 3);
	std::cout << "\nMatrix1:\n";
	PrintMatrix(arr, 3, 3);

	std::cout << "\nMiddle Row:\n";
	PrintMiddleRow(arr, 3, 3);

	std::cout << "\nMiddle Col:\n";
	PrintMiddleCol(arr, 3, 3);

	return (0);
}