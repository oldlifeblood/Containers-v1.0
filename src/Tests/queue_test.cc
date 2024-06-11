#include "../Queue/queue.h"

#include <gtest/gtest.h>

TEST(QueueTest, DefaultConstructor) {
  Queue<int> q;
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, InitializerListConstructor) {
  Queue<int> q{1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor) {
  Queue<int> q1{1, 2, 3};
  Queue<int> q2(q1);
  EXPECT_EQ(q1.front(), q2.front());
  EXPECT_EQ(q1.back(), q2.back());
  // Modify q1 and ensure q2 remains unchanged
  q1.push(4);

  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, MoveConstructor) {
  Queue<int> q1{1, 2, 3};
  Queue<int> q2(std::move(q1));
  EXPECT_TRUE(q1.empty());  // q1 should be empty after move
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(IntQueueTest, AssignmentOperator) {
  Queue<int> q;
  Queue<int> q2 = {1, 2, 3};
  q = q2;
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

// Test the size method
TEST(StringQueueTest, Size) {
  Queue<std::string> q;
  q.push("hello");
  q.push("world");
}

// Test the empty method
TEST(IntQueueTest, Empty) {
  Queue<int> q;
  EXPECT_TRUE(q.empty());
  q.push(1);
  EXPECT_FALSE(q.empty());
}

// Test the push method
TEST(StringQueueTest, Push) {
  Queue<std::string> q;
  q.push("test");
  EXPECT_EQ(q.front(), "test");
}
