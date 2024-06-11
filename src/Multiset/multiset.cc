#ifndef MULTISET_CC
#define MULTISET_CC

#include "multiset.h"

namespace s21 {

template <typename T>
s21_multiset<T>::s21_multiset() {}

template <typename T>
void s21_multiset<T>::insert(const T& value) {
  tree.insert(value);
}

template <typename T>
void s21_multiset<T>::erase(const T& value) {
  tree.erase(value);
}

template <typename T>
bool s21_multiset<T>::contains(const T& value) const {
  return tree.contains(value);
}

template <typename T>
void s21_multiset<T>::clear() {
  tree.clear();
}

template <typename T>
bool s21_multiset<T>::empty() const {
  return tree.empty();
}

template <typename T>
size_t s21_multiset<T>::size() const {
  return tree.size();
}

template <typename T>
size_t s21_multiset<T>::max_size() const {
  return tree.max_size();
}

template <typename T>
typename RedBlackTree<T>::iterator s21_multiset<T>::find(const T& value) {
  return tree.find(value);
}

template <typename T>
bool s21_multiset<T>::operator==(const s21_multiset& other) const {
  // Сравниваем размеры множеств
  if (size() != other.size()) {
    return false;
  }

  auto it1 = begin();
  auto it2 = other.begin();
  while (it1 != end() && it2 != other.end()) {
    if (*it1 != *it2) {
      return false;
    }
    ++it1;
    ++it2;
  }

  return (it1 == end() && it2 == other.end());
}

template <typename T>
bool s21_multiset<T>::operator!=(const s21_multiset& other) const {
  return !(*this == other);
}

template <typename T>
typename RedBlackTree<T>::iterator s21_multiset<T>::begin() const {
  return tree.begin();
}

template <typename T>
typename RedBlackTree<T>::iterator s21_multiset<T>::end() const {
  return tree.end();
}

template <typename T>
s21_multiset<T>::s21_multiset(const s21_multiset& other) : tree(other.tree) {}

template <typename T>
s21_multiset<T>::s21_multiset(s21_multiset&& other) noexcept
    : tree(std::move(other.tree)) {}

template <typename T>
s21_multiset<T>& s21_multiset<T>::operator=(const s21_multiset& other) {
  if (this != &other) {
    tree = other.tree;
  }
  return *this;
}

template <typename T>
s21_multiset<T>& s21_multiset<T>::operator=(s21_multiset&& other) noexcept {
  if (this != &other) {
    tree = std::move(other.tree);
  }
  return *this;
}

template <typename T>
template <typename... Args>
vector<std::pair<typename s21_multiset<T>::iterator, bool>>
s21_multiset<T>::insert_many(Args&&... args) {
  vector<std::pair<typename s21_multiset<T>::iterator, bool>> results;

  ((void)results.emplace_back(tree.insert(std::forward<Args>(args))), ...);

  return results;
}

template <typename T>
s21_multiset<T>::s21_multiset(std::initializer_list<T> init_list)
    : tree(init_list) {}

}  // namespace s21

#endif