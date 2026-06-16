#include <iostream>
#include <iomanip>

int RandomNumber(int From, int To)
{
	return (rand() % (To - From) + From);
}

void FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
		for (short j = 0; j < Cols; j++)
			arr[i][j] = RandomNumber(1, 10);
}

void PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			printf(" %0*d ", 2, arr[i][j]);
			// std::cout << std::setw(3) << arr[i][j] << "		";
		}
		std::cout << "\n";
	}
}
int    MaxNumberInMatrix(int arr[3][3], short Rows, short Cols)
{
    int Max;

    Max = arr[0][0];
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
           if (Max < arr[i][j])
            Max = arr[i][j];
		}
	} 
    return (Max);
}


int main(void)
{
    int arr[3][3];

    FillMatrixWithRandomNumbers(arr, 3, 3);
    std::cout << "\nThe matrix:\n";
    PrintMatrix(arr, 3, 3);

    std::cout << "\nMax number is: " << MaxNumberInMatrix(arr, 3, 3);

    return (0);
}