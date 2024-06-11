#ifndef MAP_CC
#define MAP_CC

#include "map.h"

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::insert(std::shared_ptr<Node>& node,
                                         const KeyType& key,
                                         const ValueType& value) {
  auto z = std::make_shared<Node>(key, value);
  std::shared_ptr<Node> y = nullptr;
  auto x = node;
  while (x) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (!y)
    node = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  fixInsert(z);
}

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::fixInsert(std::shared_ptr<Node> z) {
  while (z->parent && z->parent->color == Color::RED) {
    if (z->parent == z->parent->parent->left) {
      auto y = z->parent->parent->right;
      if (y && y->color == Color::RED) {
        z->parent->color = Color::BLACK;
        y->color = Color::BLACK;
        z->parent->parent->color = Color::RED;
        z = z->parent->parent;
      } else {
        z->parent->color = Color::BLACK;
        z->parent->parent->color = Color::RED;
      }
    } else {
      auto y = z->parent->parent->left;
      if (z == z->parent->left) {
        z = z->parent;
      }
      z->parent->color = Color::BLACK;
      z->parent->parent->color = Color::RED;
      leftRotate(z->parent->parent);
    }
  }
  root->color = Color::BLACK;
}

template <typename KeyType, typename ValueType>
std::shared_ptr<typename s21_map<KeyType, ValueType>::Node>
s21_map<KeyType, ValueType>::find(std::shared_ptr<Node> node,
                                  const KeyType& key) const {
  if (!node || node->key == key) return node;
  if (key < node->key) return find(node->left, key);
  return find(node->right, key);
}

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::leftRotate(std::shared_ptr<Node> x) {
  auto y = x->right;
  x->right = y->left;
  if (y->left) y->left->parent = x;
  y->parent = x->parent;
  if (!x->parent)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::rightRotate(std::shared_ptr<Node> y) {
  auto x = y->left;
  y->left = x->right;
  if (x->right) x->right->parent = y;
  x->parent = y->parent;
  if (!y->parent)
    root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;
  x->right = y;
  y->parent = x;
}

template <typename KeyType, typename ValueType>
size_t s21_map<KeyType, ValueType>::getSize(
    const std::shared_ptr<Node>& node) const {
  if (!node) return 0;
  return getSize(node->left) + getSize(node->right) + 1;
}

template <typename KeyType, typename ValueType>
std::shared_ptr<typename s21_map<KeyType, ValueType>::Node>
s21_map<KeyType, ValueType>::minimum(std::shared_ptr<Node> node) const {
  while (node->left) node = node->left;
  return node;
}

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::transplant(std::shared_ptr<Node> u,
                                             std::shared_ptr<Node> v) {
  if (!u->parent)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v) v->parent = u->parent;
}

template <typename KeyType, typename ValueType>
bool s21_map<KeyType, ValueType>::isEqual(
    const std::shared_ptr<Node>& node1,
    const std::shared_ptr<Node>& node2) const {
  if (!node1 && !node2) return true;
  if (!node1 || !node2) return false;
  return node1->key == node2->key && node1->value == node2->value &&
         isEqual(node1->left, node2->left) &&
         isEqual(node1->right, node2->right);
}

template <typename KeyType, typename ValueType>
int s21_map<KeyType, ValueType>::isRedBlackTreeHelper(
    std::shared_ptr<Node> node) const {
  if (node == nullptr) {
    return 0;
  }

  int leftCount = isRedBlackTreeHelper(node->left);
  int rightCount = isRedBlackTreeHelper(node->right);

  if ((node->color == Color::RED) &&
      ((node->left != nullptr && node->left->color != Color::BLACK) ||
       (node->right != nullptr && node->right->color != Color::BLACK))) {
    return -1;
  }

  if (leftCount != -1 && rightCount != -1 && leftCount != rightCount) {
    return -1;
  }

  return (node->color == Color::BLACK) ? leftCount + 1 : leftCount;
}

template <typename KeyType, typename ValueType>
s21_map<KeyType, ValueType>::s21_map() : root(nullptr) {}

template <typename KeyType, typename ValueType>
std::shared_ptr<typename s21_map<KeyType, ValueType>::Node>
s21_map<KeyType, ValueType>::getRoot() const {
  return root;
}

template <typename KeyType, typename ValueType>
bool s21_map<KeyType, ValueType>::isRedBlackTree() const {
  if (root == nullptr || root->color != Color::BLACK) {
    return false;
  }
  return isRedBlackTreeHelper(root) != -1;
}

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::insert(const KeyType& key,
                                         const ValueType& value) {
  insert(root, key, value);
}

template <typename KeyType, typename ValueType>
const ValueType& s21_map<KeyType, ValueType>::at(const KeyType& key) const {
  auto node = find(root, key);
  if (!node) throw std::out_of_range("Key not found");
  return node->value;
}

template <typename KeyType, typename ValueType>
ValueType& s21_map<KeyType, ValueType>::operator[](const KeyType& key) {
  auto node = find(root, key);
  if (!node) {
    insert(key, ValueType());
    node = find(root, key);
  }
  return node->value;
}

template <typename KeyType, typename ValueType>
size_t s21_map<KeyType, ValueType>::size() const {
  return getSize(root);
}

template <typename KeyType, typename ValueType>
bool s21_map<KeyType, ValueType>::contains(const KeyType& key) const {
  return find(root, key) != nullptr;
}

template <typename KeyType, typename ValueType>
bool s21_map<KeyType, ValueType>::empty() const {
  return root == nullptr;
}

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::clear() {
  root = nullptr;
}

template <typename KeyType, typename ValueType>
void s21_map<KeyType, ValueType>::erase(const KeyType& key) {
  auto z = find(root, key);
  if (!z) return;
  auto y = z;
  std::shared_ptr<Node> x;
  if (!z->left) {
    x = z->right;
    transplant(z, z->right);
  } else if (!z->right) {
    x = z->left;
    transplant(z, z->left);
  }
}

template <typename KeyType, typename ValueType>
bool s21_map<KeyType, ValueType>::operator==(const s21_map& other) const {
  return isEqual(root, other.root);
}

template <typename KeyType, typename ValueType>
bool s21_map<KeyType, ValueType>::operator!=(const s21_map& other) const {
  return !(*this == other);
}

template <typename KeyType, typename ValueType>
typename s21_map<KeyType, ValueType>::iterator
s21_map<KeyType, ValueType>::begin() {
  if (!root) return iterator(nullptr, root);
  auto current = root;
  while (current->left) current = current->left;
  return iterator(current, root);
}

template <typename KeyType, typename ValueType>
typename s21_map<KeyType, ValueType>::iterator
s21_map<KeyType, ValueType>::end() {
  return iterator(nullptr, root);
}

template <typename KeyType, typename ValueType>
typename s21_map<KeyType, ValueType>::const_iterator
s21_map<KeyType, ValueType>::begin() const {
  if (!root) return const_iterator(nullptr, root);
  auto current = root;
  while (current->left) current = current->left;
  return const_iterator(current, root);
}

template <typename KeyType, typename ValueType>
typename s21_map<KeyType, ValueType>::const_iterator
s21_map<KeyType, ValueType>::end() const {
  return const_iterator(nullptr, root);
}

template <typename Key, typename T>
template <class... Args>
vector<std::pair<typename s21_map<Key, T>::iterator, bool>>
s21_map<Key, T>::insert_many(Args&&... args) {
  vector<std::pair<typename s21_map<Key, T>::iterator, bool>> vec;
  for (const auto& arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

#endif