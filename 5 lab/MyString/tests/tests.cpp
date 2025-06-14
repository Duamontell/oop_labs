#include <gtest/gtest.h>
#include "../include/CMyString.h"

TEST(MyStringConstructorTest, CreateEmptyString)
{
	CMyString empty;
	EXPECT_STREQ(empty.GetStringData(), "");
	EXPECT_EQ(empty.GetLength(), 0);
	EXPECT_EQ(empty.GetCapacity(), 0);
}

TEST(MyStringConstructorTest, CreateStringFromStringDataTest)
{
	CMyString myString("Hello, World!");
	EXPECT_STREQ(myString.GetStringData(), "Hello, World!");
	EXPECT_EQ(myString.GetLength(), 13);
	EXPECT_EQ(myString.GetCapacity(), 13);
}

TEST(MyStringConstructorTest, CreateStringSpecifiedLengthTest)
{
	CMyString myString("Hello, World!", 5);
	EXPECT_STREQ(myString.GetStringData(), "Hello");
	EXPECT_EQ(myString.GetLength(), 5);
	EXPECT_EQ(myString.GetCapacity(), 5);
}

TEST(MyStringConstructorTest, CreateCopyStringTest)
{
	CMyString temp("Hello, World!");
	CMyString myString(temp);
	EXPECT_NE(myString.GetStringData(), temp.GetStringData());
	EXPECT_STREQ(myString.GetStringData(), "Hello, World!");
	EXPECT_EQ(myString.GetLength(), temp.GetLength());
	EXPECT_EQ(myString.GetCapacity(), temp.GetCapacity());
}

TEST(MyStringConstructorTest, MoveConstructorTest)
{
	CMyString myString("Hello, World!");
	CMyString myString1(std::move(myString));
	EXPECT_STREQ(myString1.GetStringData(), "Hello, World!");
	EXPECT_STREQ(myString.GetStringData(), "");

	CMyString myString2(std::move(myString));
	EXPECT_STREQ(myString2.GetStringData(), "");
	EXPECT_STREQ(myString.GetStringData(), "");
}

TEST(MyStringConstructorTest, CreateStringFromStlStringTest)
{
	std::string stlString = "Hello, World!";
	CMyString myString(stlString);
	EXPECT_NE(myString.GetStringData(), stlString.c_str());
	EXPECT_STREQ(myString.GetStringData(), "Hello, World!");
	EXPECT_EQ(myString.GetLength(), myString.GetLength());
	EXPECT_EQ(myString.GetCapacity(), myString.GetCapacity());
}

TEST(MyStringMethodsTest, GetLengthTest)
{
	CMyString myString = "";
	EXPECT_EQ(myString.GetLength(), 0);
	CMyString myString1 = "Hello, World!";
	EXPECT_EQ(myString1.GetLength(), 13);
}

TEST(MyStringMethodsTest, GetStringDataTest)
{
	CMyString myString = "";
	EXPECT_STREQ(myString.GetStringData(), "");
	CMyString myString1 = "Hello, World!";
	EXPECT_STREQ(myString1.GetStringData(), "Hello, World!");
}

TEST(MyStringMethodsTest, SubStringTest)
{
	CMyString myString = "Hello, World!";
	EXPECT_STREQ(myString.SubString(4).GetStringData(), "o, World!");
	CMyString myString1 = "";
	EXPECT_STREQ(myString1.SubString(0).GetStringData(), "");
	CMyString myString2 = "";
	EXPECT_STREQ(myString2.SubString(5).GetStringData(), "");
	CMyString myString3 = "";
	EXPECT_STREQ(myString3.SubString(5, 2).GetStringData(), "");

	CMyString myString4 = "Hello, World!";
	EXPECT_STREQ(myString4.SubString(10, 0).GetStringData(), "");
}

TEST(MyStringMethodsTest, ClearTest)
{
	CMyString myString("Hello, World!");
	myString.Clear();
	EXPECT_STREQ(myString.GetStringData(), "");
	EXPECT_EQ(myString.GetLength(), 0);
	EXPECT_EQ(myString.GetCapacity(), 0);

	CMyString myString1 = "";
	myString1.Clear();
	EXPECT_STREQ(myString1.GetStringData(), "");
	EXPECT_EQ(myString1.GetLength(), 0);
	EXPECT_EQ(myString1.GetCapacity(), 0);
}

TEST(MyStringMethodsTest, GetCapacityTest)
{
	CMyString myString("Hello, World!");
	EXPECT_EQ(myString.GetCapacity(), 13);
	CMyString myString1("");
	EXPECT_EQ(myString1.GetCapacity(), 0);
}

TEST(MyStringOperatorsTest, AssignTest)
{
	CMyString myString("");
	myString = "Hello, World!";
	EXPECT_STREQ(myString.GetStringData(), "Hello, World!");
	myString = "Hello";
	EXPECT_STREQ(myString.GetStringData(), "Hello");
	myString = myString;
	EXPECT_STREQ(myString.GetStringData(), "Hello");
}

TEST(MyStringOperatorsTest, PlusTest)
{
	CMyString myString("");
	CMyString myString1("Hello, World!");
	EXPECT_STREQ((myString + myString1).GetStringData(), "Hello, World!");
	EXPECT_EQ((myString + myString1).GetCapacity(), 16);
	std::string str = "123";
	EXPECT_STREQ((myString + str).GetStringData(), "123");
	EXPECT_EQ((myString + str).GetCapacity(), 4);

	EXPECT_STREQ((myString + str + "456").GetStringData(), "123456");
	EXPECT_EQ((myString + str + "456").GetCapacity(), 6);
}

TEST(MyStringOperatorsTest, PlusEqualTest)
{
	CMyString myString("");
	CMyString myString1("Hello, World!");
	myString += myString1;
	EXPECT_STREQ(myString.GetStringData(), "Hello, World!");
	EXPECT_EQ(myString.GetCapacity(), 16);

	CMyString myString2 = "Halo";
	CMyString myString3 = "Hello, World!";
	myString2 += myString3;
	EXPECT_STREQ(myString2.GetStringData(), "HaloHello, World!");
	EXPECT_EQ(myString2.GetCapacity(), 32);
}

TEST(MyStringOperatorsTest, EqualTest)
{
	CMyString myString("Hello, World!");
	CMyString myString1("Hello, World!");
	EXPECT_TRUE(myString == myString1);
	EXPECT_FALSE(myString == "Hello");
	EXPECT_FALSE("Hello" == myString);
}

TEST(MyStringOperatorsTest, NotEqualTest)
{
	CMyString myString("Hello, World!");
	CMyString myString1("Hello, World!");
	EXPECT_FALSE(myString != myString1);
	EXPECT_TRUE(myString != "Hello");
	EXPECT_TRUE("Hello" != myString);
}

TEST(MyStringOperatorsTest, LessTest)
{
	CMyString myString("Hello");
	CMyString myString1("Hello, World!");
	EXPECT_TRUE(myString < myString1);
	EXPECT_FALSE(myString1 < myString);
	EXPECT_FALSE("Hello" < myString);
	EXPECT_TRUE("Hell" < myString);
	EXPECT_TRUE("" < myString);
	EXPECT_TRUE("     " < myString);
}

TEST(MyStringOperatorsTest, GreaterTest)
{
	CMyString myString("Hello");
	CMyString myString1("Hello, World!");
	EXPECT_FALSE(myString > myString1);
	EXPECT_TRUE( myString1 > myString);
	EXPECT_FALSE("Hello" > myString);
	EXPECT_FALSE("Hell" > myString);
	EXPECT_FALSE("" > myString);
	EXPECT_FALSE("     " > myString);
}

TEST(MyStringOperatorsTest, LessEqualTest)
{
	CMyString myString("Hello");
	CMyString myString1("Hello, World!");
	EXPECT_TRUE(myString <= myString1);
	EXPECT_FALSE(myString1 <= myString);
	EXPECT_TRUE("Hello" <= myString);
	EXPECT_TRUE("Hell" <= myString);
	EXPECT_TRUE("" <= myString);
	EXPECT_TRUE("     " <= myString);
}

TEST(MyStringOperatorsTest, GreaterEqualTest)
{
	CMyString myString("Hello");
	CMyString myString1("Hello, World!");
	EXPECT_FALSE(myString  >= myString1);
	EXPECT_TRUE(myString1 >= myString);
	EXPECT_TRUE("Hello" >= myString);
	EXPECT_FALSE("Hell" >= myString);
	EXPECT_FALSE("" >= myString);
	EXPECT_FALSE("     " >= myString);
}

TEST(MyStringOperatorsTest, OutputStreamTest)
{
	CMyString myString("Hello, World!");
	std::ostringstream os;
	os << myString;
	EXPECT_EQ("Hello, World!", os.str());
	CMyString myString1("");
	std::ostringstream os1;
	os1 << myString1;
	EXPECT_EQ("", os1.str());
}

TEST(MyStringOperatorsTest, InputStreamTest)
{
	std::istringstream is("Hello, World!");
	CMyString myString("H");
	is >> myString;
	EXPECT_STREQ("Hello,", myString.GetStringData());

	std::istringstream is1("Hel");
	CMyString myString1("Hel1223");
	is1 >> myString1;
	EXPECT_STREQ("Hel", myString1.GetStringData());

	std::istringstream is2("");
	CMyString myString2("");
	is2 >> myString2;
	EXPECT_STREQ("", myString2.GetStringData());
}

TEST(MyStringOperatorsTest, IndexForReadTest)
{
	CMyString myString("Hello");
	EXPECT_EQ(myString[0], 'H');
	EXPECT_EQ(myString[1], 'e');
	EXPECT_EQ(myString[2], 'l');
	EXPECT_EQ(myString[3], 'l');
	EXPECT_EQ(myString[4], 'o');
	EXPECT_EQ(myString[5], '\0');
}

TEST(MyStringOperatorsTest, IndexForWriteTest)
{
	CMyString myString("Hello");
	myString[0] = 'f';
	EXPECT_STREQ(myString.GetStringData(), "fello");
	CMyString myString1(" S");
	myString1[0] = '1';
	EXPECT_STREQ(myString1.GetStringData(), "1S");
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}