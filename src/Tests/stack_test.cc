#include "../Stack/stack.h"

#include <gtest/gtest.h>

// Тест для конструктора по умолчанию
TEST(StackTest, DefaultConstructor) {
  Stack<int> stack;
  EXPECT_TRUE(stack.empty());
}

// Тест для конструктора с initializer_list
TEST(StackTest, InitializerListConstructor) {
  Stack<int> stack{1, 2, 3};
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.top(), 3);
}

// Тест для конструктора копирования
TEST(StackTest, CopyConstructor) {
  Stack<int> stack1{1, 2, 3};
  Stack<int> stack2(stack1);
  EXPECT_FALSE(stack2.empty());
  EXPECT_EQ(stack2.top(), 3);
  // Проверка, что изменения в stack2 не влияют на stack1
  stack2.pop();
  EXPECT_EQ(stack1.top(), 3);
}

// Тест для конструктора перемещения
TEST(StackTest, MoveConstructor) {
  Stack<int> stack1{1, 2, 3};
  Stack<int> stack2(std::move(stack1));
  EXPECT_TRUE(stack1.empty());  // stack1 должен быть пустым после перемещения
  EXPECT_FALSE(stack2.empty());
  EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, CopyAssignmentOperator) {
  Stack<int> s1{1, 2, 3};
  Stack<int> s2;
  s2 = s1;

  EXPECT_EQ(s1.top(), s2.top());
  s1.push(4);
  EXPECT_NE(s1.top(), s2.top());  // Проверка на глубокое копирование
}

TEST(StackTest, MoveAssignmentOperator) {
  Stack<int> s1{1, 2, 3};
  Stack<int> s2 = std::move(s1);

  EXPECT_EQ(3, s2.top());
}

TEST(StackTest, SelfAssignment) {
  Stack<int> s{1, 2, 3};

  EXPECT_EQ(3, s.top());
}

TEST(StackTest, SizeEmpty) {
  Stack<int> s;
  EXPECT_TRUE(s.empty());

  s.push(1);
  EXPECT_FALSE(s.empty());
}

TEST(StackTest, PushPop) {
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  EXPECT_EQ(s.pop(), 3);
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.pop(), 1);
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, Top) {
  Stack<int> s;
  s.push(1);
  s.push(2);

  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, PopEmptyThrows) {
  Stack<int> s;
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(StackTest, TopEmptyThrows) {
  Stack<int> s;
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(StackTest, PopFromEmpty) {
  Stack<int> stack;
  // Проверяем, выбрасывается ли исключение при попытке извлечь элемент из
  // пустого стека
  EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackTest, TopFromEmpty) {
  Stack<int> stack;
  // Проверяем, выбрасывается ли исключение при попытке получить верхний элемент
  // пустого стека
  EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(StackTest, SelfAssignment2) {
  Stack<int> stack = {1, 2, 3};
  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(stack.pop(), 3);
  EXPECT_EQ(stack.top(), 2);
}
