#include "../include/CLineSegment.h"
#include <sstream>
#include <valarray>
#include <iomanip>

double CLineSegment::GetArea() const
{
    return DEFAULT_AREA;
}

double CLineSegment::GetPerimeter() const
{
    double dx = m_endPoint.m_x - m_startPoint.m_x;
    double dy = m_endPoint.m_y - m_startPoint.m_y;
    return std::sqrt(dx * dx + dy * dy);
}

std::string CLineSegment::ToString() const
{
    std::stringstream out;
    out << "Line Segment:\n"
            << "  Start Point: (" << m_startPoint.m_x << ", " << m_startPoint.m_y << ")\n"
            << "  End Point: (" << m_endPoint.m_x << ", " << m_endPoint.m_y << ")\n"
            << "  Perimeter: " << GetPerimeter() << "\n"
            << "  Outline Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_lineColor;
    return out.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_lineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
    canvas.DrawLine(m_startPoint, m_endPoint, m_lineColor);
}