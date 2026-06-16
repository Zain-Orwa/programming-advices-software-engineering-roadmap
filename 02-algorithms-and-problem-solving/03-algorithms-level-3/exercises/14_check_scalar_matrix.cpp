#include <iostream>

void   CreateIdentityMatrix(int arr[3][3], short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            arr[i][j] = (i == j) ? 5 : 0;
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

bool    IsIdentityMatrix(int arr[3][3], short Rows, short Cols)
{
        for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            if (i == j && arr[i][j] != 1)
                return (true);
            else if (i != j && arr[i][j] != 0)
                return (false);
        }
    }
    return (true);
}

int main(void)
{
    //int arr[3][3];
    int arr[3][3]={{9,0,0},{0,4,0},{0,0,9}};

  //  CreateIdentityMatrix(arr, 3, 3);
    std::cout << "\nThe following is 3x3 matrix:\n";
    PrintMatrix(arr, 3, 3);

    if (IsIdentityMatrix(arr, 3, 3))
        std::cout << "\nYes, it's scalar matrix!\n";
    else
        std::cout << "\nNo, it's not scalar matrix!\n";

    return (0);
}