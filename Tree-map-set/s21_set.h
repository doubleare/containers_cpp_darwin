#ifndef __S21__SET__H__
#define __S21__SET__H__

#ifndef __S21__TREE__H__
#include "Tree.h"
#endif

namespace s21 {
template <typename Key, typename Comp = std::less<Key>>
class Set : public BinaryTree<Key, Key, Key, Comp> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, Key, Key, Comp>::Iterator;
  using const_iterator =
      typename BinaryTree<Key, Key, Key, Comp>::ConstIterator;
  using size_type = std::size_t;

  Set() : BinaryTree<Key, Key, Key, Comp>(){};
  Set(std::initializer_list<value_type> const &items)
      : BinaryTree<Key, Key, Key, Comp>(items){};
  Set(const Set &s) : BinaryTree<Key, Key, Key, Comp>(s){};
  Set(Set &&s) : BinaryTree<Key, Key, Key, Comp>(std::move(s)){};

  Set &operator=(Set &&s);
  Set &operator=(const Set &v);

  iterator find(const_reference key);
};

template <typename Key, typename Comp>
Set<Key, Comp> &Set<Key, Comp>::operator=(const Set &v) {
  this->cpy(v);
  return *this;
}

template <typename Key, typename Comp>
Set<Key, Comp> &Set<Key, Comp>::operator=(Set &&v) {
  this->del(this->root);
  this->mv(v);

  return *this;
};

template <typename Key, typename Comp>
typename Set<Key, Comp>::iterator Set<Key, Comp>::find(const_reference key) {
  return BinaryTree<Key, Key, Key, Comp>::find(key);
}
}  // namespace s21

#endif  // __S21__SET__H__