#ifndef CDATE_H
#define CDATE_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

//Месяцы
enum class Month
{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

// Дни недели
enum class WeekDay
{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

class CDate
{
public:
	static char DELIMITER;
	CDate(unsigned day, Month month, unsigned year);

	explicit CDate(unsigned timestamp);

	CDate() = default;
	unsigned GetDay() const;
	WeekDay GetWeekDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;

	CDate operator+(int days) const;
	CDate& operator++();
	CDate operator++(int);

	CDate operator-(int days) const;
	CDate& operator--();
	CDate operator--(int);
	int operator-(const CDate& date2) const;

	CDate& operator+=(int days);
	CDate& operator-=(int days);

	std::strong_ordering operator<=>(const CDate &) const;
	bool operator==(const CDate& date) const = default;

	friend CDate operator+(int days, const CDate& cDate);
	friend std::istream& operator>>(std::istream& is, CDate& date);
	friend std::ostream& operator<<(std::ostream& os, const CDate& date);

private:
	static const std::array<WeekDay, 7> NUMBER_OF_WEEKDAY;
	static const std::array<unsigned, 12> DAYS_IN_MONTH;
	static const std::array<unsigned, 12> DAYS_TO_MONTH;

	static constexpr unsigned MAX_AVAILABLE_YEAR = 9999;
	static constexpr unsigned MIN_AVAILABLE_YEAR = 1970;

	static constexpr unsigned MAX_AVAILABLE_MONTH = 12;
	static constexpr unsigned MIN_AVAILABLE_MONTH = 1;

	static constexpr unsigned DAYS_OF_WEEK = 7;
	static const std::map<unsigned, WeekDay> NUMBER_WEEKDAY;

	static constexpr unsigned MIN_AVAILABLE_DAY = 1;
	static constexpr unsigned MAX_AVAILABLE_DAY = 31;
	static constexpr unsigned DAYS_IN_YEAR = 365;
	static constexpr double DAYS_IN_YEAR_ACCURATE = 365.2425;
	unsigned m_days = MIN_AVAILABLE_DAY;

	static bool IsLeapYear(unsigned year);
	static bool IsFebruary(unsigned monthIndex);
	static unsigned CalculateDays(int year);
	static bool ExceedsDays(int indexByMonth, unsigned days, unsigned daysInMonth, unsigned year);
	static bool IsValid(unsigned day, Month month, unsigned year);
};
#endif //CDATE_H
