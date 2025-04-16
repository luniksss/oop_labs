#include "../include/ShapeMaker.h"
#include "Interface/IShape.h"
#include <memory>
#include <sstream>

std::shared_ptr<IShape> ShapeMaker::CreateShape(const std::string& shapeDesc)
{
    std::istringstream iss(shapeDesc);
    std::string shapeName;
    iss >> shapeName;

    if (shapeName == "line")
    {
        return CreateCLineSegment(iss);
    }
    if (shapeName == "circle")
    {
        return CreateCCircle(iss);
    }
    if (shapeName == "triangle")
    {
        return CreateCTriangle(iss);
    }
    if (shapeName == "rectangle")
    {
        return CreateCRectangle(iss);
    }

    return nullptr;
}

std::shared_ptr<CLineSegment> ShapeMaker::CreateCLineSegment(std::istringstream& iss)
{
    double startX, startY, endX, endY;

    if (!(iss >> startX >> endX >> startY >> endY))
    {
        throw std::invalid_argument("Invalid line segment coordinates");
    }
    CPoint startPoint = { startX, endX };
    CPoint endPoint = { startY, endY };

    uint32_t outlineColor;
    if (!(iss >> std::hex >> outlineColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

std::shared_ptr<CRectangle> ShapeMaker::CreateCRectangle(std::istringstream& iss)
{
    double leftTopX, leftTopY, height, width;

    if (!(iss >> leftTopX >> leftTopY >> height >> width))
    {
        throw std::invalid_argument("Invalid rectangle coordinates");
    }
    CPoint leftTopPoint = CPoint(leftTopX, leftTopY);

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CRectangle>(leftTopPoint, height, width, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> ShapeMaker::CreateCTriangle(std::istringstream& iss)
{
    double vertex1X, vertex1Y, vertex2X, vertex2Y, vertex3X, vertex3Y;

    if (!(iss >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y))
    {
        throw std::invalid_argument("Invalid number of triangle coordinates");
    }

    CPoint vertex1(vertex1X, vertex1Y);
    CPoint vertex2 = CPoint(vertex2X, vertex2Y);
    CPoint vertex3 = CPoint(vertex3X, vertex3Y);

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

std::shared_ptr<CCircle> ShapeMaker::CreateCCircle(std::istringstream& iss)
{
    double centerX, centerY, radius;

    if (!(iss >> centerX >> centerY >> radius))
    {
        throw std::invalid_argument("Invalid circle parameters");
    }
    CPoint centerPoint = { centerX, centerY };

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CCircle>(centerPoint, radius, outlineColor, fillColor);
}