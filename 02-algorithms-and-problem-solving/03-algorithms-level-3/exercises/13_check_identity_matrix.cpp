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

bool    IsIdentityMatrix(int arr[3][3], short Rows, short Cols)
{
        for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            if (i == j && arr[i][j] != 1)
                return (false);
            else if (i != j && arr[i][j] != 0)
                return (false);
        }
    }
    return (true);
}

int main(void)
{
    //int arr[3][3];
    int arr[3][3]={{1,2,3},{4,5,6},{7,8,9}};

   // CreateIdentityMatrix(arr, 3, 3);
    std::cout << "\nThe following is 3x3 matrix:\n";
    PrintMatrix(arr, 3, 3);

    if (IsIdentityMatrix(arr, 3, 3))
        std::cout << "\nYes, matrix is identity!\n";
    else
        std::cout << "\nNo, matrix is not identity!\n";

    return (0);
}