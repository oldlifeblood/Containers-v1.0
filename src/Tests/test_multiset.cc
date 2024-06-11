#include <gtest/gtest.h>

#include <random>
#include <set>

#include "../Multiset/multiset.h"

// Генератор случайных чисел
static std::mt19937 rng(std::random_device{}());

// Генерация случайного числа в заданном диапазоне [min, max]
static int random(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(rng);
}

// Тестирование конструктора копирования
TEST(MultisetTest, CopyConstructor) {
  s21::s21_multiset<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_multiset<int> copiedSet(originalSet);

  EXPECT_EQ(originalSet, copiedSet);
}

// Тестирование конструктора перемещения
TEST(MultisetTest, MoveConstructor) {
  s21::s21_multiset<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_multiset<int> movedSet(std::move(originalSet));

  EXPECT_TRUE(originalSet.empty());
}

// Тестирование оператора присваивания копирования
TEST(MultisetTest, CopyAssignmentOperator) {
  s21::s21_multiset<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_multiset<int> copiedSet;
  copiedSet = originalSet;

  EXPECT_EQ(originalSet, copiedSet);
}

// Тестирование оператора присваивания перемещения
TEST(MultisetTest, MoveAssignmentOperator) {
  s21::s21_multiset<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_multiset<int> movedSet;
  movedSet = std::move(originalSet);

  EXPECT_TRUE(originalSet.empty());
}

// Тестирование конструктора с инициализацией из списка инициализаторов
TEST(MultisetTest, InitializerListConstructor) {
  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  int randomValue3 = random(1, 100);
  s21::s21_multiset<int> mySet = {randomValue1, randomValue2, randomValue3};

  EXPECT_TRUE(mySet.contains(randomValue1));
  EXPECT_TRUE(mySet.contains(randomValue2));
  EXPECT_TRUE(mySet.contains(randomValue3));
}

// Тестирование вставки и проверки наличия элементов
TEST(MultisetTest, InsertAndContains) {
  s21::s21_multiset<int> mySet;
  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  int randomValue3 = random(1, 100);
  mySet.insert(randomValue1);
  mySet.insert(randomValue2);
  mySet.insert(randomValue3);

  EXPECT_TRUE(mySet.contains(randomValue1));
  EXPECT_TRUE(mySet.contains(randomValue2));
  EXPECT_TRUE(mySet.contains(randomValue3));
  EXPECT_FALSE(mySet.contains(random(101, 200)));
}

// Тестирование методов size и empty
TEST(MultisetTest, SizeAndEmpty) {
  s21::s21_multiset<int> mySet;
  EXPECT_TRUE(mySet.empty());

  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  mySet.insert(randomValue1);
  mySet.insert(randomValue2);

  EXPECT_FALSE(mySet.empty());
}

// Тестирование метода clear
TEST(MultisetTest, Clear) {
  s21::s21_multiset<int> mySet;
  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  mySet.insert(randomValue1);
  mySet.insert(randomValue2);

  mySet.clear();

  EXPECT_TRUE(mySet.empty());
}

// Тестирование итераторов
TEST(MultisetTest, Iterator) {
  s21::s21_multiset<int> mySet;
  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  int randomValue3 = random(1, 100);
  mySet.insert(randomValue1);
  mySet.insert(randomValue2);
  mySet.insert(randomValue3);

  std::multiset<int> expected = {randomValue1, randomValue2, randomValue3};
  std::multiset<int> result;
  for (const auto& elem : mySet) {
    result.insert(elem);
  }

  EXPECT_EQ(result, expected);
}

TEST(RedBlackTreeTest, LeftRotationAndColorChange) {
  RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);

  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));
}