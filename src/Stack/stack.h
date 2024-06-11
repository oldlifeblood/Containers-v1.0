#ifndef STACK_H
#define STACK_H

#include "../List/list.h"

template <typename T>
class Stack {
 private:
  List<int> container;

 public:
  typedef std::size_t size_type;

  Stack() {}
  Stack(const std::initializer_list<T> &init_list) : container(init_list) {}
  Stack(const Stack<T> &other) : container(other.container) {}
  Stack(Stack<T> &&other) noexcept : container(std::move(other.container)) {}

  Stack &operator=(Stack other) {
    container = std::move(other.container);
    return *this;
  }

  size_type size() const { return container.size(); }

  bool empty() const { return container.empty(); }

  void push(const T &value) { container.push_back(value); }

  T pop() {
    if (empty()) throw std::out_of_range("Stack is empty");

    T value = container.back();
    container.pop_back();
    return value;
  }

  const T &top() const {
    if (empty()) throw std::out_of_range("Stack is empty");

    return container.back();
  }
};

#endif