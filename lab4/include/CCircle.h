#ifndef CCIRCLE_H
#define CCIRCLE_H
#include "CPoint.h"
#include "../src/Interface/ISolidShape.h"
#include <stdexcept>

//TODO чем public отличается private
class CCircle: public ISolidShape
{
public:
    CCircle()
        : m_centerPoint(0.0, 0.0)
        , m_radius(0.1)
        , m_outlineColor(0)
        , m_fillColor(0)
    {};

    CCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor)
        : m_centerPoint(center)
        , m_radius(radius)
        , m_outlineColor(lineColor)
        , m_fillColor(fillColor)
    {
        if (radius <= 0)
        {
            throw std::invalid_argument("Invalid radius");
        }
    }

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    CPoint GetCenter() const;
    double GetRadius() const;

private:
    CPoint m_centerPoint;
    double m_radius;
    uint32_t m_outlineColor, m_fillColor;
};

#endif //CCIRCLE_H