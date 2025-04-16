#include "../include/CCircle.h"
#include <sstream>
#include <cmath>
#include <iomanip>

double CCircle::GetArea() const
{
    return M_PI * (m_radius * m_radius);
}

double CCircle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
    std::stringstream out;
    out << "Circle:\n"
        << " Center Point: (" << m_centerPoint.m_x << ", " << m_centerPoint.m_y << ")\n"
        << " Radius: " << m_radius << "\n"
        << " Area: " << GetArea() << "\n"
        << " Perimeter: " << GetPerimeter() << "\n"
        << " Outline Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor << "\n"
        << " Fill Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;
    return out.str();
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_centerPoint;
}

double CCircle::GetRadius() const
{
    return m_radius;
}