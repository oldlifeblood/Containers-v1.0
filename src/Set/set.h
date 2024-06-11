#ifndef SET_H
#define SET_H

#include <iostream>
#include <stdexcept>

#include "../RBTree/RedBlackTree.h"
#include "../Vector/vector.h"

namespace s21 {

template <typename T>
class s21_set {
 private:
  RedBlackTree<T> tree;

 public:
  s21_set();  // Конструктор по умолчанию

  void insert(const T& value);  // Вставка элемента в множество

  void erase(const T& value);  // Удаление элемента из множества

  bool contains(const T& value) const;  // Проверка наличия элемента в множестве

  void clear();  // Очистка множества

  bool empty() const;  // Проверка, является ли множество пустым

  size_t size() const;  // Получение размера множества

  size_t max_size() const;  // Получение максимального размера множества

  typename RedBlackTree<T>::iterator find(
      const T& value);  // Поиск элемента в множестве

  bool operator==(const s21_set& other) const;  // Оператор сравнения

  bool operator!=(const s21_set& other) const;  // Оператор неравенства

  class iterator;  // Объявление класса итератора

  iterator begin() const;  // Итератор начала множества

  iterator end() const;  // Итератор конца множества

  s21_set(const s21_set& other);  // Конструктор копирования

  s21_set(s21_set&& other) noexcept;  // Конструктор перемещения

  s21_set& operator=(const s21_set& other);  // Оператор присваивания

  s21_set& operator=(
      s21_set&& other) noexcept;  // Оператор присваивания с перемещением

  s21_set(std::initializer_list<T> init_list);  // Конструктор с инициализацией
                                                // из списка инициализаторов

  template <typename... Args>
  vector<std::pair<typename s21_set<T>::iterator, bool>> insert_many(
      Args&&... args);

  class iterator {
   private:
    typename RedBlackTree<T>::iterator iter;

   public:
    iterator(typename RedBlackTree<T>::iterator it) : iter(it) {}

    T& operator*() const { return *iter; }

    iterator& operator++() {
      ++iter;
      return *this;
    }

    bool operator==(const iterator& other) const { return iter == other.iter; }

    bool operator!=(const iterator& other) const { return !(*this == other); }
  };
};

}  // namespace s21

#include "set.cc"

#endif  // SET_H
