#include <gtest/gtest.h>
#include "../include/CDate.h"

TEST(CDateTest, CreateDateTest)
{
	EXPECT_NO_THROW(CDate date(30, Month::JUNE, 1970));
	EXPECT_NO_THROW(CDate date1(31, Month::DECEMBER, 2000));
	EXPECT_NO_THROW(CDate date1(29, Month::FEBRUARY, 2000));
	EXPECT_NO_THROW(CDate date2(0));
	EXPECT_NO_THROW(CDate date3(731));

	EXPECT_THROW(CDate date(32, Month::JANUARY, 2042), std::invalid_argument);
	EXPECT_THROW(CDate date(29, Month::FEBRUARY, 1999), std::invalid_argument);
	EXPECT_THROW(CDate date(32, Month::MARCH, 1970), std::invalid_argument);
	EXPECT_THROW(CDate date(31, Month::APRIL, 1970), std::invalid_argument);
	EXPECT_THROW(CDate date(32, Month::MAY, 1970), std::invalid_argument);
	EXPECT_THROW(CDate date(31, Month::JUNE, 1970), std::invalid_argument);
	EXPECT_THROW(CDate date(32, Month::JULY, 1970), std::invalid_argument);
	EXPECT_THROW(CDate date(32, Month::AUGUST, 1970), std::invalid_argument);
	EXPECT_THROW(CDate date(31, Month::SEPTEMBER, 1970), std::invalid_argument);
	EXPECT_THROW(CDate date(32, Month::OCTOBER, 1999), std::invalid_argument);
	EXPECT_THROW(CDate date(31, Month::NOVEMBER, 1999), std::invalid_argument);
	EXPECT_THROW(CDate date(32, Month::DECEMBER, 1999), std::invalid_argument);
}

TEST(CDateTest, GetDateTest)
{
	CDate date0(1, Month::JANUARY, 1970);
	EXPECT_EQ(date0.GetDay(), 1);
	CDate date(1, Month::JANUARY, 1972);
	EXPECT_EQ(date.GetDay(), 1);
	CDate date1(31, Month::JANUARY, 1972);
	EXPECT_EQ(date1.GetDay(), 31);
	CDate date2(29, Month::FEBRUARY, 1972);
	EXPECT_EQ(date2.GetDay(), 29);
	CDate date3(731);
	EXPECT_EQ(date3.GetDay(), 2);
	CDate date4(40434);
	EXPECT_EQ(date4.GetDay(), 14);
	CDate date5;
	EXPECT_EQ(date5.GetDay(), 1);
}

TEST(CDateTest, GetMonthTest)
{
	CDate date(31, Month::JANUARY, 1972);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	CDate date1(4, Month::APRIL, 2000);
	EXPECT_EQ(date1.GetMonth(), Month::APRIL);
	CDate date2(31, Month::DECEMBER, 9999);
	EXPECT_EQ(date2.GetMonth(), Month::DECEMBER);
}

TEST(CDateTest, GetYearTest)
{

}

TEST(CDateTest, WeekDayTest)
{
	CDate date(1, Month::JANUARY, 1970);
	EXPECT_EQ(date.GetWeekDay(), WeekDay::THURSDAY);
	CDate date1(1, Month::JANUARY, 1972);
	EXPECT_EQ(date1.GetWeekDay(), WeekDay::SATURDAY);
	CDate date2(1, Month::JANUARY, 1973);
	EXPECT_EQ(date2.GetWeekDay(), WeekDay::MONDAY);
	CDate date3(31, Month::DECEMBER, 1972);
	EXPECT_EQ(date3.GetWeekDay(), WeekDay::SUNDAY);
	CDate date4(29, Month::FEBRUARY, 2000);
	EXPECT_EQ(date4.GetWeekDay(), WeekDay::SATURDAY);
	CDate date5(29, Month::FEBRUARY, 2080);
	EXPECT_EQ(date5.GetWeekDay(), WeekDay::THURSDAY);
	CDate date6(14, Month::JULY, 2099);
	EXPECT_EQ(date6.GetWeekDay(), WeekDay::TUESDAY);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}