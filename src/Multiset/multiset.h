#ifndef MULTISET_H
#define MULTISET_H

#include <iostream>
#include <stdexcept>

#include "../RBTree/RedBlackTree.h"
#include "../Vector/vector.h"

namespace s21 {

template <typename T>
class s21_multiset {
 private:
  RedBlackTree<T> tree;

 public:
  // Объявление класса итератора
  class iterator;

  s21_multiset();

  void insert(const T& value);

  void erase(const T& value);

  bool contains(const T& value) const;

  void clear();

  bool empty() const;

  size_t size() const;

  size_t max_size() const;

  typename RedBlackTree<T>::iterator find(const T& value);

  bool operator==(const s21_multiset& other) const;

  bool operator!=(const s21_multiset& other) const;

  typename RedBlackTree<T>::iterator begin() const;

  typename RedBlackTree<T>::iterator end() const;

  s21_multiset(const s21_multiset& other);

  s21_multiset(s21_multiset&& other) noexcept;

  s21_multiset& operator=(const s21_multiset& other);

  s21_multiset& operator=(s21_multiset&& other) noexcept;

  template <typename... Args>
  vector<std::pair<typename s21_multiset<T>::iterator, bool>> insert_many(
      Args&&... args);

  s21_multiset(std::initializer_list<T> init_list);
};

// Определение класса итератора внутри класса s21_multiset
template <typename T>
class s21_multiset<T>::iterator {
 private:
  typename RedBlackTree<T>::iterator iter;

 public:
  iterator(typename RedBlackTree<T>::iterator it) : iter(it) {}

  T& operator*() const { return *iter; }

  iterator& operator++() {
    ++iter;
    return *this;
  }

  bool operator==(const iterator& other) const { return iter == other.iter; }

  bool operator!=(const iterator& other) const { return !(*this == other); }
};

}  // namespace s21

#include "multiset.cc"

#endif  // MULTISET_H
