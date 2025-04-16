#include <gtest/gtest.h>
#include "../include/CRectangle.h"

class CRectangleTest : public ::testing::Test
{
protected:
    CRectangleTest() :
            m_topLeft(3.0, 4.0),
            m_width(2.0),
            m_height(3.0),
            m_outlineColor(0xFF0000),
            m_fillColor(0x00FF00),
            m_rectangle(m_topLeft, m_width, m_height, m_outlineColor, m_fillColor)
    {}

    void SetUp() override
    {
        m_topLeft = CPoint{3.0, 4.0},
        m_width = 2,
        m_height = 3,
        m_outlineColor = 0xFF0000,
        m_fillColor = 0x00FF00,
        m_rectangle = CRectangle(m_topLeft, m_width, m_height, m_outlineColor, m_fillColor);
    }

    CPoint m_topLeft;
    double m_width;
    double m_height;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
    CRectangle m_rectangle;
};

TEST_F(CRectangleTest, GetAreaCalculatesCorrectly)
{
    double expectedArea = m_width * m_height;
    ASSERT_DOUBLE_EQ(m_rectangle.GetArea(), expectedArea);
}

TEST_F(CRectangleTest, GetPerimeterCalculatesCorrectly)
{
    double expectedPerimeter = 2 * (m_width + m_height);
    ASSERT_DOUBLE_EQ(m_rectangle.GetPerimeter(), expectedPerimeter);
}

TEST_F(CRectangleTest, GetOutlineColorReturnsCorrectValue)
{
    ASSERT_EQ(m_rectangle.GetOutlineColor(), m_outlineColor);
}

TEST_F(CRectangleTest, GetFillColorReturnsCorrectValue)
{
    ASSERT_EQ(m_rectangle.GetFillColor(), m_fillColor);
}

TEST_F(CRectangleTest, GetLeftTopReturnsCorrectValue)
{
    CPoint vertex = m_rectangle.GetLeftTop();
    ASSERT_DOUBLE_EQ(vertex.m_x, m_topLeft.m_x);
    ASSERT_DOUBLE_EQ(vertex.m_y, m_topLeft.m_y);
}

TEST_F(CRectangleTest, GetRightBottomReturnsCorrectValue)
{
    CPoint rightBottom = m_rectangle.GetRightBottom();
    ASSERT_DOUBLE_EQ(rightBottom.m_x, m_topLeft.m_x + m_width);
    ASSERT_DOUBLE_EQ(rightBottom.m_y, m_topLeft.m_y + m_height);
}

TEST_F(CRectangleTest, GetWidthReturnsCorrectValue)
{
    ASSERT_DOUBLE_EQ(m_rectangle.GetWidth(), m_width);
}

TEST_F(CRectangleTest, GetHeightReturnsCorrectValue)
{
    ASSERT_DOUBLE_EQ(m_rectangle.GetHeight(), m_height);
}

TEST_F(CRectangleTest, NotValidDataThrowsException)
{
    EXPECT_THROW(
        CRectangle(m_topLeft, -1.0, m_height, m_outlineColor, m_fillColor),
        std::invalid_argument
    );

    EXPECT_THROW(
        CRectangle(m_topLeft, 0.0, m_height, m_outlineColor, m_fillColor),
        std::invalid_argument
    );

    EXPECT_THROW(
        CRectangle(m_topLeft, m_width, -2.0, m_outlineColor, m_fillColor),
        std::invalid_argument
    );

    EXPECT_THROW(
        CRectangle(m_topLeft, m_width, 0.0, m_outlineColor, m_fillColor),
        std::invalid_argument
    );
}

TEST_F(CRectangleTest, ToStringReturnsCorrectString)
{
    std::stringstream expectedOutput;
    expectedOutput << "Rectangle: " << "\n"
    << " LeftTop: (3, 4)\n"
    << " RightBottom: (5, 7)\n"
    << " Height: 3\n"
    << " Width: 2\n"
    << " Area: 6\n"
    << " Perimeter: 10\n"
    << " Outline Color: #ff0000\n"
    << " FillColor: #00ff00\n";
    ASSERT_EQ(m_rectangle.ToString(), expectedOutput.str());
}