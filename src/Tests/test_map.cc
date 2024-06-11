#include <gtest/gtest.h>

#include <map>
#include <random>

#include "../Map/map.h"
#include "../RBTree/RedBlackTree.h"

// Функция для генерации случайного ключа
int generateRandomKey() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<int> dist(1, 1000);
  return dist(gen);
}

// Функция для генерации случайной строки
std::string generateRandomValue() {
  static const char charset[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  static std::uniform_int_distribution<int> dist(0, sizeof(charset) - 2);
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> length(1, 10);

  std::string result(length(gen), '\0');
  for (auto& c : result) {
    c = charset[dist(gen)];
  }
  return result;
}

TEST(s21_mapTest, InsertAndAccess) {
  s21_map<int, std::string> myMap;
  std::map<int, std::string> stdMap;

  int key = generateRandomKey();
  std::string value = generateRandomValue();

  myMap.insert(key, value);
  stdMap.insert({key, value});

  ASSERT_EQ(myMap.size(), stdMap.size());
  ASSERT_EQ(myMap[key], stdMap[key]);
}

TEST(s21_mapTest, Erase) {
  s21_map<int, std::string> myMap;
  std::map<int, std::string> stdMap;

  int key1 = generateRandomKey();
  std::string value1 = generateRandomValue();
  int key2 = generateRandomKey();
  std::string value2 = generateRandomValue();

  myMap.insert(key1, value1);
  myMap.insert(key2, value2);
  stdMap.insert({key1, value1});
  stdMap.insert({key2, value2});

  myMap.erase(key1);
  stdMap.erase(key1);

  ASSERT_EQ(myMap.size(), stdMap.size());
  ASSERT_FALSE(myMap.contains(key1));
  ASSERT_TRUE(myMap.contains(key2));
}

TEST(s21_mapTest, AccessNonExistentKey) {
  s21_map<int, std::string> myMap;
  std::map<int, std::string> stdMap;

  int key = generateRandomKey();
  std::string value = generateRandomValue();

  stdMap[key] = value;

  ASSERT_THROW(myMap.at(generateRandomKey()), std::out_of_range);
  ASSERT_THROW(stdMap.at(generateRandomKey()), std::out_of_range);
}

TEST(s21_mapTest, Clear) {
  s21_map<int, std::string> myMap;
  std::map<int, std::string> stdMap;

  int key1 = generateRandomKey();
  std::string value1 = generateRandomValue();
  int key2 = generateRandomKey();
  std::string value2 = generateRandomValue();

  myMap.insert(key1, value1);
  myMap.insert(key2, value2);
  stdMap.insert({key1, value1});
  stdMap.insert({key2, value2});

  myMap.clear();
  stdMap.clear();

  ASSERT_TRUE(myMap.empty());
  ASSERT_TRUE(stdMap.empty());
}

TEST(s21_mapTest, CopyConstructorAndAssignmentOperator) {
  s21_map<int, std::string> myMap;
  int key1 = generateRandomKey();
  std::string value1 = generateRandomValue();
  int key2 = generateRandomKey();
  std::string value2 = generateRandomValue();

  myMap.insert(key1, value1);
  myMap.insert(key2, value2);

  s21_map<int, std::string> copiedMap(myMap);
  ASSERT_EQ(copiedMap.size(), myMap.size());
  ASSERT_EQ(copiedMap[key1], myMap[key1]);
  ASSERT_EQ(copiedMap[key2], myMap[key2]);

  s21_map<int, std::string> assignedMap;
  assignedMap = myMap;
  ASSERT_EQ(assignedMap.size(), myMap.size());
  ASSERT_EQ(assignedMap[key1], myMap[key1]);
  ASSERT_EQ(assignedMap[key2], myMap[key2]);
}

TEST(s21_mapTest, MoveConstructorAndAssignmentOperator) {
  s21_map<int, std::string> myMap;
  int key1 = generateRandomKey();
  std::string value1 = generateRandomValue();
  int key2 = generateRandomKey();
  std::string value2 = generateRandomValue();

  myMap.insert(key1, value1);
  myMap.insert(key2, value2);

  s21_map<int, std::string> movedMap(std::move(myMap));
  ASSERT_EQ(static_cast<int>(movedMap.size()), 2);
  ASSERT_EQ(movedMap[key1], value1);
  ASSERT_EQ(movedMap[key2], value2);

  ASSERT_TRUE(myMap.empty());

  s21_map<int, std::string> anotherMap;
  anotherMap = std::move(movedMap);
  ASSERT_EQ(static_cast<int>(anotherMap.size()), 2);
  ASSERT_EQ(anotherMap[key1], value1);
  ASSERT_EQ(anotherMap[key2], value2);

  ASSERT_TRUE(movedMap.empty());
}

TEST(s21_mapTest, Contains) {
  s21_map<int, std::string> myMap;
  int key1 = generateRandomKey();
  std::string value1 = generateRandomValue();
  int key2 = generateRandomKey();
  std::string value2 = generateRandomValue();

  myMap.insert(key1, value1);
  myMap.insert(key2, value2);

  ASSERT_TRUE(myMap.contains(key1));
  ASSERT_TRUE(myMap.contains(key2));
  ASSERT_FALSE(myMap.contains(generateRandomKey()));
}

TEST(s21_mapTest, Size) {
  s21_map<int, std::string> myMap;
  ASSERT_EQ(static_cast<int>(myMap.size()), 0);

  int key1 = generateRandomKey();
  std::string value1 = generateRandomValue();
  int key2 = generateRandomKey();
  std::string value2 = generateRandomValue();

  myMap.insert(key1, value1);
  ASSERT_EQ(static_cast<int>(myMap.size()), 1);

  myMap.insert(key2, value2);
  ASSERT_EQ(static_cast<int>(myMap.size()), 2);

  myMap.erase(key1);
  ASSERT_EQ(static_cast<int>(myMap.size()), 1);

  myMap.clear();
  ASSERT_EQ(static_cast<int>(myMap.size()), 0);
}

TEST(s21_mapTest, RedBlackTreeProperties) {
  s21_map<int, std::string> myMap;

  myMap.insert(10, "A");
  myMap.insert(20, "B");
  myMap.insert(30, "C");
  myMap.insert(15, "D");
  myMap.insert(25, "E");

  ASSERT_TRUE(myMap.isRedBlackTree());
}

TEST(RedBlackTreeTest, RightChildAndRedUncle) {
  RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(20);

  tree.insert(1);

  ASSERT_TRUE(tree.isRedBlackTree());
}

TEST(RedBlackTreeTest, RightRotateParentIsRightChild) {
  RedBlackTree<int> tree;

  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);

  tree.insert(6);
  tree.insert(7);

  EXPECT_TRUE(tree.isRedBlackTree());
}

TEST(RedBlackTreeTest, RightRotateParentIsLeftChild) {
  RedBlackTree<int> tree;

  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(1);

  tree.insert(6);
  tree.insert(5);

  EXPECT_TRUE(tree.isRedBlackTree());
}

TEST(RedBlackTreeTest, RightRotateRoot) {
  RedBlackTree<int> tree;

  tree.insert(5);
  tree.insert(3);
  tree.insert(7);

  tree.insert(6);
  tree.insert(7);

  EXPECT_TRUE(tree.isRedBlackTree());
}