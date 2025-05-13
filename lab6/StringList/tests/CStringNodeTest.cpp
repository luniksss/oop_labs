#include <gtest/gtest.h>
#include "../include/CStringNode.h"

TEST(CStringNodeTest, CStringNodeConstructor)
{
    std::string str = "hello world";
    CStringNode node(str);
    EXPECT_EQ(str, node.GetData());
    EXPECT_EQ(nullptr, node.GetPrev());
    EXPECT_EQ(nullptr, node.GetNext());
}