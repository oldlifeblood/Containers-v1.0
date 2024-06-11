#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>

template <typename T>
class RedBlackTree {
 private:
  enum class Color { RED, BLACK };

  struct Node {
    T data;
    Color color;
    std::shared_ptr<Node> left, right, parent;

    explicit Node(const T& data)
        : data(data),
          color(Color::RED),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  std::shared_ptr<Node> root;

  void leftRotate(std::shared_ptr<Node> x);
  void rightRotate(std::shared_ptr<Node> y);
  void fixInsert(std::shared_ptr<Node> z);
  int isRedBlackTreeHelper(std::shared_ptr<Node> node) const;
  std::shared_ptr<Node> find(std::shared_ptr<Node> node, const T& value) const;
  size_t getSize(const std::shared_ptr<Node>& node) const;

 public:
  bool isRedBlackTree() const;

  RedBlackTree();
  RedBlackTree(std::initializer_list<T> init_list);

  void insert(const T& value);
  void erase(const T& key);
  bool contains(const T& value) const;
  T find(const T& value);
  void clear();
  bool empty() const;
  size_t size() const;
  size_t max_size() const;
  void swap(RedBlackTree& other);
  bool operator==(const RedBlackTree& other) const;
  T GetMin() const;
  T GetMax() const;
  std::shared_ptr<Node> getMinNode(std::shared_ptr<Node> node) const;
  std::shared_ptr<Node> getMaxNode(std::shared_ptr<Node> node) const;

 public:
  class iterator {
   private:
    std::shared_ptr<Node> current;

   public:
    iterator(std::shared_ptr<Node> node);
    T& operator*() const;
    iterator& operator++();
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
  };

  iterator begin() const;
  iterator end() const;

 public:
  class const_iterator {
   private:
    std::shared_ptr<const Node> current;

   public:
    const_iterator(std::shared_ptr<const Node> node);
    const T& operator*() const;
    const_iterator& operator++();
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
  };

  const_iterator cbegin() const;
  const_iterator cend() const;

 public:
#include "RedBlackTree.h"
};

#endif  // RED_BLACK_TREE_H
