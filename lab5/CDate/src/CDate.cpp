#include "../include/CDate.h"
#include <array>
#include <compare>

const std::array<unsigned, 12> CDate::DAYS_IN_MONTH = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::array<unsigned, 12> CDate::DAYS_TO_MONTH = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

const std::array<WeekDay, 7> CDate::NUMBER_OF_WEEKDAY =
{
	WeekDay::WEDNESDAY,
	WeekDay::THURSDAY,
	WeekDay::FRIDAY,
	WeekDay::SATURDAY,
	WeekDay::SUNDAY,
	WeekDay::MONDAY,
	WeekDay::TUESDAY
};

char CDate::DELIMITER = '/';

CDate::CDate(unsigned int day, Month month, unsigned year)
{
	if (!IsValid(day, month, year))
	{
		throw std::invalid_argument("Invalid CDate");
	}

	m_days += day - MIN_AVAILABLE_DAY;
	m_days += DAYS_TO_MONTH.at(static_cast<int>(month) - 1);

	int yearCircle = static_cast<int>(year);
	m_days += CalculateDays(year);
	if (month > Month::FEBRUARY && IsLeapYear(yearCircle))
	{
		m_days += 1;
	}
}

CDate::CDate(unsigned int timestamp)
{
	m_days += timestamp;

	if (GetYear() < MIN_AVAILABLE_YEAR || GetYear() > MAX_AVAILABLE_YEAR)
	{
		throw std::invalid_argument("Invalid CDate");
	}
}

bool CDate::IsFebruary(unsigned int monthIndex)
{
	return monthIndex == static_cast<unsigned>(Month::FEBRUARY);
}

bool CDate::ExceedsDays(int indexByMonth, unsigned days, unsigned daysInMonth, unsigned year)
{
	if (indexByMonth == static_cast<int>(Month::FEBRUARY))
	{
		return days > daysInMonth + IsLeapYear(year);
	}
	return days > daysInMonth;
}

unsigned CDate::CalculateDays(int year)
{
	return static_cast<int>((year - MIN_AVAILABLE_YEAR) * DAYS_IN_YEAR
		+ (year - MIN_AVAILABLE_YEAR) / 4
		- (year - MIN_AVAILABLE_YEAR) / 100
		+ (year - MIN_AVAILABLE_YEAR) / 400);
}

unsigned CDate::GetDay() const
{
	unsigned year = MIN_AVAILABLE_YEAR;
	unsigned days = m_days;

	year = static_cast<unsigned>(year + days / DAYS_IN_YEAR_ACCURATE);
	days -= CalculateDays(year);

	for (unsigned index = 0; index < DAYS_IN_MONTH.size(); index++)
	{
		unsigned indexByMonth = index + 1;
		unsigned daysInMonth = DAYS_IN_MONTH.at(index);

		if (ExceedsDays(indexByMonth, days, daysInMonth, year))
		{
			days -= daysInMonth;
			if (IsFebruary(indexByMonth))
			{
				days -= IsLeapYear(year);
			}
		}
		else
		{
			break;
		}
	}
	return days;
}

Month CDate::GetMonth() const
{
	unsigned year = MIN_AVAILABLE_YEAR;
	unsigned days = m_days;

	year = static_cast<unsigned>(year + days / DAYS_IN_YEAR_ACCURATE);
	days -= CalculateDays(year);

	Month month = static_cast<Month>(MIN_AVAILABLE_MONTH);
	unsigned daysOfMonth = 0;
	for (unsigned index = 0; index < DAYS_IN_MONTH.size(); index++)
	{
		unsigned indexByMonth = index + 1;
		unsigned daysInMonth = DAYS_IN_MONTH.at(index);

		if (ExceedsDays(indexByMonth, days, daysOfMonth, year))
		{
			daysOfMonth += daysInMonth;
			if (IsFebruary(indexByMonth))
			{
				daysOfMonth += IsLeapYear(year);
			}
			month = static_cast<Month>(indexByMonth);
		}
		else
		{
			break;
		}
	}
	return month;
}

unsigned CDate::GetYear() const
{
	unsigned year = MIN_AVAILABLE_YEAR;
	unsigned days = m_days;

	year = static_cast<unsigned>(year + days / DAYS_IN_YEAR_ACCURATE);
	return year;
}

WeekDay CDate::GetWeekDay() const
{
	return NUMBER_OF_WEEKDAY[m_days % DAYS_OF_WEEK];
}

bool CDate::IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool CDate::IsValid(unsigned int day, Month month, unsigned int year)
{
	bool isValidMonth = (static_cast<int>(month) >= MIN_AVAILABLE_MONTH)
		&& (static_cast<int>(month) <= MAX_AVAILABLE_MONTH);

	bool isValidDay = false;
	if (isValidMonth)
	{
		isValidDay = (day >= MIN_AVAILABLE_DAY)
			&& (day <= DAYS_IN_MONTH.at(static_cast<int>(month) - 1) + IsLeapYear(year));
	}

	bool isValidYear = (year >= MIN_AVAILABLE_YEAR)
		&& (year <= MAX_AVAILABLE_YEAR);

	return isValidYear && isValidMonth && isValidDay;
}

CDate& CDate::operator++()
{
	++m_days;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp(*this);
	++(*this);
	return temp;
}

CDate& CDate::operator--()
{
	--m_days;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp(*this);
	--(*this);
	return temp;
}

CDate CDate::operator+(int days) const
{
	return CDate(m_days + days - MIN_AVAILABLE_DAY);
}

CDate CDate::operator-(int days) const
{
	return CDate(m_days - days - MIN_AVAILABLE_DAY);
}

int CDate::operator-(const CDate& date2) const
{
	auto deltaDays = static_cast<int>(m_days) - static_cast<int>(date2.m_days);

	return deltaDays;
}

CDate& CDate::operator+=(int days)
{
	m_days += static_cast<unsigned>(days);
	return *this;
}

CDate& CDate::operator-=(int days)
{
	m_days -= static_cast<unsigned>(days);
	return *this;
}

std::strong_ordering CDate::operator<=>(const CDate& date) const
{
	return m_days <=> date.m_days;
}

CDate operator+(int days, const CDate& cDate)
{
	return CDate(cDate.m_days + days - CDate::MIN_AVAILABLE_DAY);
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	os << date.GetDay() << '/' << static_cast<int>(date.GetMonth()) << '/' << date.GetYear();
	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned int day;
	unsigned year;
	int month;
	char dot;
	if (!(is >> day >> dot >> month >> dot >> year) || dot != '/')
	{
		is.setstate(std::ios::badbit);
		return is;
	}

	date = CDate(day, static_cast<Month>(month), year);
	return is;
}