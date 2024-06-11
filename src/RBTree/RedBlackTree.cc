#ifndef RBT_CC
#define RBT_CC

#include "RedBlackTree.h"

template <typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr) {}

template <typename T>
RedBlackTree<T>::RedBlackTree(std::initializer_list<T> init_list)
    : root(nullptr) {
  for (const T& value : init_list) {
    insert(value);
  }
}

template <typename T>
void RedBlackTree<T>::leftRotate(std::shared_ptr<Node> x) {
  std::shared_ptr<Node> y = x->right;
  x->right = y->left;
  if (y->left != nullptr) y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rightRotate(std::shared_ptr<Node> y) {
  std::shared_ptr<Node> x = y->left;
  y->left = x->right;
  if (x->right != nullptr) x->right->parent = y;
  x->parent = y->parent;
  if (y->parent == nullptr)
    root = x;
  else if (y == y->parent->right)
    y->parent->right = x;
  else
    y->parent->left = x;
  x->right = y;
  y->parent = x;
}

template <typename T>
void RedBlackTree<T>::fixInsert(std::shared_ptr<Node> newNode) {
  while (newNode->parent && newNode->parent->color == Color::RED) {
    if (newNode->parent == newNode->parent->parent->left) {
      auto uncle = newNode->parent->parent->right;
      if (uncle && uncle->color == Color::RED) {
        newNode->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        newNode->parent->parent->color = Color::RED;
        newNode = newNode->parent->parent;
      } else {
        if (newNode == newNode->parent->right) {
          newNode = newNode->parent;
          leftRotate(newNode);
        }
        newNode->parent->color = Color::BLACK;
        newNode->parent->parent->color = Color::RED;
        rightRotate(newNode->parent->parent);
      }
    } else {
      auto uncle = newNode->parent->parent->left;
      if (uncle && uncle->color == Color::RED) {
        newNode->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        newNode->parent->parent->color = Color::RED;
        newNode = newNode->parent->parent;
      } else {
        if (newNode == newNode->parent->left) {
          newNode = newNode->parent;
          rightRotate(newNode);
        }
        newNode->parent->color = Color::BLACK;
        newNode->parent->parent->color = Color::RED;
        leftRotate(newNode->parent->parent);
      }
    }
  }
  root->color = Color::BLACK;
}

template <typename T>
std::shared_ptr<typename RedBlackTree<T>::Node> RedBlackTree<T>::find(
    std::shared_ptr<Node> node, const T& value) const {
  if (!node || node->data == value) return node;
  if (value < node->data) return find(node->left, value);
  return find(node->right, value);
}

template <typename T>
size_t RedBlackTree<T>::getSize(const std::shared_ptr<Node>& node) const {
  if (!node) return 0;
  return getSize(node->left) + getSize(node->right) + 1;
}

template <typename T>
void RedBlackTree<T>::insert(const T& value) {
  auto newNode = std::make_shared<Node>(value);
  std::shared_ptr<Node> parent = nullptr;
  auto currentNode = root;
  while (currentNode) {
    parent = currentNode;
    if (newNode->data < currentNode->data)
      currentNode = currentNode->left;
    else
      currentNode = currentNode->right;
  }
  newNode->parent = parent;
  if (!parent)
    root = newNode;
  else if (newNode->data < parent->data)
    parent->left = newNode;
  else
    parent->right = newNode;
  fixInsert(newNode);
}

template <typename T>
bool RedBlackTree<T>::isRedBlackTree() const {
  return isRedBlackTreeHelper(root) >= 0;
}

template <typename T>
int RedBlackTree<T>::isRedBlackTreeHelper(std::shared_ptr<Node> node) const {
  if (!node) return 1;

  if (node->color == Color::RED) {
    if (node->left && node->left->color == Color::RED) return -1;
    if (node->right && node->right->color == Color::RED) return -1;
  }

  int leftBlackHeight = isRedBlackTreeHelper(node->left);
  int rightBlackHeight = isRedBlackTreeHelper(node->right);

  if (leftBlackHeight < 0 || rightBlackHeight < 0) return -1;

  if (leftBlackHeight != rightBlackHeight) return -1;

  return leftBlackHeight + (node->color == Color::BLACK ? 1 : 0);
}

template <typename T>
void RedBlackTree<T>::erase(const T& key) {
  auto z = find(root, key);
  if (!z || z->data != key) {
    return;
  }

  std::shared_ptr<Node> y, x;
  if (!z->left || !z->right) {
    y = z;
  } else {
    y = getMinNode(z->right);
  }

  if (y->left) {
    x = y->left;
  } else {
    x = y->right;
  }

  if (x) {
    x->parent = y->parent;
  }

  if (!y->parent) {
    root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  if (y != z) {
    z->data = y->data;
  }
}

template <typename T>
bool RedBlackTree<T>::contains(const T& value) const {
  return find(root, value) != nullptr;
}

template <typename T>
T RedBlackTree<T>::find(const T& value) {
  auto node = find(root, value);
  if (node)
    return node->data;
  else
    throw std::runtime_error("Element not found");
}

template <typename T>
void RedBlackTree<T>::clear() {
  root = nullptr;
}

template <typename T>
bool RedBlackTree<T>::empty() const {
  return !root;
}

template <typename T>
size_t RedBlackTree<T>::size() const {
  return getSize(root);
}

template <typename T>
size_t RedBlackTree<T>::max_size() const {
  return std::numeric_limits<size_t>::max();
}

template <typename T>
void RedBlackTree<T>::swap(RedBlackTree& other) {
  std::swap(root, other.root);
}

template <typename T>
bool RedBlackTree<T>::operator==(const RedBlackTree& other) const {
  return root == other.root;
}

template <typename T>
T RedBlackTree<T>::GetMin() const {
  auto current = root;
  while (current && current->left) current = current->left;
  if (!current) throw std::runtime_error("Tree is empty");
  return current->data;
}

template <typename T>
T RedBlackTree<T>::GetMax() const {
  auto current = root;
  while (current && current->right) current = current->right;
  if (!current) throw std::runtime_error("Tree is empty");
  return current->data;
}

template <typename T>
std::shared_ptr<typename RedBlackTree<T>::Node> RedBlackTree<T>::getMinNode(
    std::shared_ptr<Node> node) const {
  while (node && node->left) node = node->left;
  return node;
}

template <typename T>
std::shared_ptr<typename RedBlackTree<T>::Node> RedBlackTree<T>::getMaxNode(
    std::shared_ptr<Node> node) const {
  while (node && node->right) node = node->right;
  return node;
}

template <typename T>
RedBlackTree<T>::iterator::iterator(std::shared_ptr<Node> node)
    : current(node) {}

template <typename T>
T& RedBlackTree<T>::iterator::operator*() const {
  return current->data;
}

template <typename T>
typename RedBlackTree<T>::iterator& RedBlackTree<T>::iterator::operator++() {
  if (!current) return *this;
  if (current->right) {
    current = current->right;
    while (current->left) current = current->left;
  } else {
    auto parent = current->parent;
    while (parent && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename T>
bool RedBlackTree<T>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename T>
bool RedBlackTree<T>::iterator::operator!=(const iterator& other) const {
  return !(*this == other);
}

template <typename T>
typename RedBlackTree<T>::iterator RedBlackTree<T>::begin() const {
  auto node = root;
  while (node && node->left) node = node->left;
  return iterator(node);
}

template <typename T>
typename RedBlackTree<T>::iterator RedBlackTree<T>::end() const {
  return iterator(nullptr);
}

template <typename T>
RedBlackTree<T>::const_iterator::const_iterator(
    std::shared_ptr<const Node> node)
    : current(node) {}

template <typename T>
const T& RedBlackTree<T>::const_iterator::operator*() const {
  return current->data;
}

template <typename T>
typename RedBlackTree<T>::const_iterator&
RedBlackTree<T>::const_iterator::operator++() {
  if (!current) return *this;
  if (current->right) {
    current = current->right;
    while (current->left) current = current->left;
  } else {
    auto parent = current->parent;
    while (parent && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename T>
bool RedBlackTree<T>::const_iterator::operator==(
    const const_iterator& other) const {
  return current == other.current;
}

template <typename T>
bool RedBlackTree<T>::const_iterator::operator!=(
    const const_iterator& other) const {
  return !(*this == other);
}

template <typename T>
typename RedBlackTree<T>::const_iterator RedBlackTree<T>::cbegin() const {
  auto node = root;
  while (node && node->left) node = node->left;
  return const_iterator(node);
}

template <typename T>
typename RedBlackTree<T>::const_iterator RedBlackTree<T>::cend() const {
  return const_iterator(nullptr);
}

template class RedBlackTree<int>;

#endif