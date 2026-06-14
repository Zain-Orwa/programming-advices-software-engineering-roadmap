#include <iostream>

void    FillArrayWithOrderedNumbers(int arr[3][3], short Rows, short Cols)
{
    short   Counter;

    Counter = 0;
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            Counter++;
            arr[i][j] = Counter;
        }
    }
}

void    PrintMatrix(int arr[3][3], short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
            std::cout << arr[i][j] << "     ";
        std::cout << "\n";
    }
}

int main(void)
{
    int arr[3][3];

    FillArrayWithOrderedNumbers(arr, 3, 3);
    PrintMatrix(arr, 3, 3);

    return (0);
}