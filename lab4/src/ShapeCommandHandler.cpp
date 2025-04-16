#include "../include/ShapeCommandHandler.h"
#include "../include/ShapeMaker.h"
#include <algorithm>

void ShapeCommandHandler::ConstructShape(const std::string& line)
{
    auto shape = ShapeMaker::CreateShape(line);
    if (!shape)
    {
        throw std::runtime_error("Unknown shape");
    }
    m_shapes.push_back(std::move(shape));
}

IShape* ShapeCommandHandler::GetShapeWithMaxArea() const
{
    if (m_shapes.empty()) return nullptr;

    auto it = std::max_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b) { return a->GetArea() < b->GetArea(); });
    return it->get();
}

IShape* ShapeCommandHandler::GetShapeWithMinPerimeter() const
{
    if (m_shapes.empty()) return nullptr;

    auto it = std::min_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b) { return a->GetPerimeter() < b->GetPerimeter(); });
    return it->get();
}

const std::vector<std::unique_ptr<IShape>>& ShapeCommandHandler::GetShapes() const
{
    return m_shapes;
}

void ShapeCommandHandler::RenderShapes()
{
    CCanvas canvas(m_window);
    for (const auto& shape : m_shapes)
    {
        shape->Draw(canvas);
    }
}