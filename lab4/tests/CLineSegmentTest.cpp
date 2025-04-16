#include <gtest/gtest.h>
#include "../include/CLineSegment.h"

class CLineSegmentTest : public ::testing::Test
{
protected:
    CLineSegmentTest()
        : startPoint{0.0, 0.0},
          endPoint{3.0, 4.0},
          lineSegment(startPoint, endPoint, 0xFF5733)
    {}

    CPoint startPoint;
    CPoint endPoint;
    CLineSegment lineSegment;
};

TEST_F(CLineSegmentTest, GetAreaReturnsDefaultArea)
{
    EXPECT_DOUBLE_EQ(lineSegment.GetArea(), 0);
}


TEST_F(CLineSegmentTest, GetPerimeterCalculatesCorrectly)
{
    double expectedPerimeter = 5.0;
    EXPECT_DOUBLE_EQ(lineSegment.GetPerimeter(), expectedPerimeter);
}


TEST_F(CLineSegmentTest, ToStringReturnsCorrectString)
{
    std::stringstream expectedOutput;
    expectedOutput << "Line Segment:\n"
                   << "  Start Point: (0, 0)\n"
                   << "  End Point: (3, 4)\n"
                   << "  Perimeter: 5\n"
                   << "  Outline Color: #ff5733";

    EXPECT_EQ(lineSegment.ToString(), expectedOutput.str());
}

TEST_F(CLineSegmentTest, GetOutlineColorReturnsCorrectValue)
{
    EXPECT_EQ(lineSegment.GetOutlineColor(), 0xFF5733);
}

TEST_F(CLineSegmentTest, GetStartPointReturnsCorrectValue)
{
    EXPECT_EQ(lineSegment.GetStartPoint().m_x, startPoint.m_x);
    EXPECT_EQ(lineSegment.GetStartPoint().m_y, startPoint.m_y);
}

TEST_F(CLineSegmentTest, GetEndPointReturnsCorrectValue)
{
    EXPECT_EQ(lineSegment.GetEndPoint().m_x, endPoint.m_x);
    EXPECT_EQ(lineSegment.GetEndPoint().m_y, endPoint.m_y);
}