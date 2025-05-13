#include <gtest/gtest.h>
#include "../include/CStringConstIterator.h"
#include "../include/CStringNode.h"

class CStringConstIteratorTest : public ::testing::Test
{
protected:
    CStringConstIteratorTest()
    : node1("data1"),
      node2("data2")
    {}


    void SetUp() override
    {
        node1.SetNext(&node2);
        node2.SetPrev(&node1);
    }

    CStringNode node1;
    CStringNode node2;
};

TEST_F(CStringConstIteratorTest, ConstructFromConstNode)
{
    const CStringNode* cnode = &node1;
    CStringConstIterator it(cnode);
    EXPECT_EQ(it.GetNode(), cnode);
}

TEST_F(CStringConstIteratorTest, ConstructFromNonConstIterator)
{
    CStringIterator base_it(&node1);
    CStringConstIterator it(base_it);
    EXPECT_EQ(it.GetNode(), &node1);
}

TEST_F(CStringConstIteratorTest, DereferenceOperator)
{
    CStringConstIterator it(&node1);
    EXPECT_EQ(*it, "data1");
    static_assert(std::is_same_v<decltype(*it), const std::string&>);
}

TEST_F(CStringConstIteratorTest, ArrowOperator)
{
    CStringConstIterator it(&node1);
    EXPECT_EQ(it->size(), 5);
    static_assert(std::is_same_v<decltype(it.operator->()), const std::string*>);
}

TEST_F(CStringConstIteratorTest, PreIncrement)
{
    CStringConstIterator it(&node1);
    ++it;
    EXPECT_EQ(it.GetNode(), &node2);
}

TEST_F(CStringConstIteratorTest, PostIncrement)
{
    CStringConstIterator it(&node1);
    auto old = it++;
    EXPECT_EQ(old.GetNode(), &node1);
    EXPECT_EQ(it.GetNode(), &node2);
}

TEST_F(CStringConstIteratorTest, PreDecrement)
{
    CStringConstIterator it(&node2);
    --it;
    EXPECT_EQ(it.GetNode(), &node1);
}

TEST_F(CStringConstIteratorTest, PostDecrement)
{
    CStringConstIterator it(&node2);
    auto old = it--;
    EXPECT_EQ(old.GetNode(), &node2);
    EXPECT_EQ(it.GetNode(), &node1);
}

TEST_F(CStringConstIteratorTest, Equality)
{
    CStringConstIterator it1(&node1);
    CStringConstIterator it2(&node1);
    CStringConstIterator it3(&node2);

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 == it3);
}

TEST_F(CStringConstIteratorTest, Inequality)
{
    CStringConstIterator it1(&node1);
    CStringConstIterator it2(&node2);

    EXPECT_TRUE(it1 != it2);
}

TEST_F(CStringConstIteratorTest, CrossTypeComparison)
{
    CStringIterator base_it(&node1);
    CStringConstIterator const_it(&node1);

    EXPECT_TRUE(base_it == const_it);
    EXPECT_FALSE(base_it != const_it);
}

TEST(CStringConstIteratorDeathTest, InvalidOperations)
{
    CStringConstIterator it(nullptr);
    EXPECT_THROW(++it, std::logic_error);
    EXPECT_THROW(it++, std::logic_error);
    EXPECT_THROW(--it, std::logic_error);
    EXPECT_THROW(it--, std::logic_error);
}