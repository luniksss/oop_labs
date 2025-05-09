#include <gtest/gtest.h>
#include "../include/CMyString.h"

TEST(CMyStringTest, DefaultConstructor)
{
    CMyString str;
    EXPECT_EQ(0, str.GetLength());
    EXPECT_STREQ("", str.GetStringData());
    EXPECT_EQ(1, str.GetCapacity());
}

TEST(CMyStringTest, CStringConstructor)
{
    const char* testStr = "Hello";
    CMyString str(testStr);
    EXPECT_EQ(5, str.GetLength());
    EXPECT_STREQ("Hello", str.GetStringData());
    EXPECT_EQ(6, str.GetCapacity());
}

TEST(CMyStringTest, CStringWithLengthConstructor)
{
    const char* testStr = "Hello World";
    CMyString str(testStr, 5);
    EXPECT_EQ(5, str.GetLength());
    EXPECT_STREQ("Hello", str.GetStringData());
    EXPECT_EQ(6, str.GetCapacity());
}

TEST(CMyStringTest, CopyConstructor)
{
    CMyString original("Test");
    CMyString copy(original);
    EXPECT_EQ(4, copy.GetLength());
    EXPECT_STREQ("Test", copy.GetStringData());
    EXPECT_EQ(5, copy.GetCapacity());
}

TEST(CMyStringTest, MoveConstructor)
{
    CMyString original("Test");
    CMyString moved(std::move(original));
    EXPECT_EQ(4, moved.GetLength());
    EXPECT_STREQ("Test", moved.GetStringData());
    EXPECT_EQ(5, moved.GetCapacity());
    EXPECT_EQ(0, original.GetLength());
    EXPECT_STREQ("", original.GetStringData());
    EXPECT_EQ(1, original.GetCapacity());
}

TEST(CMyStringTest, STLStringConstructor)
{
    std::string stlStr = "STL String";
    CMyString str(stlStr);
    EXPECT_EQ(stlStr.length(), str.GetLength());
    EXPECT_STREQ(stlStr.c_str(), str.GetStringData());
}

TEST(CMyStringTest, AssignmentOperator)
{
    CMyString str1("First");
    CMyString str2("Second");
    str1 = str2;
    EXPECT_EQ(6, str1.GetLength());
    EXPECT_STREQ("Second", str1.GetStringData());
}

TEST(CMyStringTest, MoveAssignmentOperator)
{
    CMyString str1("First");
    CMyString str2("Second");
    str1 = std::move(str2);
    EXPECT_EQ(6, str1.GetLength());
    EXPECT_STREQ("Second", str1.GetStringData());
    EXPECT_EQ(0, str2.GetLength());
}

TEST(CMyStringTest, SubString)
{
    CMyString str("Hello World");
    CMyString sub = str.SubString(6, 5);
    EXPECT_EQ(5, sub.GetLength());
    EXPECT_STREQ("World", sub.GetStringData());
}

TEST(CMyStringTest, SubStringEdgeCases)
{
    CMyString str("Test");
    EXPECT_THROW(str.SubString(5, 1), std::out_of_range);
    
    CMyString fullSub = str.SubString(0);
    EXPECT_STREQ("Test", fullSub.GetStringData());
}

TEST(CMyStringTest, Clear)
{
    CMyString str("Text");
    str.Clear();
    EXPECT_EQ(0, str.GetLength());
    EXPECT_STREQ("", str.GetStringData());
    EXPECT_EQ(1, str.GetCapacity());
}

TEST(CMyStringTest, OperatorPlusSTLStringAndCMyString)
{
    std::string stlStr = "Hello";
    CMyString myStr(" World");
    CMyString result = stlStr + myStr;
    EXPECT_STREQ("Hello World", result.GetStringData());
    EXPECT_EQ(11, result.GetLength());
}

TEST(CMyStringTest, OperatorPlusEmptySTLStringAndCMyString)
{
    std::string stlStr;
    CMyString myStr("Test");
    CMyString result = stlStr + myStr;
    EXPECT_STREQ("Test", result.GetStringData());
    EXPECT_EQ(4, result.GetLength());
}

TEST(CMyStringTest, OperatorPlusSTLStringAndEmptyCMyString)
{
    std::string stlStr = "Hello";
    CMyString myStr;
    CMyString result = stlStr + myStr;
    EXPECT_STREQ("Hello", result.GetStringData());
    EXPECT_EQ(5, result.GetLength());
}

TEST(CMyStringTest, OperatorPlusBothEmptySTLStringAndCMyString)
{
    std::string stlStr;
    CMyString myStr;
    CMyString result = stlStr + myStr;
    EXPECT_STREQ("", result.GetStringData());
    EXPECT_EQ(0, result.GetLength());
}

TEST(CMyStringTest, OperatorPlusCStringAndCMyString)
{
    const char* cstr = "Hello";
    CMyString myStr(" World");
    CMyString result = cstr + myStr;
    EXPECT_STREQ("Hello World", result.GetStringData());
    EXPECT_EQ(11, result.GetLength());
}

TEST(CMyStringTest, OperatorPlusEmptyCStringAndCMyString)
{
    const char* cstr = "";
    CMyString myStr("Test");
    CMyString result = cstr + myStr;
    EXPECT_STREQ("Test", result.GetStringData());
    EXPECT_EQ(4, result.GetLength());
}

TEST(CMyStringTest, OperatorPlusCStringAndEmptyCMyString)
{
    const char* cstr = "Hello";
    CMyString myStr;
    CMyString result = cstr + myStr;
    EXPECT_STREQ("Hello", result.GetStringData());
    EXPECT_EQ(5, result.GetLength());
}

TEST(CMyStringTest, OperatorPlusNullCStringAndCMyString)
{
    const char* cstr = nullptr;
    CMyString myStr("Test");
    EXPECT_THROW(cstr + myStr, std::invalid_argument);
}

TEST(CMyStringTest, OperatorPlusEmptyCStringAndEmptyCMyString)
{
    const char* cstr = "";
    CMyString myStr;
    CMyString result = cstr + myStr;
    EXPECT_STREQ("", result.GetStringData());
    EXPECT_EQ(0, result.GetLength());
}

TEST(CMyStringTest, ConcatenationOperator)
{
    CMyString str1("Hello");
    CMyString str2(" World");
    CMyString result = str1 + str2;
    EXPECT_EQ(11, result.GetLength());
    EXPECT_STREQ("Hello World", result.GetStringData());
}

TEST(CMyStringTest, ConcatenationWithSTLString)
{
    CMyString str("Hello");
    std::string stlStr(" World");
    CMyString result = str + stlStr;
    EXPECT_STREQ("Hello World", result.GetStringData());
}

TEST(CMyStringTest, ConcatenationWithCString)
{
    CMyString str("Hello");
    CMyString result = str + " World";
    EXPECT_STREQ("Hello World", result.GetStringData());
}

TEST(CMyStringTest, PlusEqualOperator)
{
    CMyString str("Hello");
    str += " World";
    EXPECT_STREQ("Hello World", str.GetStringData());
}

TEST(CMyStringTest, ComparisonOperators)
{
    CMyString str1("Apple");
    CMyString str2("Banana");
    CMyString str3("Apple");
    
    EXPECT_TRUE(str1 == str3);
    EXPECT_TRUE(str1 != str2);
    EXPECT_TRUE(str1 < str2);
    EXPECT_TRUE(str2 > str1);
    EXPECT_TRUE(str1 <= str3);
    EXPECT_TRUE(str1 >= str3);
}

TEST(CMyStringTest, ThreeWayComparison)
{
    CMyString str1("Apple");
    CMyString str2("Banana");
    CMyString str3("Apple");
    
    EXPECT_EQ(std::strong_ordering::equal, str1 <=> str3);
    EXPECT_EQ(std::strong_ordering::less, str1 <=> str2);
    EXPECT_EQ(std::strong_ordering::greater, str2 <=> str1);
}

TEST(CMyStringTest, IndexOperator)
{
    CMyString str("Test");
    EXPECT_EQ('T', str[0]);
    EXPECT_EQ('e', str[1]);
    EXPECT_EQ('s', str[2]);
    EXPECT_EQ('t', str[3]);
    
    str[0] = 't';
    EXPECT_EQ('t', str[0]);
}

TEST(CMyStringTest, ConstIndexOperator)
{
    const CMyString str("Test");
    EXPECT_EQ('T', str[0]);
    EXPECT_EQ('e', str[1]);
    EXPECT_EQ('s', str[2]);
    EXPECT_EQ('t', str[3]);
}

TEST(CMyStringTest, IndexOperatorOutOfRange)
{
    CMyString str("Test");
    EXPECT_THROW(str[4], std::out_of_range);
    const CMyString constStr("Test");
    EXPECT_THROW(constStr[4], std::out_of_range);
}

TEST(CMyStringTest, StreamOutput)
{
    CMyString str("Hello");
    std::ostringstream oss;
    oss << str;
    EXPECT_EQ("Hello", oss.str());
}

TEST(CMyStringTest, StreamInput)
{
    CMyString str;
    std::istringstream iss("Input");
    iss >> str;
    EXPECT_STREQ("Input", str.GetStringData());
}

TEST(CMyStringTest, EmptyStringOperations)
{
    CMyString empty1;
    CMyString empty2;
    CMyString nonEmpty("Text");
    
    EXPECT_TRUE(empty1 == empty2);
    EXPECT_FALSE(empty1 != empty2);
    EXPECT_EQ(empty1 + empty2, empty1);
    EXPECT_EQ(empty1 + nonEmpty, nonEmpty);
    EXPECT_EQ(nonEmpty + empty1, nonEmpty);
}

TEST(CMyStringTest, SelfAssignment)
{
    CMyString str("Test");
    str = str;
    EXPECT_STREQ("Test", str.GetStringData());
    
    str = std::move(str);
    EXPECT_STREQ("Test", str.GetStringData());
}

TEST(CMyStringTest, NullPointerInConstructor)
{
    EXPECT_THROW(CMyString str(nullptr), std::invalid_argument);
    EXPECT_THROW(CMyString str(nullptr, 5), std::invalid_argument);
}