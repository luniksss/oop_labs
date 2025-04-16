#include "../include/CRectangle.h"
#include <iomanip>
#include <sstream>

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return 2 * m_width + 2 * m_height;
}

std::string CRectangle::ToString() const
{
    std::stringstream out;
    out << "Rectangle: " << "\n"
        << " LeftTop: (" << m_topLeft.m_x << ", " << m_topLeft.m_y << ")" << "\n"
        << " RightBottom: (" << GetRightBottom().m_x << ", " << GetRightBottom().m_y << ")" << "\n"
        << " Height: " << m_height << "\n"
        << " Width: " << m_width << "\n"
        << " Area: " << GetArea() << "\n"
        << " Perimeter: " << GetPerimeter() << "\n"
        << " Outline Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor << "\n"
        << " FillColor: #" << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << "\n";
    return out.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_topLeft;
}

CPoint CRectangle::GetRightBottom() const
{
    return { m_topLeft.m_x + m_width, m_topLeft.m_y + m_height };
}

double CRectangle::GetHeight() const
{
    return m_height;
}

double CRectangle::GetWidth() const
{
    return m_width;
}