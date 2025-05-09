#include <iostream>
#include "include/CMyString.h"

int main()
{
    const char* testData = "Test String";
    CMyString str(testData);
    CMyString subStr = str.SubString(5, 6);
    std::cout << subStr << std::endl;
    return 0;
}