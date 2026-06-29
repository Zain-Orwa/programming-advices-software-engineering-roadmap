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

bool    IsPalindrome(int arr[3][3], short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols / 2; j++)
        {
            if (arr[i][j] != arr[i][Cols - 1 - j])
                return (false);
            //printf("[i]:%d, [j]:%d, arr[i][j]:%d, arr[i][Cols-1-j]:%d\n", i, j, arr[i][j], arr[i][Cols-1-j]);
        }
    }
    return (true);
}

int main(void)
{
     int arr[3][3] = {{0, 0, 1}, {2, 4, 2}, {9, 0, 9}};
    std::cout << "\nThe matrix:\n";
    PrintMatrix(arr, 3, 3);

    if (IsPalindrome(arr, 3, 3))
        std::cout << "Yes, is palindrome!\n";
    else
        std::cout << "No, it's not palindrome!\n";

    return (0);
}
