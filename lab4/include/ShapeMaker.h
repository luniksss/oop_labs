#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H
#include <memory>
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "../src/Interface/IShape.h"

class ShapeMaker
{
public:
    static std::unique_ptr<IShape> CreateShape(const std::string& line);

private:
    static std::unique_ptr<CLineSegment> CreateCLineSegment(std::istringstream& iss);
    static std::unique_ptr<CRectangle> CreateCRectangle(std::istringstream& iss);
    static std::unique_ptr<CTriangle> CreateCTriangle(std::istringstream& iss);
    static std::unique_ptr<CCircle> CreateCCircle(std::istringstream& iss);
};

#endif //SHAPEMAKER_H