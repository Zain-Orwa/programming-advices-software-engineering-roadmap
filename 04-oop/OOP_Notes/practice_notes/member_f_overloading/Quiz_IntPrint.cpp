#include <iostream>

class IntPair
{
public:
    int _IntA{};
    int _IntB{};

    void    print()
    {
        std::cout << "Pair(" << _IntA << ", " << _IntB << ")"<< std::endl;
    }

	bool	isEqual(const IntPair& other)
	{
		return ((_IntA == other._IntA) && (_IntB == other._IntB));
	}
};



int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

	return 0;

	return 0;
}