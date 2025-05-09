#include <iostream>
#include "include/CHttpUrl.h"

int main()
{
    std::string url;
    while (!std::cin.eof() && !std::cin.fail())
    {
        getline(std::cin, url);
        try
        {
            CHttpUrl parsedUrl(url);
            std::cout << parsedUrl;
        }
        catch (std::exception const& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}