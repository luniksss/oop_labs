#include <SFML/Graphics.hpp>
#include "include/ShapeController.h"
#include "include/CCanvas.h"
#include <iostream>

int main()
{ sf::RenderWindow window(sf::VideoMode(800, 600), "Shapes");
    window.setFramerateLimit(60);

    ShapeCommandHandler handler(window);
    ShapeController controller(std::cin, std::cout, handler);

    try {
        controller.ReadShapes();
        controller.ShapeMaxArea();
        controller.ShapeMinPerimeter();
        controller.DrawShapes();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}