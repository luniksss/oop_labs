#ifndef CTRIANGLE_H
#define CTRIANGLE_H
#include "CPoint.h"
#include "../src/Interface/ISolidShape.h"
#include <stdexcept>

class CTriangle: public ISolidShape
{
public:
    CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
        : m_vertex1(vertex1)
        , m_vertex2(vertex2)
        , m_vertex3(vertex3)
        , m_outlineColor(outlineColor)
        , m_fillColor(fillColor)
    {
        //проверка, что это существующий треугольник по 3 сторонам
        const double sideLine1 = GetSideLength(m_vertex2, m_vertex1);
        const double sideLine2 = GetSideLength(m_vertex3, m_vertex2);
        const double sideLine3 = GetSideLength(m_vertex1, m_vertex3);

        if ((sideLine1 + sideLine2 <= sideLine3)
            || (sideLine2 + sideLine3 <= sideLine1)
            || (sideLine1 + sideLine3 <= sideLine2))
        {
            throw std::invalid_argument("Triangle is not valid");
        }
    }

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;
    void Draw(ICanvas& canvas) const override;

private:
    CPoint m_vertex1, m_vertex2, m_vertex3;
    uint32_t m_outlineColor, m_fillColor;
    static double GetSideLength(const CPoint& vertex1, const CPoint& vertex2);
};

#endif //CTRIANGLE_H