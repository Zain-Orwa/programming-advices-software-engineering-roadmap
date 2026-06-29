#include <iostream>

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
short ReadNumber(void)
{
    short num;

    num = 0;
    std::cout << "Enter a number to count in matrix: ";
    std::cin >> num;
    return (num);
}
short CountNumberInMatrix(int arr[3][3], short Rows, short Cols, int num)
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

int main(void)
{
    //seed the random number generator, only once
	srand((unsigned)time(NULL));
	
	int arr[3][3];
    short num = 0;
    short Count = 0;

	FillMatrixWithRandomNumbers(arr, 3, 3);
	std::cout << "\n The following is a 3x3 random matrix:\n";
	PrintMatrix(arr, 3, 3);

    num = ReadNumber();
    Count = CountNumberInMatrix(arr, 3, 3, num); 

    std::cout << "Number [" << num << "] count in matrix: " << Count <<
    std::endl; 

    return (0);
}