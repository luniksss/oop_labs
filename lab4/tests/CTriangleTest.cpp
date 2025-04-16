#include <gtest/gtest.h>
#include "../include/CTriangle.h"

class CTriangleTest : public ::testing::Test
{
protected:
    CTriangleTest() :
        m_vertex1(0.0, 0.0),
        m_vertex2(0.0, 3.0),
        m_vertex3(4.0, 0.0),
        m_outlineColor(0),
        m_fillColor(0),
        m_triangle(m_vertex1, m_vertex2, m_vertex3, m_outlineColor, m_fillColor)
    {}

    void SetUp() override {
        m_vertex1 = CPoint{0.0, 0.0};
        m_vertex2 = CPoint{3.0, 0.0};
        m_vertex3 = CPoint{0.0, 4.0};
        m_outlineColor = 0xFF0000;
        m_fillColor = 0x00FF00;
        m_triangle = CTriangle(m_vertex1, m_vertex2, m_vertex3, m_outlineColor, m_fillColor);
    }

    CPoint m_vertex1;
    CPoint m_vertex2;
    CPoint m_vertex3;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
    CTriangle m_triangle;
};

TEST_F(CTriangleTest, GetAreaCalculatesCorrectly)
{
    double expectedArea = 6.0; // Area = 0.5 * base * height = 0.5 * 3 * 4 = 6
    ASSERT_DOUBLE_EQ(m_triangle.GetArea(), expectedArea);
}

TEST_F(CTriangleTest, GetPerimeterCalculatesCorrectly)
{
    double expectedPerimeter = 3.0 + 4.0 + 5.0; // Sides: 3, 4, 5 (Pythagorean triple)
    ASSERT_DOUBLE_EQ(m_triangle.GetPerimeter(), expectedPerimeter);
}

TEST_F(CTriangleTest, GetOutlineColorReturnsCorrectValue) {
    ASSERT_EQ(m_triangle.GetOutlineColor(), 0xFF0000);
}

TEST_F(CTriangleTest, GetFillColorReturnsCorrectValue) {
    ASSERT_EQ(m_triangle.GetFillColor(), 0x00FF00);
}

TEST_F(CTriangleTest, GetVertex1ReturnsCorrectValue) {
    CPoint vertex = m_triangle.GetVertex1();
    ASSERT_DOUBLE_EQ(vertex.m_x, 0.0);
    ASSERT_DOUBLE_EQ(vertex.m_y, 0.0);
}

TEST_F(CTriangleTest, GetVertex2ReturnsCorrectValue) {
    CPoint vertex = m_triangle.GetVertex2();
    ASSERT_DOUBLE_EQ(vertex.m_x, 3.0);
    ASSERT_DOUBLE_EQ(vertex.m_y, 0.0);
}

TEST_F(CTriangleTest, GetVertex3ReturnsCorrectValue) {
    CPoint vertex = m_triangle.GetVertex3();
    ASSERT_DOUBLE_EQ(vertex.m_x, 0.0);
    ASSERT_DOUBLE_EQ(vertex.m_y, 4.0);
}

TEST_F(CTriangleTest, ToStringReturnsCorrectString) {
    std::stringstream expectedOutput;
    expectedOutput << "Triangle: " << "\n"
                   << " First Vertex: (0, 0)\n"
                   << " Second Vertex: (3, 0)\n"
                   << " Third Vertex: (0, 4)\n"
                   << " Area: 6\n"
                   << " Perimeter: 12\n"
                   << " Outline Color: #ff0000\n"
                   << " Fill Color: #00ff00\n";
    ASSERT_EQ(m_triangle.ToString(), expectedOutput.str());
}