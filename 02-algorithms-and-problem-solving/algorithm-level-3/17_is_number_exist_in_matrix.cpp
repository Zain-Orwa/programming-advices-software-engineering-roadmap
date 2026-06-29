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

int ReadNumber()
{
    int Number;
    std::cout << "\nPlease Enter the number to look for in matrix? ";
    std::cin >> Number;
    return (Number);
}

int main(void)
{
    int arr[3][3] = { {77,5,12},{22,20,1},{1,0,9} };
    std::cout << "\nMatrix:\n";
    PrintMatrix(arr, 3, 3);

    int Number = ReadNumber();

    if (IsNumberInMatrix(arr, Number, 3, 3))
    std::cout << "\nYes it is there.\n";
    else
    std::cout << "\nNo: It's NOT there.\n";


    return (0);
}