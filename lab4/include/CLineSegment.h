#ifndef CLINESEGMENT_H
#define CLINESEGMENT_H
#include "../src/Interface/IShape.h"
#include "CPoint.h"

class CLineSegment: public IShape
{
public:
    CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color)
        : m_startPoint(startPoint)
        , m_endPoint(endPoint)
        , m_lineColor(color)
    {}

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    uint32_t GetOutlineColor() const override;
    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;
    void Draw(ICanvas& canvas) const override;

private:
    CPoint m_startPoint, m_endPoint;
    uint32_t m_lineColor;

    const double DEFAULT_AREA = 0;
};

#endif //CLINESEGMENT_H