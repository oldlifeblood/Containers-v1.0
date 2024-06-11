#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <initializer_list>
#include <iostream>

#include "../List/list.h"

template <typename T>
class array {
 public:
  // Array Member type //
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::size_t size_type;
  // Array Member type //

  // Array Member functions //
  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& a);
  array(array&& a);
  ~array();
  array<T>& operator=(array&& a);
  // Array Member functions //

  // Array Element access //
  reference at(size_type pos);
  reference operator[](size_t index);
  const_reference front();
  const_reference back();
  iterator data();
  // Array Element access //

  // Array Iterators //
  typename List<T>::iterator begin() { return list.begin(); }
  typename List<T>::iterator end() { return list.end(); }
  // Array Iterators //

  // Array Capacity //
  bool empty();
  size_type size();
  size_type max_size();
  // Array Capacity //

  // Array Modifiers //
  void swap(array& other);
  void fill(const_reference value);
  // Array Modifiers //

 private:
  List<T> list;
  size_type size_array;
};
#include "array.cc"
#endif