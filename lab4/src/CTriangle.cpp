#include "../include/CTriangle.h"
#include <valarray>
#include <sstream>
#include <iomanip>

double CTriangle::GetArea() const
{
    return 0.5 * std::abs(
            (m_vertex1.m_x * (m_vertex2.m_y - m_vertex3.m_y) +
             m_vertex2.m_x * (m_vertex3.m_y - m_vertex1.m_y) +
             m_vertex3.m_x * (m_vertex1.m_y - m_vertex2.m_y))
        );
}

double CTriangle::GetPerimeter() const
{
    const double a = GetSideLength(m_vertex2, m_vertex1);
    const double b = GetSideLength(m_vertex3, m_vertex2);
    const double c = GetSideLength(m_vertex1, m_vertex3);
    return a + b + c;
}

std::string CTriangle::ToString() const
{
    std::stringstream out;
    out << "Triangle: " << "\n"
        << " First Vertex: (" << m_vertex1.m_x << ", " << m_vertex1.m_y << ")\n"
        << " Second Vertex: (" << m_vertex2.m_x << ", " << m_vertex2.m_y << ")\n"
        << " Third Vertex: (" << m_vertex3.m_x << ", " << m_vertex3.m_y << ")\n"
        << " Area: " << GetArea() << "\n"
        << " Perimeter: " << GetPerimeter() << "\n"
        << " Outline Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor << "\n"
        << " Fill Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor << "\n";
    return out.str();;
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
    return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
    return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
    return m_vertex3;
}

double CTriangle::GetSideLength(const CPoint& vertex1, const CPoint& vertex2)
{
    return std::sqrt(std::pow(vertex1.m_x - vertex2.m_x, 2) + std::pow(vertex1.m_y - vertex2.m_y, 2));
}

void CTriangle::Draw(ICanvas& canvas) const
{
    //TODO доделать рисовку
}