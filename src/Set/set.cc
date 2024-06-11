#ifndef SET_CC
#define SET_CC

#include "set.h"

namespace s21 {

template <typename T>
s21_set<T>::s21_set() {}

template <typename T>
void s21_set<T>::insert(const T& value) {
  try {
    tree.insert(value);
  } catch (const std::exception& e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
  }
}

template <typename T>
void s21_set<T>::erase(const T& value) {
  tree.erase(value);
}

template <typename T>
bool s21_set<T>::contains(const T& value) const {
  return tree.contains(value);
}

template <typename T>
void s21_set<T>::clear() {
  tree.clear();
}

template <typename T>
bool s21_set<T>::empty() const {
  return tree.empty();
}

template <typename T>
size_t s21_set<T>::size() const {
  return tree.size();
}

template <typename T>
size_t s21_set<T>::max_size() const {
  return tree.max_size();
}

template <typename T>
typename RedBlackTree<T>::iterator s21_set<T>::find(const T& value) {
  return tree.find(value);
}

template <typename T>
bool s21_set<T>::operator==(const s21_set& other) const {
  return tree == other.tree;
}

template <typename T>
bool s21_set<T>::operator!=(const s21_set& other) const {
  return !(*this == other);
}

template <typename T>
typename s21_set<T>::iterator s21_set<T>::begin() const {
  return iterator(tree.begin());
}

template <typename T>
typename s21_set<T>::iterator s21_set<T>::end() const {
  return iterator(tree.end());
}

template <typename T>
s21_set<T>::s21_set(const s21_set& other) : tree(other.tree) {}

template <typename T>
s21_set<T>::s21_set(s21_set&& other) noexcept : tree(std::move(other.tree)) {}

template <typename T>
s21_set<T>& s21_set<T>::operator=(const s21_set& other) {
  if (this != &other) {
    tree = other.tree;
  }
  return *this;
}

template <typename T>
s21_set<T>& s21_set<T>::operator=(s21_set&& other) noexcept {
  if (this != &other) {
    tree = std::move(other.tree);
  }
  return *this;
}

template <typename T>
s21_set<T>::s21_set(std::initializer_list<T> init_list) : tree() {
  for (const auto& elem : init_list) {
    insert(elem);
  }
}

}  // namespace s21

template <typename T>
template <typename... Args>
vector<std::pair<typename s21::s21_set<T>::iterator, bool>>
s21::s21_set<T>::insert_many(Args&&... args) {
  vector<std::pair<typename s21::s21_set<T>::iterator, bool>> results;

  if constexpr (sizeof...(Args) == 0) {
    return results;
  }

  ((void)results.emplace_back(tree.insert(std::forward<Args>(args))), ...);

  return results;
}

#endif