#ifndef ARRAY_CC
#define ARRAY_CC

#include "array.h"
// Array Member functions //
template <typename T>
array<T>::array() : list(), size_array(0) {}

template <typename T>
array<T>::array(std::initializer_list<value_type> const &items) : list(items) {}

template <typename T>
array<T>::array(const array &a) : list(a.list) {}

template <typename T>
array<T>::array(array &&a) : list(std::move(a.list)) {}

template <typename T>
array<T>::~array() {
  list.~List();
}

template <typename T>
array<T> &array<T>::operator=(array &&a) {
  if (this != &a) {
    this->swap(a);
  }
  return *this;
}
// Array Member functions //
template <typename T>
typename array<T>::reference array<T>::at(size_type pos) {
  if (pos >= this->size()) {
    throw std::out_of_range("Index out of range");
  }
  return this->operator[](pos);
}

template <typename T>
typename array<T>::reference array<T>::operator[](size_t index) {
  if (index >= this->size()) {
    static T dummy;
    return dummy;
  }
  auto it = this->begin();
  std::advance(it, index);
  return *it;
}

template <typename T>
typename array<T>::const_reference array<T>::front() {
  if (this->empty()) {
    throw std::out_of_range("Array is empty");
  }
  return list.front();
}

template <typename T>
typename array<T>::const_reference array<T>::back() {
  if (this->empty()) {
    throw std::out_of_range("Array is empty");
  }
  return list.back();
}

template <typename T>
typename array<T>::iterator array<T>::data() {
  if (empty()) {
    return nullptr;
  } else {
    return &list[0];
  }
}
// Array Element access //

// Array Capacity //
template <typename T>
bool array<T>::empty() {
  return list.empty();
}

template <typename T>
size_t array<T>::size() {
  size_array = list.size();
  return list.size();
}

template <typename T>
size_t array<T>::max_size() {
  return list.max_size();
}
// Array Capacity //

// Array Modifiers //
template <typename T>
void array<T>::swap(array &other) {
  using std::swap;
  swap(list, other.list);
  swap(size_array, other.size_array);
}

template <typename T>
void array<T>::fill(const_reference value) {
  if (empty()) {
    throw std::logic_error("Trying to fill an empty array");
  }
  for (size_t i = 0; i < size(); ++i) {
    list[i] = value;
  }
}
// Array Modifiers //

#endif