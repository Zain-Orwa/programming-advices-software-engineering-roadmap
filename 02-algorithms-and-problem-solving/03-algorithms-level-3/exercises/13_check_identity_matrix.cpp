#include <iostream>

void   CreateIdentityMatrix(int arr[3][3], short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            arr[i][j] = (i == j) ? 1 : 0;
        }
    }
}
void PrintMatrix(int arr[3][3], short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            printf(" %0*d ", 2, arr[i][j]);
        }
        std::cout << "\n";
    }
}

int main(void)
{
    int arr[3][3];

    CreateIdentityMatrix(arr, 3, 3);
    std::cout << "\nThe following is 3x3 matrix:\n";
    PrintMatrix(arr, 3, 3);

    return (0);
}