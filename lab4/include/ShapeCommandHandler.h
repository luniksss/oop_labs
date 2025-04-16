#pragma once
#include <memory>
#include <vector>
#include "CCanvas.h"
#include "../src/Interface/IShape.h"

class ShapeCommandHandler
{
public:
    explicit ShapeCommandHandler(sf::RenderWindow& window)
        : m_window(window) {}

    void ConstructShape(const std::string& line);
    IShape* GetShapeWithMaxArea() const;
    IShape* GetShapeWithMinPerimeter() const;
    const std::vector<std::unique_ptr<IShape>>& GetShapes() const;
    void RenderShapes();

private:
    const int WIDTH_WINDOW = 1280;
    const int HEIGHT_WINDOW = 720;
    const std::string STANDARD_WINDOW_NAME = "Window";
    std::vector<std::unique_ptr<IShape>> m_shapes;
    sf::RenderWindow& m_window;
};