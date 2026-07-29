#include <iostream>

struct Date
{
    int Day{};
    int Month{};
    int Year{};
};

void    PrintDate(const Date& date)
{
    std::cout << date.Day << " / " << date.Month << " / " << date.Year << std::endl;
}

int main(void)
{
    Date date{ 4, 10, 21};

    PrintDate(date);

    return (0);
}