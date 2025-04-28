#include <iostream>
#include "include/CDate.h"

int main()
{
    std::cout << "Hello World!\n";
    CDate date1(15, Month::JUNE, 2023);
    CDate date2(20, Month::MAY, 2023);

    if (date1 > date2)
        {
        std::cout << "Date 1 is later than Date 2" << std::endl;
    }

    CDate date4 = date1 + 10;
    std::cout << "Date 1 + 10 days: " << date4 << std::endl;

    int diff = date1 - date2;
    std::cout << "Difference between dates: " << diff << " days" << std::endl;
}