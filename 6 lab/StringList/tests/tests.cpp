#include "../include/CStringList.h"
#include "gtest/gtest.h"

// Добавить тесты для константных итераторов
TEST(StringListConstructorTest, DefaultConstructorTest)
{
	CStringList list;
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_EQ(list.begin(), list.end());
}

TEST(StringListConstructorTest, CopyConstructorTest)
{
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");
	CStringList copy = list;
	EXPECT_EQ(copy.GetSize(), 2);
	EXPECT_EQ(*copy.begin(), *list.begin());
	EXPECT_EQ(*copy.begin(), "hello");
	EXPECT_EQ(*copy.rbegin(), *list.rbegin());
	EXPECT_EQ(*copy.rbegin(), "world");
}

TEST(StringListConstructorTest, MoveConstructorTest)
{
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");
	CStringList movedList(std::move(list));
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_EQ(list.begin(), nullptr);
	EXPECT_EQ(list.rbegin(), nullptr);

	EXPECT_EQ(movedList.GetSize(), 2);
	EXPECT_EQ(*movedList.begin(), "hello");
	EXPECT_EQ(*++movedList.begin(), "world");
}

TEST(StringListIteratorTest, IteratorTest)
{
	CStringList list;
	list.PushBack("Hello");
	list.PushBack("World!");
	EXPECT_EQ(*list.begin(), "Hello");
	EXPECT_EQ(*list.rbegin(), "World!");
}

TEST(IteratorOperatorsTest, OperatorArrowTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack("World!");

	auto it = list.begin();
	EXPECT_EQ(it->length(), 4);
	EXPECT_EQ(it->substr(0, 4), "Halo");
}

TEST(IteratorOperatorsTest, PrefixIncrementTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack("World!");
	auto it = list.begin();
	auto it1 = ++it;
	EXPECT_EQ(*it1, "World!");
	EXPECT_EQ(*it, "World!");
}

TEST(IteratorOperatorsTest, PostfixIncrementTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack("World!");
	auto it = list.begin();
	auto it1 = it++;
	EXPECT_EQ(*it1, "Halo");
	EXPECT_EQ(*it, "World!");
}

TEST(IteratorOperatorsTest, PrefixDecrementTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack("World!");
	auto it = ++list.begin();
	auto it1 = --it;
	EXPECT_EQ(*it1, "Halo");
	EXPECT_EQ(*it, "Halo");
}

TEST(IteratorOperatorsTest, PostfixDecrementTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack("World!");
	auto it = ++list.begin();
	auto it1 = it--;
	EXPECT_EQ(*it1, "World!");
	EXPECT_EQ(*it, "Halo");
}

TEST(IteratorOperatorsTest, EqualTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack("World!");
	auto it = list.begin();
	auto it1 = list.begin();
	EXPECT_TRUE(it == it1);
	auto it2 = ++list.begin();
	EXPECT_FALSE(it == it2);
	EXPECT_FALSE(it1 == it2);
}

TEST(IteratorOperatorsTest, NotEqualTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack("World!");
	auto it = list.begin();
	auto it1 = list.begin();
	EXPECT_FALSE(it != it1);
	auto it2 = ++list.begin();
	EXPECT_TRUE(it1 != it2);
	EXPECT_TRUE(it1 != it2);
}

TEST(StringListMethodsTest, InsertTest)
{
	CStringList list;
	auto it = list.begin();
	list.Insert(it, "Hello");
	EXPECT_EQ(*list.begin(), "Hello");
	EXPECT_EQ(list.GetSize(), 1);

	auto it1 = list.begin();
	list.Insert(it1, "World!");
	EXPECT_EQ(*list.begin(), "World!");
	EXPECT_EQ(list.GetSize(), 2);

	auto it2 = ++++list.begin();
	EXPECT_EQ(*list.Insert(it2, "123"), "123");
	EXPECT_EQ(*list.rbegin(), "123");
	EXPECT_EQ(list.GetSize(), 3);
}

TEST(StringListMethodsTest, EraseTest)
{
	CStringList list;
	list.PushBack("Halo");
	list.PushBack(", ");
	list.PushBack("World!");
	list.Erase(++list.begin());
	EXPECT_EQ(*list.begin(), "Halo");
	EXPECT_EQ(*++list.begin(), "World!");
	EXPECT_EQ(list.GetSize(), 2);

	list.Erase(++list.begin());
	EXPECT_EQ(*list.begin(), "Halo");
	EXPECT_EQ(list.GetSize(), 1);

	EXPECT_EQ(list.Erase(++list.begin()), nullptr);
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_EQ(*list.rbegin(), "Halo");

	list.Erase(list.begin());
	EXPECT_EQ(list.begin(), nullptr);
	EXPECT_EQ(list.rbegin(), nullptr);
	EXPECT_EQ(list.GetSize(), 0);
}

TEST(StringListMethodsTest, PushFrontTest)
{
	CStringList list;
	list.PushFront("Hello");
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_EQ(list.GetFrontElement(), "Hello");
	EXPECT_EQ(list.GetBackElement(), "Hello");
	list.PushFront(",");
	EXPECT_EQ(list.GetSize(), 2);
	EXPECT_EQ(list.GetFrontElement(), ",");
	EXPECT_EQ(list.GetBackElement(), "Hello");
	list.PushFront("World!");
	EXPECT_EQ(list.GetSize(), 3);
	EXPECT_EQ(list.GetFrontElement(), "World!");
	EXPECT_EQ(list.GetBackElement(), "Hello");
}

TEST(StringListMethodsTest, PushBackTest)
{
	CStringList list;
	list.PushBack("Hello");
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_EQ(list.GetBackElement(), "Hello");
	EXPECT_EQ(list.GetFrontElement(), "Hello");
	list.PushBack(",");
	EXPECT_EQ(list.GetSize(), 2);
	EXPECT_EQ(list.GetBackElement(), ",");
	EXPECT_EQ(list.GetFrontElement(), "Hello");
	list.PushBack("World!");
	EXPECT_EQ(list.GetSize(), 3);
	EXPECT_EQ(list.GetBackElement(), "World!");
	EXPECT_EQ(list.GetFrontElement(), "Hello");
}

TEST(StringListMethodsTest, CheckEmptyTest)
{
	CStringList list;
	EXPECT_TRUE(list.IsEmpty());
	list.PushBack("Hello");
	EXPECT_FALSE(list.IsEmpty());
	list.Clear();
	EXPECT_TRUE(list.IsEmpty());
}

TEST(StringListMethodsTest, ClearTest)
{
	CStringList list;
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_EQ(list.begin(), nullptr);
	EXPECT_EQ(list.rbegin(), nullptr);
	list.PushBack("Hello");
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_NE(list.begin(), nullptr);
	EXPECT_NE(list.rbegin(), nullptr);
	list.Clear();
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_EQ(list.begin(), nullptr);
	EXPECT_EQ(list.rbegin(), nullptr);
}

TEST(StringListOperatorsTest, AssignTest)
{
	CStringList list;
	CStringList other;
	list = other;
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_EQ(list.begin(), nullptr);
	EXPECT_EQ(list.rbegin(), nullptr);
	other.PushBack("Hello");
	other.PushBack(", ");
	other.PushBack("World!");
	list = other;
	EXPECT_EQ(list.GetSize(), 3);
	EXPECT_EQ(*list.begin(), "Hello");
	EXPECT_EQ(*list.rbegin(), "World!");

	CStringList list1 = std::move(list);
	EXPECT_EQ(list1.GetSize(), 3);
	EXPECT_EQ(*list1.begin(), "Hello");
	EXPECT_EQ(*list1.rbegin(), "World!");
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_EQ(list.begin(), nullptr);
	EXPECT_EQ(list.rbegin(), nullptr);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}