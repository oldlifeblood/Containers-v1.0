#ifndef QUEUE_H
#define QUEUE_H

#include "../List/list.h"

template <typename T>
class Queue {
 private:
  List<T> container;

 public:
  typedef std::size_t size_type;

  Queue() {}
  Queue(const std::initializer_list<T>& init_list) : container(init_list) {}
  Queue(const Queue<T>& other) : container(other.container) {}
  Queue(Queue<T>&& other) noexcept : container(std::move(other.container)) {}

  Queue& operator=(Queue other) {
    container = std::move(other.container);
    return *this;
  }

  size_type size() const { return container.size(); }

  bool empty() const { return container.empty(); }

  void push(const T& value) { container.push_back(value); }

  T pop() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    T value = container.front();
    container.pop_front();
    return value;
  }

  const T& front() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return container.front();
  }

  const T& back() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return container.back();
  }

  void swap(Queue& other) noexcept { container.swap(other.container); }
};

#endif