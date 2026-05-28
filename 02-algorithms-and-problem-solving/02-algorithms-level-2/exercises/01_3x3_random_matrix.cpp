#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int	RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1) + From);
}
/*
void	FillMatirxWithRandomNumbers(int arr[3][3], short rows, short cols)	
{

}
*/
int main(void)
{
	srand(time(0));

	cout << RandomNumber(1, 7) << endl;
	cout << RandomNumber(1, 7) << endl;
	cout << RandomNumber(1, 7) << endl;

	return (0);
}
