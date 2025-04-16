#include <gtest/gtest.h>
#include "../include/ShapeMaker.h"
#include "../src/Interface/IShape.h"
#include <memory>
#include <valarray>

class ShapeMakerTest : public ::testing::Test
{
    protected:
        void SetUp() override {}
};

TEST_F(ShapeMakerTest, CreateLineSegmentValidInput)
{
    std::string input = "line 1.0 2.0 3.0 4.0 ff0000";
    auto shape = ShapeMaker::CreateShape(input);
    
    ASSERT_NE(shape, nullptr);
    double expected = sqrt(pow(3.0 - 1.0, 2) + pow(4.0 - 2.0, 2));
    EXPECT_DOUBLE_EQ(shape->GetPerimeter(), expected);
}

TEST_F(ShapeMakerTest, CreateLineSegmentInvalidCoordinates)
{
    std::string input = "line 1.0 abc 3.0 4.0 ff0000";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateLineSegmentMissingColor)
{
    std::string input = "line 1.0 2.0 3.0 4.0";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateCircleValidInput)
{
    std::string input = "circle 0.0 0.0 5.0 ff0000 00ff00";
    auto shape = ShapeMaker::CreateShape(input);
    
    ASSERT_NE(shape, nullptr);
    EXPECT_DOUBLE_EQ(shape->GetArea(), 78.53981633974483);
}

TEST_F(ShapeMakerTest, CreateCircleNegativeRadius)
{
    std::string input = "circle 0.0 0.0 -5.0 ff0000 00ff00";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateCircleInvalidParams)
{
    std::string input = "circle 0.0 0.0 asv ff0000 00ff00";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateCircleMissingColors)
{
    std::string input = "circle 0.0 0.0 5.0";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateTriangleValidInput)
{
    std::string input = "triangle 0.0 0.0 3.0 0.0 0.0 4.0 ff0000 00ff00";
    auto shape = ShapeMaker::CreateShape(input);
    
    ASSERT_NE(shape, nullptr);
    EXPECT_DOUBLE_EQ(shape->GetArea(), 6.0);
}

TEST_F(ShapeMakerTest, CreateTriangleDegenerateTriangle)
{
    std::string input = "triangle 0.0 0.0 3.0 0.0 4.0 ff0000 00ff00";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateTriangleInvalidParams)
{
    std::string input = "triangle 0.0 4.0 ff0000 00ff00";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateTriangleMissingColors)
{
    std::string input = "triangle 0.0 0.0 0.0 0.0 0.0 0.0";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateRectangleValidInput)
{
    std::string input = "rectangle 0.0 0.0 4.0 5.0 ff0000 00ff00";
    auto shape = ShapeMaker::CreateShape(input);
    
    ASSERT_NE(shape, nullptr);
    EXPECT_DOUBLE_EQ(shape->GetArea(), 20.0);
}

TEST_F(ShapeMakerTest, CreateRectangleInvalidParams)
{
    std::string input = "rectangle 5.0 ff0000 00ff00";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateRectangleMissingColors)
{
    std::string input = "rectangle 0.0 0.0 4.0 5.0";
    EXPECT_THROW(ShapeMaker::CreateShape(input), std::invalid_argument);
}

TEST_F(ShapeMakerTest, CreateShapeUnknownShape)
{
    std::string input = "hexagon 0.0 0.0 1.0 ff0000";
    auto shape = ShapeMaker::CreateShape(input);
    
    EXPECT_EQ(shape, nullptr);
}

TEST_F(ShapeMakerTest, CreateShapeEmptyInput)
{
    std::string input = "";
    auto shape = ShapeMaker::CreateShape(input);
    
    EXPECT_EQ(shape, nullptr);
}