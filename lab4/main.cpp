#include <iostream>
#include "include/ShapeCommandHandler.h"
#include "include/ShapeController.h"

int main()
{
    try
    {
        ShapeCommandHandler shapeHandler;
        ShapeController shapeController =
        {
            std::cin,
            std::cout,
            shapeHandler
        };

        shapeController.ReadShapes();
        shapeController.ShapeMaxArea();
        shapeController.ShapeMinPerimeter();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}