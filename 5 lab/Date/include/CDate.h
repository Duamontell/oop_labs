#ifndef CDATE_H
#define CDATE_H
#include <stdexcept>
#include <iostream>
#include <map>
#include <ostream>

const int COUNT_LEAP_YEARS_FROM_JESUS_BIRTHDAY_TO_START_YEAR = 477;
const int START_YEAR = 1970;

enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY,
};

const std::map<Month, int> monthDays = {
	{Month::JANUARY, 31},
	{Month::FEBRUARY, 28},
	{Month::MARCH, 31},
	{Month::APRIL, 30},
	{Month::MAY, 31},
	{Month::JUNE, 30},
	{Month::JULY, 31},
	{Month::AUGUST, 31},
	{Month::SEPTEMBER, 30},
	{Month::OCTOBER, 31},
	{Month::NOVEMBER, 30},
	{Month::DECEMBER, 31}
};
// Дата в формате день-месяц-год. Год в диапазоне от 1970 до 9999
class CDate
{
public:

	// инициализируем дату заданными днем, месяцем и годом.
	// примечание: год >= 1970
	CDate(unsigned day, Month month, unsigned year)
	{
		if (year < 1970 || day == 0|| day > 31 )
		{
			throw std::invalid_argument("Not a valid date.");
		}

		bool isLeapYear = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
		unsigned countLeapYears = (year / 4 - year / 100 + year / 400) - COUNT_LEAP_YEARS_FROM_JESUS_BIRTHDAY_TO_START_YEAR;
		if (isLeapYear)
		{
			countLeapYears -= 1;
		}
		m_timestamp = countLeapYears * 366 + (year - 1970 - countLeapYears) * 365;
		for (auto monthDay : monthDays)
		{
			if (monthDay.first == month)
			{
				break;
			}
			if (monthDay.first == Month::FEBRUARY && isLeapYear)
			{
				m_timestamp += 1;
			}
			m_timestamp += monthDay.second;
		}
		if (!IsValideDayInMonth(day, month, isLeapYear))
		{
			throw std::invalid_argument("Not a valid day.");
		}
		m_timestamp += day - 1;
	}

	// инициализируем дату количеством дней, прошедших после 1 января 1970 года
	// например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
	explicit CDate(unsigned timestamp) : m_timestamp(timestamp) {}

	// Конструктор по умолчанию. Создаёт дату, равную 1 января 1970.
	CDate() = default;

	unsigned GetDay()const;
	Month GetMonth()const;
	unsigned GetYear()const;
	WeekDay GetWeekDay()const;
private:
	unsigned m_timestamp = 0;
	bool IsValideDayInMonth(unsigned day, Month month, bool isLeapYear);
};

#endif //CDATE_H
