#ifndef MAP_H
#define MAP_H

#include <memory>
#include <stdexcept>
#include <utility>

#include "../Vector/vector.h"

template <typename KeyType, typename ValueType>
class s21_map {
 private:
  enum class Color { RED, BLACK };

  struct Node {
    KeyType key;
    ValueType value;
    Color color;
    std::shared_ptr<Node> left, right, parent;

    Node(const KeyType& key, const ValueType& value)
        : key(key),
          value(value),
          color(Color::RED),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  std::shared_ptr<Node> root;

  void insert(std::shared_ptr<Node>& node, const KeyType& key,
              const ValueType& value);
  void fixInsert(std::shared_ptr<Node> z);
  std::shared_ptr<Node> find(std::shared_ptr<Node> node,
                             const KeyType& key) const;
  size_t getSize(const std::shared_ptr<Node>& node) const;
  std::shared_ptr<Node> minimum(std::shared_ptr<Node> node) const;
  void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);
  bool isEqual(const std::shared_ptr<Node>& node1,
               const std::shared_ptr<Node>& node2) const;
  int isRedBlackTreeHelper(std::shared_ptr<Node> node) const;

 public:
  s21_map();
  std::shared_ptr<Node> getRoot() const;
  bool isRedBlackTree() const;
  void insert(const KeyType& key, const ValueType& value);
  const ValueType& at(const KeyType& key) const;
  ValueType& operator[](const KeyType& key);
  size_t size() const;
  bool contains(const KeyType& key) const;
  bool empty() const;
  void clear();
  void erase(const KeyType& key);
  bool operator==(const s21_map& other) const;
  bool operator!=(const s21_map& other) const;
  void rightRotate(std::shared_ptr<Node> x);
  void leftRotate(std::shared_ptr<Node> x);

  class iterator;

  template <typename... Args>
  vector<std::pair<typename s21_map<KeyType, ValueType>::iterator, bool>>
  insert_many(Args&&... args);

  class iterator {
   private:
    std::shared_ptr<Node> current;
    std::shared_ptr<Node> root;

   public:
    iterator(std::shared_ptr<Node> curr, std::shared_ptr<Node> rt)
        : current(curr), root(rt) {}

    iterator& operator++() { return *this; }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

    std::pair<const KeyType&, ValueType&> operator*() const {
      return {current->key, current->value};
    }
  };

  class const_iterator;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
};

#include "map.cc"

#endif  // MAP_H
