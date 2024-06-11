#ifndef LIST_CPP
#define LIST_CPP

#include "list.h"

// default constructor
template <typename T>
List<T>::List() : Size(0) {
  head = tail = nullptr;
}

// parameterized constructor
template <typename T>
List<T>::List(size_type n) : Size(0) {
  head = tail = nullptr;
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

// initializer list constructor
template <typename T>
List<T>::List(std::initializer_list<T> const &items) {
  head = tail = nullptr;
  Size = 0;
  for (auto const &item : items) {
    push_back(item);
  }
}

// copy constructor
template <typename T>
List<T>::List(const List &l) : Size(0) {
  head = tail = nullptr;
  for (Node *node = l.head; node; node = node->next) {
    push_back(node->data);
  }
}

// move constructor
template <typename T>
List<T>::List(List &&l) noexcept : List() {
  swap(*this, l);
  l.clear();
}

// move operator=
template <typename T>
List<T> &List<T>::operator=(List<T> &&list) {
  swap(*this, list);
  list.clear();
  return *this;
}

// operator[]
template <typename T>
T &List<T>::operator[](int count) {
  iterator temp = this->begin();
  for (int i = 0; i < count; i++) {
    temp++;
  }
  Node *node = temp.current;
  return node->data;
}

template <typename T>
T &List<T>::operator[](int count) const {
  iterator temp = this->begin();
  for (int i = 0; i < count; i++) {
    temp++;
  }
  Node *node = temp.current;
  return node->data;
}

template <typename T>
void List<T>::sort() {
  int n = Size;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if ((*this)[j] > (*this)[j + 1]) {
        T temp = (*this)[j];
        (*this)[j] = (*this)[j + 1];
        (*this)[j + 1] = temp;
      }
    }
  }
}

template <typename T>
void List<T>::unique() {
  if (head == nullptr || head->next == nullptr) {
    return;
  }
  Node *current = head;
  while (current->next != nullptr) {
    if (current->data == current->next->data) {
      Node *temp = current->next;
      current->next = temp->next;
      if (temp->next != nullptr) {
        temp->next->previous = current;
      } else {
        tail = current;
      }
      delete temp;
      Size--;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void List<T>::reverse() {
  if (head == nullptr || head == tail) {
    return;
  }

  Node *current_node = head;
  while (current_node != nullptr) {
    Node temp_node = *current_node;

    current_node->previous = temp_node.next;
    current_node->next = temp_node.previous;

    current_node = current_node->previous;
  }
  std::swap(head, tail);
}

// Destructor
template <typename T>
List<T>::~List() {
  clear();
}

template <typename T>
typename List<T>::size_type List<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
const T &List<T>::front() const {
  if (head != nullptr)
    return head->data;
  else
    throw std::out_of_range("List is empty");
}

template <typename T>
const T &List<T>::back() const {
  if (tail != nullptr)
    return tail->data;
  else
    throw std::out_of_range("List is empty");
}

template <typename T>
bool List<T>::empty() const {
  if (Size == 0) return true;
  return false;
}

template <typename T>
size_t List<T>::size() const {
  return Size;
}

template <typename T>
void List<T>::clear() {
  while (head != nullptr) pop_front();
}

template <typename T>
void List<T>::pop_front() {
  if (head == nullptr) return;

  if (head == tail) tail = nullptr;

  Node *temp = head;
  head = head->next;
  if (Size != 1) head->previous = nullptr;
  delete temp;
  Size--;
}

template <typename T>
void List<T>::pop_back() {
  if (head == nullptr) return;

  if (head == tail) head = nullptr;

  Node *temp = tail;
  tail = tail->previous;
  if (Size != 1) tail->next = nullptr;
  delete temp;
  Size--;
}

template <typename T>
void List<T>::push_front(T data) {
  if (head == nullptr) {
    addFirstNode(data);
    return;
  }

  Node *newNode = new Node(data);
  newNode->next = head;
  newNode->previous = nullptr;
  head->previous = newNode;
  head = newNode;
  Size++;
}

template <typename T>
void List<T>::push_back(T data) {
  if (head == nullptr) {
    addFirstNode(data);
    return;
  }
  Node *newNode = new Node(data);
  newNode->previous = tail;
  tail->next = newNode;
  tail = newNode;
  Size++;
}

template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator pos,
                                           const_reference value) {
  if (pos.current == nullptr) {
    push_back(value);
    return iterator(tail, tail);
  } else if (pos.current == head) {
    push_front(value);
    return iterator(head, tail);
  } else {
    Node *newNode = new Node(value);
    newNode->next = pos.current;
    newNode->previous = pos.current->previous;
    pos.current->previous->next = newNode;
    pos.current->previous = newNode;
    Size++;
    return iterator(newNode, tail);
  }
}

template <typename T>
void List<T>::erase(List<T>::iterator position) {
  if (position.current == nullptr) {
    return;
  }

  if (position.current == head) {
    pop_front();
  } else if (position.current == tail) {
    pop_back();
  } else {
    position.current->previous->next = position.current->next;
    position.current->next->previous = position.current->previous;
    delete position.current;
    this->Size--;
  }
}

template <typename T>
void List<T>::merge(List &other) {
  if (this->empty()) {
    *this = std::move(other);
    return;
  }

  if (!other.empty()) {
    this->tail->next = other.head;
    other.head->previous = this->tail;
    this->tail = other.tail;
    this->Size += other.Size;
  }

  other.head = nullptr;
  other.tail = nullptr;
  other.Size = 0;
}

template <typename T>
void List<T>::addFirstNode(T data) {
  head = new Node(data);
  tail = head;
  Size = 1;
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_back(Args &&...args) {
  if constexpr (sizeof...(args) > 0) {
    (void)std::initializer_list<int>{
        (push_back(std::forward<Args>(args)), 0)...};
  }
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_front(Args &&...args) {
  if constexpr (sizeof...(args) > 0) {
    (void)std::initializer_list<int>{
        (push_front(std::forward<Args>(args)), 0)...};
  }
}

#endif