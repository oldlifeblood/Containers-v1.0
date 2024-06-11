#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>

template <typename T>
class vector;

template <typename T>
class array;

template <typename T>
class List {
 public:
  using const_reference = const T &;

  typedef std::size_t size_type;

  List();                                       // Default constructor
  List(size_type n);                            // parameterized constructor
  List(std::initializer_list<T> const &items);  // initializer list constructor
  List(const List &l);                          // copy constructor
  List(List &&l) noexcept;                      // move constructor
  ~List();                                      // Destructor

 private:
  friend class vector<T>;
  friend class array<T>;
  // Node Struct
  struct Node {
    T data;
    Node *next;
    Node *previous;
    Node(T val) : data(val), next(nullptr), previous(nullptr) {}
  };

  // Iterators
  class iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    iterator(Node *node, Node *tail) : current(node), tail_(tail) {}

    reference operator*() const { return current->data; }
    pointer operator->() const { return &(current->data); }

    iterator &operator++() {
      current = current->next;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    iterator &operator--() {
      if (current == nullptr) {
        current = tail_;
      } else {
        current = current->previous;
      }
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const iterator &other) const {
      return current == other.current;
    }
    bool operator!=(const iterator &other) const { return !(*this == other); }

    Node *current;

   private:
    Node *tail_;
  };

 public:
  class const_iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;    // Pointer to const T
    using reference = const T &;  // Reference to const T

    const_iterator(Node *node, Node *tail) : current(node), tail_(tail) {}
    reference operator*() const { return current->data; }
    pointer operator->() const { return &(current->data); }

    iterator &operator++() {
      current = current->next;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    iterator &operator--() {
      if (current == nullptr) {
        current = tail_;
      } else {
        current = current->previous;
      }
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const iterator &other) const {
      return current == other.current;
    }
    bool operator!=(const iterator &other) const { return !(*this == other); }

    Node *current;

   private:
    Node *tail_;
  };

 public:
  // Accessors
  const T &front() const;  // access the first element
  const T &back() const;   // access the last element

  // Operators
  List<T> &operator=(List &&l);
  T &operator[](int count);
  T &operator[](int count) const;

  // List Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size();

  // List modifiers
  void clear();
  typename List<T>::iterator insert(
      typename List<T>::iterator pos,
      const_reference value);  // inserts element into concrete pos
  void erase(typename List<T>::iterator pos);  // erases element at pos
  void merge(List &other);                     // merges two sorted lists
  void sort();                                 // sorts the elements
  void unique();            // removes consecutive duplicate elements
  void pop_front();         // adds an element to the head
  void pop_back();          // removes the last element
  void push_front(T data);  // adds an element to the head
  void push_back(T data);   // adds an element to the end
  void reverse();           // reverses the order of the elements

  // Bonus: insert_many
  template <typename... Args>
  typename List<T>::iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);

  friend void swap(List &first, List &second) {
    std::swap(first.head, second.head);
    std::swap(first.tail, second.tail);
    std::swap(first.Size, second.Size);
  }

 private:
  Node *tail;
  Node *head;
  size_type Size;

  void addFirstNode(T data);

 public:
  iterator begin() { return iterator(head, tail); }
  iterator end() { return iterator(nullptr, tail); }
};

#include "list.cc"

#endif