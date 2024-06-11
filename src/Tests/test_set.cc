#include <gtest/gtest.h>

#include <random>
#include <set>

#include "../RBTree/RedBlackTree.h"
#include "../Set/set.h"

// Генератор случайных чисел
std::mt19937 rng(std::random_device{}());

// Генерация случайного числа в заданном диапазоне [min, max]
int random(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(rng);
}

// Тестирование конструктора копирования
TEST(SetTest, CopyConstructor) {
  s21::s21_set<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_set<int> copiedSet(originalSet);

  EXPECT_EQ(originalSet, copiedSet);
}

// Тестирование конструктора перемещения
TEST(SetTest, MoveConstructor) {
  s21::s21_set<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_set<int> movedSet(std::move(originalSet));

  EXPECT_EQ(static_cast<int>(movedSet.size()), 3);
  EXPECT_TRUE(originalSet.empty());
}

// Тестирование оператора присваивания копирования
TEST(SetTest, CopyAssignmentOperator) {
  s21::s21_set<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_set<int> copiedSet;
  copiedSet = originalSet;

  EXPECT_EQ(originalSet, copiedSet);
}

// Тестирование оператора присваивания перемещения
TEST(SetTest, MoveAssignmentOperator) {
  s21::s21_set<int> originalSet;
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));
  originalSet.insert(random(1, 100));

  s21::s21_set<int> movedSet;
  movedSet = std::move(originalSet);

  EXPECT_TRUE(originalSet.empty());
}

// Тестирование конструктора с инициализацией из списка инициализаторов
TEST(SetTest, InitializerListConstructor) {
  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  int randomValue3 = random(1, 100);
  s21::s21_set<int> mySet = {randomValue1, randomValue2, randomValue3};

  EXPECT_TRUE(mySet.contains(randomValue1));
  EXPECT_TRUE(mySet.contains(randomValue2));
  EXPECT_TRUE(mySet.contains(randomValue3));
}

// Тестирование вставки и проверки наличия элементов
TEST(SetTest, InsertAndContains) {
  s21::s21_set<int> mySet;
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

// Тестирование удаления элемента
TEST(SetTest, Erase) {
  s21::s21_set<int> mySet;
  int Value1 = 10;
  int Value2 = 0;
  int Value3 = -7;
  mySet.insert(Value1);
  mySet.insert(Value2);
  mySet.insert(Value3);

  mySet.erase(Value2);

  EXPECT_TRUE(mySet.contains(Value1));
  EXPECT_FALSE(mySet.contains(Value2));
  EXPECT_TRUE(mySet.contains(Value3));
}

// Тестирование методов size и empty
TEST(SetTest, SizeAndEmpty) {
  s21::s21_set<int> mySet;
  EXPECT_TRUE(mySet.empty());

  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  mySet.insert(randomValue1);
  mySet.insert(randomValue2);

  EXPECT_FALSE(mySet.empty());
}

// Тестирование метода clear
TEST(SetTest, Clear) {
  s21::s21_set<int> mySet;
  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  mySet.insert(randomValue1);
  mySet.insert(randomValue2);

  mySet.clear();

  EXPECT_TRUE(mySet.empty());
}

// Тестирование итераторов
TEST(SetTest, Iterator) {
  s21::s21_set<int> mySet;
  int randomValue1 = random(1, 100);
  int randomValue2 = random(1, 100);
  int randomValue3 = random(1, 100);
  mySet.insert(randomValue1);
  mySet.insert(randomValue2);
  mySet.insert(randomValue3);

  std::set<int> expected = {randomValue1, randomValue2, randomValue3};
  std::set<int> result;
  for (const auto& elem : mySet) {
    result.insert(elem);
  }

  EXPECT_EQ(result, expected);
}

// тесты дерева

// Тест для метода GetMin
TEST(RedBlackTreeTest, GetMin) {
  RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(20);

  EXPECT_EQ(tree.GetMin(), 3);
}

// Тест для метода GetMax
TEST(RedBlackTreeTest, GetMax) {
  RedBlackTree<int> tree;
  // Добавляем элементы для создания дерева
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(20);

  EXPECT_EQ(tree.GetMax(), 20);
}

// Тест для метода RecursiveInsert
TEST(RedBlackTreeTest, RecursiveInsert) {
  RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(20);

  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(15));
}

// Тест для метода RecursiveDelete
TEST(RedBlackTreeTest, RecursiveDelete) {
  RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(20);

  tree.erase(12);
  EXPECT_FALSE(tree.contains(12));
}

// Тест для методов cbegin() и cend()
TEST(RedBlackTreeTest, Iterator) {
  RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(20);

  std::set<int> expected = {3, 5, 7, 10, 12, 15, 20};
  std::set<int> result;
  for (auto it = tree.cbegin(); it != tree.cend(); ++it) {
    result.insert(*it);
  }

  EXPECT_EQ(result, expected);
}

// Тест для конструктора с инициализацией из списка инициализаторов
TEST(RedBlackTreeTest, InitializerListConstructor) {
  RedBlackTree<int> tree = {10, 5, 15, 3, 7, 12, 20};

  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(15));
  EXPECT_TRUE(tree.contains(3));
  EXPECT_TRUE(tree.contains(7));
  EXPECT_TRUE(tree.contains(12));
  EXPECT_TRUE(tree.contains(20));
}

// Тестирование метода max_size
TEST(RedBlackTreeTest, MaxSize) {
  RedBlackTree<int> tree;
  EXPECT_EQ(tree.max_size(), std::numeric_limits<size_t>::max());
}

// Тестирование метода swap
TEST(RedBlackTreeTest, Swap) {
  RedBlackTree<int> tree1, tree2;
  tree1.insert(1);
  tree1.insert(2);
  tree1.insert(3);

  tree2.insert(4);
  tree2.insert(5);
  tree2.insert(6);

  tree1.swap(tree2);

  // Проверяем, что содержимое деревьев поменялось после вызова swap
  EXPECT_TRUE(tree1.contains(4));
  EXPECT_TRUE(tree1.contains(5));
  EXPECT_TRUE(tree1.contains(6));
  EXPECT_FALSE(tree1.contains(1));
  EXPECT_FALSE(tree1.contains(2));
  EXPECT_FALSE(tree1.contains(3));

  EXPECT_TRUE(tree2.contains(1));
  EXPECT_TRUE(tree2.contains(2));
  EXPECT_TRUE(tree2.contains(3));
  EXPECT_FALSE(tree2.contains(4));
  EXPECT_FALSE(tree2.contains(5));
  EXPECT_FALSE(tree2.contains(6));
}

// Тестирование метода find
TEST(RedBlackTreeTest, Find) {
  RedBlackTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);

  EXPECT_EQ(tree.find(5), 5);
  EXPECT_EQ(tree.find(3), 3);
  EXPECT_EQ(tree.find(7), 7);
  EXPECT_EQ(tree.find(2), 2);
  EXPECT_EQ(tree.find(4), 4);
  EXPECT_EQ(tree.find(6), 6);
  EXPECT_EQ(tree.find(8), 8);

  EXPECT_THROW(tree.find(10), std::runtime_error);
  EXPECT_THROW(tree.find(1), std::runtime_error);
  EXPECT_THROW(tree.find(0), std::runtime_error);
}
