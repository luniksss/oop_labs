#include "gtest/gtest.h"
#include "../include/CDate.h"

TEST(CDateTest, ConstructorValidation)
{
    EXPECT_NO_THROW(CDate(1, Month::JANUARY, 1970));
    EXPECT_NO_THROW(CDate(31, Month::DECEMBER, 9999));
    EXPECT_THROW(CDate(0, Month::JANUARY, 1970), std::invalid_argument);
    EXPECT_THROW(CDate(32, Month::JANUARY, 1970), std::invalid_argument);
    EXPECT_THROW(CDate(29, Month::FEBRUARY, 2023), std::invalid_argument);
    EXPECT_NO_THROW(CDate(29, Month::FEBRUARY, 2024));
    EXPECT_THROW(CDate(1, static_cast<Month>(0), 1970), std::invalid_argument);
    EXPECT_THROW(CDate(1, static_cast<Month>(13), 1970), std::invalid_argument);
    EXPECT_THROW(CDate(1, Month::JANUARY, 1969), std::invalid_argument);
    EXPECT_THROW(CDate(1, Month::JANUARY, 10000), std::invalid_argument);
}

TEST(CDateTest, TimestampConstructor)
{
    EXPECT_NO_THROW(CDate(0));
    EXPECT_NO_THROW(CDate(2932896));  // 31.12.9999
    EXPECT_THROW(CDate(2932897), std::invalid_argument);  // 1.1.10000
}

TEST(CDateTest, Getters)
{
    CDate date(15, Month::JUNE, 2023);
    EXPECT_EQ(date.GetDay(), 15);
    EXPECT_EQ(date.GetMonth(), Month::JUNE);
    EXPECT_EQ(date.GetYear(), 2023);
    EXPECT_EQ(date.GetWeekDay(), WeekDay::THURSDAY);

    CDate leapDate(29, Month::FEBRUARY, 2024);
    EXPECT_EQ(leapDate.GetDay(), 29);
    EXPECT_EQ(leapDate.GetMonth(), Month::FEBRUARY);
    EXPECT_EQ(leapDate.GetYear(), 2024);
}

TEST(CDateTest, ComparisonOperators)
{
    CDate date1(15, Month::JUNE, 2023);
    CDate date2(20, Month::JUNE, 2023);
    CDate date3(15, Month::JUNE, 2023);

    EXPECT_TRUE(date1 < date2);
    EXPECT_FALSE(date2 < date1);
    EXPECT_TRUE(date1 <= date2);
    EXPECT_TRUE(date1 <= date3);
    EXPECT_TRUE(date2 > date1);
    EXPECT_TRUE(date1 >= date3);
    EXPECT_TRUE(date1 == date3);
    EXPECT_TRUE(date1 != date2);
}

TEST(CDateTest, ArithmeticOperators)
{
    CDate date(1, Month::JANUARY, 2023);

    CDate date2 = ++date;
    EXPECT_EQ(date.GetDay(), 2);
    EXPECT_EQ(date2.GetDay(), 2);

    CDate date3 = date++;
    EXPECT_EQ(date.GetDay(), 3);
    EXPECT_EQ(date3.GetDay(), 2);

    CDate date4 = --date;
    EXPECT_EQ(date.GetDay(), 2);
    EXPECT_EQ(date4.GetDay(), 2);

    CDate date5 = date--;
    EXPECT_EQ(date.GetDay(), 1);
    EXPECT_EQ(date5.GetDay(), 2);

    CDate date6 = date + 10;
    EXPECT_EQ(date6.GetDay(), 11);

    CDate date7 = date6 - 5;
    EXPECT_EQ(date7.GetDay(), 6);

    date7 += 4;
    EXPECT_EQ(date7.GetDay(), 10);
    date7 -= 9;
    EXPECT_EQ(date7.GetDay(), 1);

    EXPECT_EQ(date6 - date7, 10);
}

TEST(CDateTest, WeekDayCalculation)
{
    EXPECT_EQ(CDate(1, Month::JANUARY, 1970).GetWeekDay(), WeekDay::THURSDAY);
    EXPECT_EQ(CDate(2, Month::JANUARY, 1970).GetWeekDay(), WeekDay::FRIDAY);
    EXPECT_EQ(CDate(3, Month::JANUARY, 1970).GetWeekDay(), WeekDay::SATURDAY);
    EXPECT_EQ(CDate(4, Month::JANUARY, 1970).GetWeekDay(), WeekDay::SUNDAY);
    EXPECT_EQ(CDate(31, Month::DECEMBER, 9999).GetWeekDay(), WeekDay::FRIDAY);
}

TEST(CDateTest, EdgeCases)
{
    CDate endOfJan(31, Month::JANUARY, 2023);
    CDate startOfFeb = endOfJan + 1;
    EXPECT_EQ(startOfFeb.GetDay(), 1);
    EXPECT_EQ(startOfFeb.GetMonth(), Month::FEBRUARY);

    CDate endOfYear(31, Month::DECEMBER, 2023);
    CDate startOfNewYear = endOfYear + 1;
    EXPECT_EQ(startOfNewYear.GetDay(), 1);
    EXPECT_EQ(startOfNewYear.GetMonth(), Month::JANUARY);
    EXPECT_EQ(startOfNewYear.GetYear(), 2024);
}

TEST(CDateTest, IOStreamOperators)
{
    CDate date(15, Month::JUNE, 2023);
    std::ostringstream oss;
    oss << date;
    EXPECT_EQ(oss.str(), "15/6/2023");
    
    std::istringstream iss("20/7/2023");
    CDate date2;
    iss >> date2;
    EXPECT_EQ(date2.GetDay(), 20);
    EXPECT_EQ(date2.GetMonth(), Month::JULY);
    EXPECT_EQ(date2.GetYear(), 2023);

    std::istringstream badIss("20-7-2023");
    CDate date3;
    badIss >> date3;
    EXPECT_TRUE(badIss.fail());
}

TEST(CDateTest, ThreeWayComparison)
{
    CDate date1(15, Month::JUNE, 2023);
    CDate date2(20, Month::JUNE, 2023);
    CDate date3(15, Month::JUNE, 2023);

    EXPECT_TRUE(date1 < date2);
    EXPECT_TRUE(date2 > date1);
    EXPECT_TRUE(date1 == date3);
}

TEST(CDateTest, FriendAdditionOperator)
{
    CDate date(15, Month::JUNE, 2023);
    CDate date2 = 5 + date;
    EXPECT_EQ(date2.GetDay(), 20);
}

TEST(CDateTest, FebruaryEdgeCases)
{
    EXPECT_NO_THROW(CDate(28, Month::FEBRUARY, 2023));
    EXPECT_THROW(CDate(29, Month::FEBRUARY, 2023), std::invalid_argument);
    EXPECT_NO_THROW(CDate(29, Month::FEBRUARY, 2024));
    EXPECT_THROW(CDate(30, Month::FEBRUARY, 2024), std::invalid_argument);
}

TEST(CDateTest, MonthBoundaries)
{
    EXPECT_NO_THROW(CDate(31, Month::JANUARY, 2023));
    EXPECT_NO_THROW(CDate(28, Month::FEBRUARY, 2023));
    EXPECT_NO_THROW(CDate(31, Month::MARCH, 2023));
    EXPECT_NO_THROW(CDate(30, Month::APRIL, 2023));
    EXPECT_NO_THROW(CDate(31, Month::MAY, 2023));
    EXPECT_NO_THROW(CDate(30, Month::JUNE, 2023));
    EXPECT_NO_THROW(CDate(31, Month::JULY, 2023));
    EXPECT_NO_THROW(CDate(31, Month::AUGUST, 2023));
    EXPECT_NO_THROW(CDate(30, Month::SEPTEMBER, 2023));
    EXPECT_NO_THROW(CDate(31, Month::OCTOBER, 2023));
    EXPECT_NO_THROW(CDate(30, Month::NOVEMBER, 2023));
    EXPECT_NO_THROW(CDate(31, Month::DECEMBER, 2023));

    EXPECT_THROW(CDate(32, Month::JANUARY, 2023), std::invalid_argument);
    EXPECT_THROW(CDate(31, Month::APRIL, 2023), std::invalid_argument);
    EXPECT_THROW(CDate(32, Month::DECEMBER, 2023), std::invalid_argument);
}

TEST(CDateTest, LeapYearAdjustment)
{
    CDate date1(1, Month::MARCH, 2024);
    CDate date2(1, Month::MARCH, 2023);
    EXPECT_EQ(date1 - date2, 366);

    CDate preLeap(28, Month::FEBRUARY, 2024);
    CDate postLeap = preLeap + 1;
    EXPECT_EQ(postLeap.GetDay(), 29);
    EXPECT_EQ(postLeap.GetMonth(), Month::FEBRUARY);

    CDate march1st = postLeap + 1;
    EXPECT_EQ(march1st.GetDay(), 1);
    EXPECT_EQ(march1st.GetMonth(), Month::MARCH);

    CDate febDate(15, Month::FEBRUARY, 2024);
    CDate janDate(15, Month::JANUARY, 2024);
    EXPECT_EQ(febDate - janDate, 31);
}

TEST(CDateTest, LeapYearMonthBoundaries)
{
    CDate feb28(28, Month::FEBRUARY, 2024);
    CDate feb29 = feb28 + 1;
    CDate mar1 = feb29 + 1;

    EXPECT_EQ(feb29.GetDay(), 29);
    EXPECT_EQ(mar1.GetDay(), 1);
    EXPECT_EQ(mar1.GetMonth(), Month::MARCH);

    EXPECT_EQ(feb28.GetWeekDay(), WeekDay::WEDNESDAY);
    EXPECT_EQ(feb29.GetWeekDay(), WeekDay::THURSDAY);
    EXPECT_EQ(mar1.GetWeekDay(), WeekDay::FRIDAY);
}

TEST(CDateTest, LeapYearNoAdjustment)
{
    CDate date1(1, Month::MARCH, 2023);
    CDate date2(1, Month::MARCH, 2022);
    EXPECT_EQ(date1 - date2, 365);

    CDate feb1(1, Month::FEBRUARY, 2024);
    CDate jan1(1, Month::JANUARY, 2024);
    EXPECT_EQ(feb1 - jan1, 31);
}