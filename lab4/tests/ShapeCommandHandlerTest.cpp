#include <gtest/gtest.h>
#include "../include/ShapeCommandHandler.h"
#include "../src/Interface/IShape.h"
#include <memory>

class MockShape : public IShape
{
    public:
        MockShape(double area, double perimeter)
            : m_area(area), m_perimeter(perimeter) {}

        double GetArea() const override { return m_area; }
        double GetPerimeter() const override { return m_perimeter; }
        std::string ToString() const override { return ""; }

    private:
        double m_area;
        double m_perimeter;
};

class ShapeCommandHandlerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        handler.ConstructShape("circle 0 0 5 ff0000 00ff00");
        handler.ConstructShape("rectangle 0 0 4 5 ff0000 00ff00");
        handler.ConstructShape("triangle 0 0 3 0 0 4 ff0000 00ff00");
    }

    ShapeCommandHandler handler;
};

TEST_F(ShapeCommandHandlerTest, ConstructShape_InvalidInput_ThrowsException)
{
    EXPECT_THROW(handler.ConstructShape("invalid shape"), std::runtime_error);
}

TEST_F(ShapeCommandHandlerTest, GetShapeWithMaxArea_ReturnsCorrectShape)
{
    auto maxAreaShape = handler.GetShapeWithMaxArea();
    ASSERT_NE(nullptr, maxAreaShape);
    EXPECT_NEAR(maxAreaShape->GetArea(), 78.5, 0.05);
}

TEST_F(ShapeCommandHandlerTest, GetShapeWithMaxArea_EmptyList_ReturnsNull)
{
    ShapeCommandHandler emptyHandler;
    EXPECT_EQ(nullptr, emptyHandler.GetShapeWithMaxArea());
}

TEST_F(ShapeCommandHandlerTest, GetShapeWithMinPerimeter_ReturnsCorrectShape)
{
    auto minPerimeterShape = handler.GetShapeWithMinPerimeter();
    ASSERT_NE(nullptr, minPerimeterShape);
    EXPECT_DOUBLE_EQ(12.0, minPerimeterShape->GetPerimeter());
}

TEST_F(ShapeCommandHandlerTest, GetShapeWithMinPerimeter_EmptyList_ReturnsNull)
{
    ShapeCommandHandler emptyHandler;
    EXPECT_EQ(nullptr, emptyHandler.GetShapeWithMinPerimeter());
}