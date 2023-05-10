#ifndef __S21__MAP__H__
#define __S21__MAP__H__

#ifndef __S21__TREE__H__
#include "Tree.h"
#endif

namespace s21 {
template <typename Key, typename T, typename Comp = std::less<Key>>
class Map : public BinaryTree<Key, T, std::pair<const Key, T>, Comp> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, T, value_type, Comp>::Iterator;
  using const_iterator =
      typename BinaryTree<Key, T, value_type, Comp>::ConstIterator;
  using size_type = std::size_t;
  Map() : BinaryTree<Key, T, value_type, Comp>(){};
  Map(std::initializer_list<value_type> const& items)
      : BinaryTree<Key, T, value_type, Comp>(items){};
  Map(const Map& s) : BinaryTree<Key, T, value_type, Comp>(s){};
  Map(Map&& s) : BinaryTree<Key, T, value_type, Comp>(std::move(s)){};

  Map& operator=(Map&& s);
  Map& operator=(const Map& v);

  T& at(const Key& key);
  T& operator[](const Key& key);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  std::pair<iterator, bool> insert(const value_type& key);
};

template <typename Key, typename T, typename Comp>
Map<Key, T, Comp>& Map<Key, T, Comp>::operator=(Map&& v) {
  this->del(this->root);
  this->mv(v);

  return *this;
};

template <typename Key, typename T, typename Comp>
Map<Key, T, Comp>& Map<Key, T, Comp>::operator=(const Map& v) {
  this->cpy(v);
  return *this;
}

template <typename Key, typename T, typename Comp>
T& Map<Key, T, Comp>::at(const Key& key) {
  if (!this->contains(key)) {
    throw std::out_of_range("s21::Map::at");
  }
  auto it = this->find(key);
  return it.m_ptr->val.second;
}

template <typename Key, typename T, typename Comp>
T& Map<Key, T, Comp>::operator[](const Key& key) {
  if (!this->contains(key)) {
    BinaryTree<Key, T, value_type, Comp>::insert({key, T{}});
  }
  auto it = this->find(key);
  return it.m_ptr->val.second;
}

template <typename Key, typename T, typename Comp>
std::pair<typename Map<Key, T, Comp>::iterator, bool> Map<Key, T, Comp>::insert(
    const Key& key, const T& obj) {
  return BinaryTree<Key, T, value_type, Comp>::insert({key, obj});
}

template <typename Key, typename T, typename Comp>
std::pair<typename Map<Key, T, Comp>::iterator, bool> Map<Key, T, Comp>::insert(
    const value_type& key) {
  return BinaryTree<Key, T, value_type, Comp>::insert(key);
}

template <typename Key, typename T, typename Comp>
std::pair<typename Map<Key, T, Comp>::iterator, bool>
Map<Key, T, Comp>::insert_or_assign(const Key& key, const T& obj) {
  bool f = this->contains(key) ? false : true;
  this->operator[](key) = obj;
  return std::make_pair(this->find(key), f);
}

}  // namespace s21

#endif  // __S21__MAP__H__