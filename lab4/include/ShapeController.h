#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#include "../include/ShapeCommandHandler.h"

class ShapeController
{
public:
    ShapeController(std::istream& in, std::ostream& out, ShapeCommandHandler& handler)
        : m_in(in)
        , m_out(out)
        , m_shapeHandler(handler)
    {
    }

    void ReadShapes() const;
    void ShapeMaxArea() const;
    void ShapeMinPerimeter() const;
    void DrawShapes();

private:
    std::istream& m_in;
    std::ostream& m_out;
    ShapeCommandHandler& m_shapeHandler;
};

#endif //SHAPECONTROLLER_H