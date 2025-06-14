#include <gtest/gtest.h>
#include "../include/CMyArray.h"

// Добавить тесты для ranged-based for
TEST(MyArrayConstructorTest, DefaultConstructorTest)
{
	CMyArray<double> myArray;
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);

	const CMyArray<double> myArray2;
	EXPECT_EQ(myArray2.GetSize(), 0);
	EXPECT_EQ(myArray2.GetCapacity(), 0);
}

TEST(MyArrayConstructorTest, CopyConstructorTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.4);
	myArray.PushBack(2.3);
	myArray.PushBack(3.4);
	CMyArray<double> myArray2(myArray);
	EXPECT_EQ(myArray2.GetSize(), 3);
	EXPECT_EQ(myArray.GetSize(), myArray2.GetSize());
	EXPECT_EQ(myArray2.GetCapacity(), 3);
	EXPECT_EQ(myArray2[0], 1.4);
	EXPECT_EQ(myArray2[1], 2.3);
	EXPECT_EQ(myArray2[2], 3.4);
	EXPECT_EQ(myArray[0], myArray2[0]);
	EXPECT_EQ(myArray[1], myArray2[1]);
	EXPECT_EQ(myArray[2], myArray2[2]);
}

TEST(MyArrayConstructorTest, MoveConstructorTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.4);
	myArray.PushBack(2.3);
	myArray.PushBack(3.4);
	CMyArray<double> myArray2(std::move(myArray));
	EXPECT_EQ(myArray2.GetSize(), 3);
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray2.GetCapacity(), 4);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_EQ(myArray2[0], 1.4);
	EXPECT_EQ(myArray2[1], 2.3);
	EXPECT_EQ(myArray2[2], 3.4);
}

TEST(MyArrayOperatorsTest, AssignTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	CMyArray<double> myArray2;
	myArray2 = myArray;
	EXPECT_EQ(myArray2.GetSize(), 3);
	EXPECT_EQ(myArray.GetSize(), myArray2.GetSize());
	EXPECT_EQ(myArray2.GetCapacity(), 3);

	EXPECT_EQ(myArray2[0], 1.0);
	EXPECT_EQ(myArray2[1], 2.0);
	EXPECT_EQ(myArray2[2], 5.0);

	myArray2 = myArray2;
	EXPECT_EQ(myArray2.GetSize(), 3);
	EXPECT_EQ(myArray.GetSize(), myArray2.GetSize());
	EXPECT_EQ(myArray2.GetCapacity(), 3);
	EXPECT_EQ(myArray2[0], 1.0);
	EXPECT_EQ(myArray2[1], 2.0);
	EXPECT_EQ(myArray2[2], 5.0);

	CMyArray<double> myArray3;
	myArray3 = std::move(myArray2);
	EXPECT_EQ(myArray3.GetSize(), 3);
	EXPECT_EQ(myArray.GetSize(), myArray3.GetSize());
	EXPECT_EQ(myArray3.GetCapacity(), 3);
	EXPECT_EQ(myArray3[0], 1.0);
	EXPECT_EQ(myArray3[1], 2.0);
	EXPECT_EQ(myArray3[2], 5.0);
}

TEST(MyArrayOperatorsTest, IndexTest)
{
	CMyArray<double> myArray;
	EXPECT_THROW(myArray[0], std::out_of_range);
	EXPECT_THROW(myArray[1], std::out_of_range);
	myArray.PushBack(15);
	EXPECT_EQ(myArray[0], 15);
	EXPECT_THROW(myArray[-1], std::out_of_range);

	const CMyArray<double> myArray1;
	EXPECT_THROW(myArray1[100], std::out_of_range);
	EXPECT_THROW(myArray1[2], std::out_of_range);
	EXPECT_THROW(myArray1[1], std::out_of_range);
	EXPECT_THROW(myArray1[0], std::out_of_range);
	EXPECT_THROW(myArray1[-1], std::out_of_range);
	EXPECT_THROW(myArray1[-2], std::out_of_range);
	EXPECT_THROW(myArray1[-100], std::out_of_range);

	const CMyArray<double> myArray2(myArray);
	EXPECT_EQ(myArray2[0], 15);
	EXPECT_EQ(myArray2.GetSize(), 1);
	EXPECT_THROW(myArray2[1], std::out_of_range);
	EXPECT_THROW(myArray2[-1], std::out_of_range);
}

TEST(MyArrayIteratorTest, BeginTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	EXPECT_EQ(*myArray.begin(), 1.0);
}

TEST(MyArrayIteratorTest, EndTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	EXPECT_EQ(*--myArray.end(), 5.0);
}

TEST(MyArrayIteratorTest, RbeginTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	EXPECT_EQ(*myArray.rbegin(), 5.0);
}

TEST(MyArrayIteratorTest, REndTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	EXPECT_EQ(*--myArray.rend(), 1.0);
}

TEST(MyArrayIteratorTest, DereferenceTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	EXPECT_EQ(*myArray.begin(), 1.0);
	EXPECT_EQ(*myArray.rbegin(), 5.0);
}

TEST(MyArrayIteratorTest, ArrowOperationTest)
{
	CMyArray<std::string> myArray;
	myArray.PushBack("Halo");
	myArray.PushBack("Hello");
	myArray.PushBack("World");
	EXPECT_FALSE(myArray.begin()->empty());
	EXPECT_EQ(myArray.begin()->size(), 4);
}

TEST(MyArrayIteratorTest, PrefixPlusTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.begin();
	auto it2 = ++it;
	EXPECT_EQ(*it, 2.0);
	EXPECT_EQ(*it2, 2.0);
}

TEST(MyArrayIteratorTest, PostfixPlusTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.begin();
	auto it2 = it++;
	EXPECT_EQ(*it, 2.0);
	EXPECT_EQ(*it2, 1.0);
}

TEST(MyArrayIteratorTest, PrefixMinusTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = --myArray.end();
	auto it2 = --it;
	EXPECT_EQ(*it, 2.0);
	EXPECT_EQ(*it2, 2.0);
}

TEST(MyArrayIteratorTest, PostfixMinusTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = --myArray.end();
	auto it2 = it--;
	EXPECT_EQ(*it, 2.0);
	EXPECT_EQ(*it2, 5.0);
}

TEST(MyArrayIteratorTest, PlusTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.begin();
	it = it + 2;
	EXPECT_EQ(*it, 5.0);
}

TEST(MyArrayIteratorTest, PlusEqualTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.begin();
	it += 2;
	EXPECT_EQ(*it, 5.0);
}

TEST(MyArrayIteratorTest, MinusTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.end();
	it = it - 2;
	EXPECT_EQ(*it, 2.0);
}

TEST(MyArrayIteratorTest, MinusEqualTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.end();
	it -= 2;
	EXPECT_EQ(*it, 2.0);
}

TEST(MyArrayIteratorTest, EqualTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.end();
	EXPECT_TRUE(it == myArray.end());
	EXPECT_TRUE(--it == --myArray.end());
	EXPECT_TRUE(myArray.begin() == myArray.begin());
	EXPECT_TRUE(myArray.rbegin() == myArray.rbegin());
}

TEST(MyArrayIteratorTest, NotEqualTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.0);
	myArray.PushBack(2.0);
	myArray.PushBack(5.0);
	auto it = myArray.end();
	EXPECT_FALSE(it != myArray.end());
	EXPECT_FALSE(--it != --myArray.end());
	EXPECT_FALSE(myArray.begin() != myArray.begin());
	EXPECT_FALSE(myArray.rbegin() != myArray.rbegin());
	EXPECT_TRUE(myArray.begin() != myArray.end());
}

TEST(MyArrayMethodsTest, PushBackTest)
{
	CMyArray<double> myArray;
	myArray.PushBack(1.2);
	EXPECT_EQ(myArray[0], 1.2);
	EXPECT_EQ(myArray.GetSize(), 1);
	EXPECT_EQ(myArray.GetCapacity(), 1);
	myArray.PushBack(3.0000005);
	EXPECT_EQ(myArray[1], 3.0000005);
	EXPECT_EQ(myArray.GetSize(), 2);
	EXPECT_EQ(myArray.GetCapacity(), 2);
	myArray.PushBack(5.041);
	EXPECT_EQ(myArray[2], 5.041);
	EXPECT_EQ(myArray.GetSize(), 3);
	EXPECT_EQ(myArray.GetCapacity(), 4);
}

TEST(MyArrayMethodsTest, ResizeTest)
{
	CMyArray<std::string> myArray;
	myArray.Resize(2);
	EXPECT_EQ(myArray.GetSize(), 2);
	EXPECT_EQ(myArray.GetCapacity(), 2);
	EXPECT_EQ(myArray[0], "");
	EXPECT_EQ(myArray[1], "");
	myArray.PushBack("hello");
	myArray.Resize(3);
	EXPECT_EQ(myArray.GetSize(), 3);
	EXPECT_EQ(myArray.GetCapacity(), 4);
	EXPECT_EQ(myArray[0], "");
	EXPECT_EQ(myArray[1], "");
	EXPECT_EQ(myArray[2], "hello");
	myArray.PushBack("world");
	myArray.Resize(1);
	EXPECT_EQ(myArray.GetSize(), 1);
	EXPECT_EQ(myArray.GetCapacity(), 4);
	EXPECT_EQ(myArray[0], "");

	myArray.Resize(1);
	EXPECT_EQ(myArray.GetSize(), 1);
	EXPECT_EQ(myArray.GetCapacity(), 4);
	myArray.Resize(2);
	EXPECT_EQ(myArray.GetSize(), 2);
	EXPECT_EQ(myArray.GetCapacity(), 4);
	EXPECT_EQ(myArray[0], "");
	EXPECT_EQ(myArray[1], "");
}

TEST(MyArrayMethodsTest, GetSizeTest)
{
	CMyArray<std::string> myArray;
	myArray.PushBack("hello");
	EXPECT_EQ(myArray.GetSize(), 1);
	myArray.PushBack("world");
	EXPECT_EQ(myArray.GetSize(), 2);
	myArray.PushBack("hello");
	EXPECT_EQ(myArray.GetSize(), 3);
}

TEST(MyArrayMethodsTest, GetCapacityTest)
{
	CMyArray<std::string> myArray;
	myArray.PushBack("hello");
	EXPECT_EQ(myArray.GetCapacity(), 1);
	myArray.PushBack("world");
	EXPECT_EQ(myArray.GetCapacity(), 2);
	myArray.PushBack("hello");
	EXPECT_EQ(myArray.GetCapacity(), 4);
	myArray.PushBack("hello");
	myArray.PushBack("world");
	EXPECT_EQ(myArray.GetCapacity(), 8);
}

TEST(MyArrayMethodsTest, ClearTest)
{
	CMyArray<double> myArray;
	myArray.Clear();
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_THROW(myArray[0], std::out_of_range);

	myArray.PushBack(1.2);
	myArray.PushBack(3.0);
	myArray.PushBack(5.041);
	myArray.Clear();
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_THROW(myArray[0], std::out_of_range);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}