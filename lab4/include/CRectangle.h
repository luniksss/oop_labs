#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <stdexcept>
#include "CPoint.h"
#include "../src/Interface/ISolidShape.h"

class CRectangle: public ISolidShape
{
public:
    CRectangle(CPoint pointStart, double width, double height, uint32_t outlineColor, uint32_t fillColor)
        : m_topLeft(pointStart)
        , m_width(width)
        , m_height(height)
        , m_outlineColor(outlineColor)
        , m_fillColor(fillColor)
    {
        if (height <= 0 || width <= 0)
        {
            throw std::invalid_argument("Invalid rectangle params");
        }
    }

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;
    double GetHeight() const;
    double GetWidth() const;
    void Draw(ICanvas& canvas) const override;

private:
    CPoint m_topLeft;
    double m_width, m_height;
    uint32_t m_outlineColor, m_fillColor;
};

#endif //RECTANGLE_H