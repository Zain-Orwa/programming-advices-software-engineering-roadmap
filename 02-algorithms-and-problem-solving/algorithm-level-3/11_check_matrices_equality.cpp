#include <iostream>
#include <iomanip>

int RandomNumber(int From, int To)
{
    return (rand() % (To - From + 1) + From);
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

int SumMatrix(int arr[3][3], short Rows, short Cols)
{
    int sum;

    sum = 0;
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            sum += arr[i][j];
        }
    }
    return (sum);
}
bool    AreEqualMatrices(int arr1[3][3], int arr2[3][3], short Rows, short Cols)
{
    return  (SumMatrix(arr1,Rows,Cols) == SumMatrix(arr2,Rows,Cols));
}


int main(void)
{
    // seed the random number generator, only once
    srand((unsigned)time(NULL));

    int arr1[3][3];
    int arr2[3][3];

    FillMatrixWithRandomNumbers(arr1, 3, 3);
    std::cout << "\nMatrix1:\n";
    PrintMatrix(arr1, 3, 3);

    FillMatrixWithRandomNumbers(arr2, 3, 3);
    std::cout << "\nMatrix2:\n";
    PrintMatrix(arr2, 3, 3);

    if (AreEqualMatrices(arr1, arr2, 3, 3))
        std::cout << "\nYes, matrices are equal!\n";
    else
        std::cout << "\nNo, matrices are not equal!\n";

    return (0);
}