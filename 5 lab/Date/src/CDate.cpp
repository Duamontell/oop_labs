#include "../include/CDate.h"

#include <chrono>

unsigned CDate::GetDay() const
{
	int countYear = static_cast<int>(m_timestamp / 365.2425) + START_YEAR;
	bool isLeapYear = countYear % 4 == 0 && countYear % 100 != 0 || countYear % 400 == 0;
	int countLeapYears = (countYear / 4 - countYear / 100 + countYear / 400) - COUNT_LEAP_YEARS_FROM_JESUS_BIRTHDAY_TO_START_YEAR;
	if (isLeapYear)
	{
		countLeapYears -= 1;
	}
	int day = static_cast<int>(m_timestamp) - countLeapYears * 366 - (countYear - START_YEAR - countLeapYears) * 365 + 1;

	for (auto monthDay : monthDays)
	{
		if (monthDay.first == Month::FEBRUARY && isLeapYear)
		{
			if (day - monthDay.second - 1 <= 0)
			{
				break;
			}
			day -= monthDay.second + 1;
		}
		else if (day - monthDay.second <= 0)
		{
			break;
		}
		else
		{
			day -= monthDay.second;
		}
	}

	return static_cast<unsigned>(day);
}

Month CDate::GetMonth() const
{
	int countYear = static_cast<int>(m_timestamp / 365.2425) + START_YEAR;
	bool isLeapYear = countYear % 4 == 0 && countYear % 100 != 0 || countYear % 400 == 0;
	int countLeapYears = (countYear / 4 - countYear / 100 + countYear / 400) - COUNT_LEAP_YEARS_FROM_JESUS_BIRTHDAY_TO_START_YEAR;
	int day = static_cast<int>(m_timestamp) - countLeapYears * 366 - (countYear - START_YEAR - countLeapYears) * 365 + 1;

	for (auto monthDay : monthDays)
	{
		if (monthDay.first == Month::FEBRUARY && isLeapYear)
		{
			if (day - monthDay.second - 1 <= 0)
			{
				return monthDay.first;
			}
		}
		else if (day - monthDay.second <= 0)
		{
			return monthDay.first;
		}
		day -= monthDay.second;
	}
}

unsigned CDate::GetYear() const
{
	return m_timestamp / 365.2425 + START_YEAR;
}

WeekDay CDate::GetWeekDay() const
{
	int countYear = static_cast<int>(m_timestamp / 365.2425) + START_YEAR;
	bool isLeapYear = countYear % 4 == 0 && countYear % 100 != 0 || countYear % 400 == 0;
	int countLeapYears = (countYear / 4 - countYear / 100 + countYear / 400) - COUNT_LEAP_YEARS_FROM_JESUS_BIRTHDAY_TO_START_YEAR;
	if (isLeapYear)
	{
		countLeapYears -= 1;
	}
	int day = static_cast<int>(m_timestamp) - countLeapYears * 366 - (countYear - START_YEAR - countLeapYears) * 365 + 1;
	int countDayShift = countLeapYears * 2 + (countYear - START_YEAR - countLeapYears);
	int countShift = 0;
	int countWeek = 0;
	int countDay = 0;
	for (auto monthDay : monthDays)
	{
		if (monthDay.first == Month::FEBRUARY && isLeapYear)
		{
			if (day - monthDay.second - 1 <= 0)
			{
				break;
			}
		}
		else if (day - monthDay.second <= 0)
		{
			break;
		}
		day -= monthDay.second;
		countWeek += monthDay.second / 7;
		countShift = monthDay.second % 7;
	}
	countWeek += countShift + 1;
	countDay = countShift % 7;
	int weekDay = countDayShift % 7;

	return static_cast<WeekDay>(weekDay);
}

bool CDate::IsValideDayInMonth(unsigned day, Month month, bool isLeapYear)
{
	int countDaysInMonth = monthDays.find(month)->second;
	if (month == Month::FEBRUARY)
	{
		if (isLeapYear)
		{
			return day <= countDaysInMonth + 1;
		}
	}
	return day <= countDaysInMonth;
}
