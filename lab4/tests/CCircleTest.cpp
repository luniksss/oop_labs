#include <gtest/gtest.h>
#include "../include/CCircle.h"
#include <cmath>

class CCircleTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_centerPoint = CPoint{5.0, 5.0};
        m_radius = 10.0;
        m_outlineColor = 0xFF5733;
        m_fillColor = 0x33FF57;
        m_circle = CCircle(m_centerPoint, m_radius, m_outlineColor, m_fillColor);
    }

    CPoint m_centerPoint;
    double m_radius;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
    CCircle m_circle;
};

TEST_F(CCircleTest, GetAreaCalculatesCorrectly)
{
    double expectedArea = M_PI * (m_radius * m_radius);
    EXPECT_DOUBLE_EQ(m_circle.GetArea(), expectedArea);
}

TEST_F(CCircleTest, GetPerimeterCalculatesCorrectly)
{
    double expectedPerimeter = 2 * M_PI * m_radius;
    EXPECT_DOUBLE_EQ(m_circle.GetPerimeter(), expectedPerimeter);
}

TEST_F(CCircleTest, ToStringReturnsCorrectString)
{
    std::stringstream expectedOutput;
    expectedOutput << "Circle:\n"
                   << " Center Point: (" << m_centerPoint.m_x << ", " << m_centerPoint.m_y << ")\n"
                   << " Radius: " << m_radius << "\n"
                   << " Area: " << M_PI * (m_radius * m_radius) << "\n"
                   << " Perimeter: " << 2 * M_PI * m_radius << "\n"
                   << " Outline Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor << "\n"
                   << " Fill Color: #" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;

    EXPECT_EQ(m_circle.ToString(), expectedOutput.str());
}

TEST_F(CCircleTest, GetOutlineColorReturnsCorrectValue)
{
    EXPECT_EQ(m_circle.GetOutlineColor(), m_outlineColor);
}

TEST_F(CCircleTest, GetFillColorReturnsCorrectValue)
{
    EXPECT_EQ(m_circle.GetFillColor(), m_fillColor);
}

// Тест метода GetCenter
TEST_F(CCircleTest, GetCenterReturnsCorrectValue) {
    EXPECT_EQ(m_circle.GetCenter().m_x, m_centerPoint.m_x);
    EXPECT_EQ(m_circle.GetCenter().m_y, m_centerPoint.m_y);
}

// Тест метода GetRadius
TEST_F(CCircleTest, GetRadiusReturnsCorrectValue) {
    EXPECT_DOUBLE_EQ(m_circle.GetRadius(), m_radius);
}