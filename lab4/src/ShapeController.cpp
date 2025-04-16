#include "../include/ShapeController.h"
#include <iostream>

void ShapeController::ReadShapes() const
{
    std::string line;
    while (std::getline(m_in, line))
    {
        if (line.empty())
        {
            break;
        }

        m_shapeHandler.ConstructShape(line);
    }
}

void ShapeController::ShapeMaxArea() const
{
    IShape* shape = m_shapeHandler.GetShapeWithMaxArea();
    if (shape != nullptr)
    {
        std::cout << "Shape with max area:\n" << shape->ToString() << std::endl;
    }
}

void ShapeController::ShapeMinPerimeter() const
{
    IShape* shape = m_shapeHandler.GetShapeWithMinPerimeter();
    if (shape != nullptr)
    {
        std::cout << "Shape with min perimeter:\n" << shape->ToString() << std::endl;
    }
}

void ShapeController::DrawShapes()
{
    m_shapeHandler.RenderShapes();
}