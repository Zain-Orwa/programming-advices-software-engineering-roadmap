#include <iostream>

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

short CountZeroInMatrix(int arr[3][3], short num, short Rows, short Cols)
{
    short Counter;

    Counter = 0;
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            if (arr[i][j] == num)
                Counter++;
        }
    }
    return (Counter);
}
bool    IsSparseMatrix(int arr[3][3], short Rows, short Cols )
{
   return (CountZeroInMatrix(arr, 0, Rows, Cols) >= ((Rows * Cols) + 1) / 2);     
}

int main(void)
{
    int arr[3][3] = {{9, 0, 0}, {0, 4, 0}, {0, 0, 9}};
	std::cout << "\nThe matrix:\n";
	PrintMatrix(arr, 3, 3);

    if (IsSparseMatrix(arr, 3, 3))
        std::cout << "\nYes, it's sparse matrix!\n";
    else
        std::cout << "\nNo, it's not sparse matrix\n";

    return (0);
}