#include "../List/list.h"

#include <gtest/gtest.h>

TEST(ListTest, DefaultConstructor) {
  List<int> list;
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, InitializerListConstructor) {
  List<int> list = {1, 2, 3};
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, SizeConstructor) {
  List<int> list(5);
  // Check if all elements are initialized to default value (0 for int)
  for (int i : list) {
    EXPECT_EQ(i, 0);
  }
}

// Test copy constructor
TEST(ListTest, CopyConstructor) {
  List<int> list1 = {1, 2, 3};
  List<int> list2(list1);
  EXPECT_EQ(list1.front(), list2.front());
  EXPECT_EQ(list1.back(), list2.back());
  // Modify list2 and check if list1 remains unchanged
  list2.push_back(4);
}

// Test move constructor
TEST(ListTest, MoveConstructor) {
  List<int> list1 = {1, 2, 3};
  List<int> list2(std::move(list1));
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 3);
}

// Test accessors front() and back()
TEST(ListTest, Accessors) {
  List<int> list = {1, 2, 3};
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
  list.push_front(0);
  list.push_back(4);
  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(list.back(), 4);
}

// Test capacity functions: empty, size, max_size
TEST(ListTest, Capacity) {
  List<int> list;
  EXPECT_TRUE(list.empty());
  list.push_back(1);
  EXPECT_FALSE(list.empty());
}

// Test clear function
TEST(ListTest, Clear) {
  List<int> list = {1, 2, 3};
  list.clear();
  EXPECT_TRUE(list.empty());
}

// Test pop_front
TEST(ListTest, PopFront) {
  List<int> list = {1, 2, 3};
  list.pop_front();
  EXPECT_EQ(list.front(), 2);
  list.pop_front();
  EXPECT_EQ(list.front(), 3);
}

// Test pop_back
TEST(ListTest, PopBack) {
  List<int> list = {1, 2, 3};
  list.pop_back();
  EXPECT_EQ(list.back(), 2);
  list.pop_back();
  EXPECT_EQ(list.back(), 1);
}

// Test push_front
TEST(ListTest, PushFront) {
  List<int> list;
  list.push_front(1);
  EXPECT_EQ(list.front(), 1);
  list.push_front(2);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 1);
}

// Test push_back
TEST(ListTest, PushBack) {
  List<int> list;
  list.push_back(1);
  EXPECT_EQ(list.back(), 1);
  list.push_back(2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

// Test inserting at the beginning
TEST(ListTest, InsertAtBeginning) {
  List<int> list = {2, 3, 4};
  auto it = list.begin();
  list.insert(it, 1);

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(*(++list.begin()), 2);
}

// Test inserting in the middle
TEST(ListTest, InsertInMiddle) {
  List<int> list = {1, 4};
  auto it = ++list.begin();  // Iterator pointing to the second element
  list.insert(it, 2);

  EXPECT_EQ(*(++list.begin()), 2);
}

// Test inserting at the end
TEST(ListTest, InsertAtEnd) {
  List<int> list = {1, 2, 3};
  auto it = list.end();
  list.insert(it, 4);

  EXPECT_EQ(list.back(), 4);
}

// Test erase for the first element
TEST(ListTest, EraseFirst) {
  List<int> list = {1, 2, 3};
  auto it = list.begin();
  list.erase(it);

  EXPECT_EQ(list.front(), 2);
}

// Test erase for an element in the middle
TEST(ListTest, EraseMiddle) {
  List<int> list = {1, 2, 3, 4};
  auto it = ++(++list.begin());  // Iterator pointing to the third element
  list.erase(it);

  EXPECT_EQ(*(++list.begin()), 2);
  EXPECT_EQ(*(++(++list.begin())), 4);
}

// Test erase for the last element
TEST(ListTest, EraseLast) {
  List<int> list = {1, 2, 3};
  auto it = --list.end();
  list.erase(it);

  EXPECT_EQ(list.back(), 2);
}

// Test erasing from an empty list (should do nothing)
TEST(ListTest, EraseEmpty) {
  List<int> list;
  auto it = list.begin();
  list.erase(it);

  EXPECT_TRUE(list.empty());
}

TEST(ListTest, ReverseEmptyList) {
  List<int> list;
  list.reverse();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, ReverseSingleElementList) {
  List<int> list;
  list.push_back(1);
  list.reverse();
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, ReverseMultipleElementList) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.reverse();
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, MergeSort_EmptyList) {
  List<int> list;
  list.sort();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, MergeSort_SingleElement) {
  List<int> list;
  list.push_back(1);
  list.sort();
  EXPECT_EQ(list[0], 1);
}

TEST(ListTest, MergeSort_SortedList) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.sort();
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
}

TEST(ListTest, MergeSort_UnsortedList) {
  List<int> list;
  list.push_back(3);
  list.push_back(1);
  list.push_back(4);
  list.push_back(2);
  list.sort();
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
  EXPECT_EQ(list[3], 4);
}

TEST(ListTest, UniqueEmptyList) {
  List<int> l;
  l.unique();
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, UniqueSingleElementList) {
  List<int> l{1};
  l.unique();
  EXPECT_EQ(l.front(), 1);
}

TEST(ListTest, UniqueNoDuplicates) {
  List<int> l{1, 2, 3, 4, 5};
  l.unique();
  EXPECT_EQ(l[0], 1);
  EXPECT_EQ(l[1], 2);
  EXPECT_EQ(l[2], 3);
  EXPECT_EQ(l[3], 4);
  EXPECT_EQ(l[4], 5);
}

TEST(ListTest, UniqueWithDuplicates) {
  List<int> l{1, 1, 2, 2, 3, 3};
  l.unique();
  EXPECT_EQ(l[0], 1);
  EXPECT_EQ(l[1], 2);
  EXPECT_EQ(l[2], 3);
}

TEST(ListTest, UniqueWithDuplicatesAtBeginning) {
  List<int> l{1, 1, 1, 2, 3};
  l.unique();
  EXPECT_EQ(l[0], 1);
  EXPECT_EQ(l[1], 2);
  EXPECT_EQ(l[2], 3);
}

TEST(ListTest, UniqueWithDuplicatesAtEnd) {
  List<int> l{1, 2, 3, 3, 3};
  l.unique();
  EXPECT_EQ(l[0], 1);
  EXPECT_EQ(l[1], 2);
  EXPECT_EQ(l[2], 3);
}

TEST(ListTest, UniqueWithAllDuplicates) {
  List<int> l{1, 1, 1, 1};
  l.unique();
  EXPECT_EQ(l[0], 1);
}

TEST(ListTest, InsertManyBackEmptyList) {
  List<int> list;
  list.insert_many_back(1, 2, 3);

  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
}

TEST(ListTest, InsertManyFrontEmptyList) {
  List<int> list;
  list.insert_many_front(1, 2, 3);

  EXPECT_EQ(list[0], 3);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 1);
}

TEST(ListTest, InsertManyBack_EmptyList) {
  List<int> list;
  list.insert_many_back(1, 2, 3, 4, 5);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 5);
}

TEST(ListTest, InsertManyBack_ExistingList) {
  List<int> list{10, 20};
  list.insert_many_back(30, 40, 50);
  EXPECT_EQ(list.front(), 10);
  EXPECT_EQ(list.back(), 50);
}

TEST(ListTest, InsertManyBack_DifferentTypes) {
  List<std::string> list{"hello"};
  list.insert_many_back("world", "!", "testing");
  EXPECT_EQ(list.front(), "hello");
  EXPECT_EQ(list.back(), "testing");
}

TEST(ListTest, InsertManyBack_NoArguments) {
  List<int> list{1, 2, 3};
  list.insert_many_back();
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

// TEST(ListTest, InsertManyBack_InitializerList) {
//   List<int> list;
//   list.insert_many_back({1, 2}, {4, 5, 6});
//   //, 6);
//   EXPECT_EQ(list.front(), 1);
//   EXPECT_EQ(list.back(), 6);
// }

TEST(ListTest, InsertManyFront_EmptyList) {
  List<int> list;
  list.insert_many_front(1, 2, 3, 4, 5);
  EXPECT_EQ(list.front(), 5);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, InsertManyFront_ExistingList) {
  List<int> list{10, 20};
  list.insert_many_front(30, 40, 50);
  EXPECT_EQ(list.front(), 50);
  EXPECT_EQ(list.back(), 20);
}

TEST(ListTest, InsertManyFront_DifferentTypes) {
  List<std::string> list{"hello"};
  list.insert_many_front("world", "!", "testing");
  EXPECT_EQ(list.front(), "testing");
  EXPECT_EQ(list.back(), "hello");
}

TEST(ListTest, InsertManyFront_NoArguments) {
  List<int> list{1, 2, 3};
  list.insert_many_front();  // Should not modify the list
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

// TEST(ListTest, InsertManyFront_InitializerList) {
//   List<int> list;
//   list.insert_many_front({1, 2}, 3, {4, 5, 6});
//   //, 6);
//   EXPECT_EQ(list.front(), 6);
//   EXPECT_EQ(list.back(), 1);
// }