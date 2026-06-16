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

int main(void)
{
    int arr1[3][3] = {{9, 0, 0}, {0, 4, 0}, {0, 1, 9}};
    int arr2[3][3] = {{9, 5, 0}, {0, 4, 0}, {0, 8, 9}};


	std::cout << "\nMatrix1:\n";
	PrintMatrix(arr1, 3, 3);

	std::cout << "\nMatrix2:\n";
	PrintMatrix(arr2, 3, 3);


    return (0);
}