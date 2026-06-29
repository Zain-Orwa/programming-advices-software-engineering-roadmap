#include <iostream>

void PrintMatrix(int arr[3][3], short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            printf(" %d ", arr[i][j]);
            // std::cout << std::setw(3) << arr[i][j] << "		";
        }
        std::cout << "\n";
    }
}

bool IsNumberInMatrix(int arr[3][3], short num, short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            if (arr[i][j] == num)
                return (true);
        }
    }
    return (false);
}
void    PrintIntersectedNumbers(int arr1[3][3], int arr2[3][3], short Rows, short Cols)
{
    short Number;

    for (short i = 0; i < Rows; i++)
    { 
        for (short j = 0; j < Cols; j++)
        {
            Number = arr1[i][j];
            if (IsNumberInMatrix(arr2, Number, Rows, Cols))
                std::cout << Number << "    ";
        }
    }
}

int main(void)
{
    int arr1[3][3] = { {77,5,12},{22,20,1},{1,0,9} };
    int arr2[3][3] = { {5,80,90},{22,77,1},{10,8,33} };


	std::cout << "\nMatrix1:\n";
	PrintMatrix(arr1, 3, 3);

	std::cout << "\nMatrix2:\n";
	PrintMatrix(arr2, 3, 3);

    std::cout << "\nIntersected numbers are:\n";
    PrintIntersectedNumbers(arr1, arr2, 3, 3);

    return (0);
}