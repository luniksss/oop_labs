#ifndef ICANVAS_H
#define ICANVAS_H
#include "../../include/CPoint.h"
#include <vector>
#include <cstdint>

class ICanvas
{
    public:
        virtual ~ICanvas() = default;
        virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
        virtual void FillPolygon(std::vector<CPoint>, uint32_t lineColor, uint32_t fillColor) = 0;
        virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;
        virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
};

#endif //ICANVAS_H