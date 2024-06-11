#ifndef VECTOR_CC
#define VECTOR_CC

#include "vector.h"

// Vector Member functions //
template <typename T>
vector<T>::vector() : list(), vector_capacity(0) {}

template <typename T>
vector<T>::vector(size_type n) : vector_capacity(n) {
  for (size_type i = 0; i < n; ++i) {
    this->push_back(T());
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const& items) : list(items) {}

template <typename T>
vector<T>::vector(const vector& v) : list(v.list) {}

template <typename T>
vector<T>::vector(vector&& v) : list(std::move(v.list)) {}

template <typename T>
vector<T>::~vector() {
  list.~List();
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) {
  if (this != &v) {
    this->swap(v);
  }
  return *this;
}
// Vector Member functions //

// Vector Element access //
template <typename T>
typename vector<T>::reference vector<T>::operator[](size_t index) {
  if (index >= this->size()) {
    static T dummy;
    return dummy;
  }
  auto it = this->begin();
  std::advance(it, index);
  return *it;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= this->size()) {
    throw std::out_of_range("Index out of range");
  }
  return this->operator[](pos);
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return list.front();
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return list.back();
}

template <typename T>
T* vector<T>::data() {
  if (this->empty()) {
    return nullptr;
  } else {
    T* array = new T[this->size()];
    size_t i = 0;
    for (const auto& item : list) {
      array[i++] = item;
    }
    return array;
  }
}
// Vector Element access //

// Vector Capacity //
template <typename T>
bool vector<T>::empty() {
  return list.empty();
}

template <typename T>
size_t vector<T>::size() {
  return list.size();
}

template <typename T>
size_t vector<T>::max_size() {
  return list.max_size();
}

template <typename T>
void vector<T>::reserve(size_t new_capacity) {
  if (new_capacity <= vector_capacity) {
    return;
  }
  T* new_data = new T[new_capacity];
  auto it = this->begin();
  size_t i = 0;
  for (; it != this->end(); ++it, ++i) {
    new_data[i] = *it;
  }
  delete[] this->data();
  this->clear();
  for (size_t j = 0; j < i; ++j) {
    this->push_back(new_data[j]);
  }
  vector_capacity = new_capacity;
  delete[] new_data;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return vector_capacity;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (this->empty()) {
    delete[] this->data();
    vector_capacity = 0;
  } else {
    T* new_data = new T[this->size()];
    auto it = this->begin();
    size_t i = 0;
    for (; it != this->end(); ++it, ++i) {
      new_data[i] = *it;
    }
    delete[] this->data();
    this->clear();
    for (size_t j = 0; j < i; ++j) {
      this->push_back(new_data[j]);
    }
    vector_capacity = this->size();
    delete[] new_data;
  }
}
// Vector Capacity //

// Vector Modifiers //
template <typename T>
void vector<T>::clear() {
  list.clear();
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::insert(VectorIterator pos,
                                                     const_reference value) {
  return VectorIterator(list.insert(pos.list_iterator, value));
}

template <typename T>
void vector<T>::erase(VectorIterator pos) {
  list.erase(pos.list_iterator);
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (this->size() == capacity()) {
    this->reserve(capacity() == 0 ? 1 : capacity() * 2);
  }
  list.push_back(value);
}

template <typename T>
void vector<T>::pop_back() {
  if (this->empty()) {
    throw std::out_of_range("pop_back() called on an empty vector");
  }
  list.pop_back();
}

template <typename T>
void vector<T>::swap(vector& other) {
  using std::swap;
  swap(list, other.list);
  swap(vector_capacity, other.vector_capacity);
}
// Vector Modifiers //

// Bonus: insert_many
template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  list.insert_many_back(std::forward<Args>(args)...);
}
// Bonus: insert_many

#endif