#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <initializer_list>
#include <iostream>

#include "../List/list.h"

template <typename T>
class vector {
 public:
  // Vector Member type //
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::size_t size_type;
  // Vector Member type //

  // Vector Member functions //
  vector();
  vector(size_type n);
  vector(std::initializer_list<T> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();
  vector<T>& operator=(vector&& v);
  // Vector Member functions //

  // Vector Element access //
  reference at(size_type pos);
  reference operator[](size_t index);
  const_reference front();
  const_reference back();
  T* data();
  // Vector Element access //

  // Vector Iterators //
  class VectorIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VectorIterator(typename List<T>::iterator list_iterator)
        : list_iterator(list_iterator) {}

    reference operator*() const { return *list_iterator; }
    pointer operator->() const { return &(*list_iterator); }

    VectorIterator operator+(int n) const {
      VectorIterator result = *this;
      for (int i = 0; i < n; ++i) {
        ++result;
      }
      return result;
    }

    VectorIterator operator-(int n) const {
      VectorIterator result = *this;
      for (int i = 0; i < n; ++i) {
        --result;
      }
      return result;
    }

    VectorIterator& operator++() {
      ++list_iterator;
      return *this;
    }

    VectorIterator operator++(int) {
      VectorIterator temp = *this;
      ++(*this);
      return temp;
    }

    VectorIterator& operator--() {
      --list_iterator;
      return *this;
    }

    VectorIterator operator--(int) {
      VectorIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const VectorIterator& rhs) const {
      return list_iterator == rhs.list_iterator;
    }
    bool operator!=(const VectorIterator& rhs) const {
      return list_iterator != rhs.list_iterator;
    }

   private:
    typename List<T>::iterator list_iterator;
    friend class vector<T>;
  };
  VectorIterator begin() { return VectorIterator(list.begin()); }
  VectorIterator end() { return VectorIterator(list.end()); }

  // Vector Iterators //

  // Vector Capacity //
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  // Vector Capacity //

  // Vector Modifiers //
  void clear();
  VectorIterator insert(VectorIterator pos, const_reference value);
  void erase(VectorIterator pos);
  void pop_back();
  void push_back(const_reference value);
  void swap(vector& other);
  // Vector Modifiers //

  // Bonus: insert_many
  template <typename... Args>
  typename vector<T>::iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);
  // Bonus: insert_many

 private:
  List<T> list;
  size_type vector_capacity;
};
#include "vector.cc"
#endif