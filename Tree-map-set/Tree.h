#ifndef __S21__TREE__H__
#define __S21__TREE__H__

#include <initializer_list>
#include <iostream>
#include <utility>

#include "tree_Node.h"

namespace s21 {

template <class Key, class M, class T, typename Comp>
class BinaryTree {
 public:
  BinaryTree();
  BinaryTree(std::initializer_list<T> const& items);
  BinaryTree(const BinaryTree& s);
  BinaryTree(BinaryTree&& s);
  ~BinaryTree();

  using n_ptr = Node<Key, M, T, Comp>*;

#include "Tree_iterator.h"

  size_t size();
  size_t max_size();
  bool empty();
  bool contains(const Key& key);

  void clear();
  void erase(Iterator pos);
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);

  std::pair<typename BinaryTree<Key, M, T, Comp>::Iterator, bool> insert(
      const T& new_val);
  Iterator begin();
  Iterator end();
  ConstIterator cbegin() const;
  ConstIterator cend() const;

 protected:
  Node<Key, M, T, Comp>* root;
  size_t m_size;

  Iterator find(const Key& key);
  void mv(BinaryTree& s);
  void cpy(const BinaryTree& s);
  void del(n_ptr par);
  std::pair<typename BinaryTree<Key, M, T, Comp>::Iterator, bool> add_node(
      Node<Key, M, T, Comp>* n);

 private:
  bool contains(std::pair<Key, M> key);
  void add_to_emt(n_ptr n_e);
  void add_to_end(n_ptr n_e);
  void erase_no_del(const Iterator pos);
  void erase_last(const Iterator pos);
};

template <typename Key, typename M, typename T, typename Comp>
BinaryTree<Key, M, T, Comp>::BinaryTree(std::initializer_list<T> const& items)
    : m_size(0) {
  root = new Node<Key, M, T, Comp>{};
  for (auto it = items.begin(); it != items.end(); it++) {
    this->insert(*it);
  }
};

template <typename Key, typename M, typename T, typename Comp>
BinaryTree<Key, M, T, Comp>::BinaryTree(const BinaryTree<Key, M, T, Comp>& s)
    : m_size(0) {
  root = new Node<Key, M, T, Comp>{};
  cpy(s);
};

template <typename Key, typename M, typename T, typename Comp>
BinaryTree<Key, M, T, Comp>::BinaryTree(BinaryTree&& s) : m_size(0) {
  root = new Node<Key, M, T, Comp>{};
  mv(s);
};

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::mv(BinaryTree<Key, M, T, Comp>& s) {
  delete this->root;
  this->root = s.root;
  this->m_size = s.m_size;

  s.root = new Node<Key, M, T, Comp>{};
  s.m_size = 0;
};

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::cpy(const BinaryTree<Key, M, T, Comp>& s) {
  clear();
  if (s.m_size) {
    for (auto it = s.cbegin(); it != s.cend(); it++) {
      this->insert(*it);
    }
  }
};

template <typename Key, typename M, typename T, typename Comp>
BinaryTree<Key, M, T, Comp>::BinaryTree() : m_size(0) {
  root = new Node<Key, M, T, Comp>{};
}

template <typename Key, typename M, typename T, typename Comp>
BinaryTree<Key, M, T, Comp>::~BinaryTree() {
  this->clear();
  delete root;
}

template <typename Key, typename M, typename T, typename Comp>
typename BinaryTree<Key, M, T, Comp>::Iterator
BinaryTree<Key, M, T, Comp>::begin() {
  return Iterator(root->to_right_left_par(LEFT));
}

template <typename Key, typename M, typename T, typename Comp>
typename BinaryTree<Key, M, T, Comp>::Iterator
BinaryTree<Key, M, T, Comp>::end() {
  return Iterator(root->to_right_left_par(RIGHT));
}

template <typename Key, typename M, typename T, typename Comp>
typename BinaryTree<Key, M, T, Comp>::ConstIterator
BinaryTree<Key, M, T, Comp>::cbegin() const {
  return ConstIterator(root->to_right_left_par(LEFT));
}

template <typename Key, typename M, typename T, typename Comp>
typename BinaryTree<Key, M, T, Comp>::ConstIterator
BinaryTree<Key, M, T, Comp>::cend() const {
  return ConstIterator(root->to_right_left_par(RIGHT));
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::del(n_ptr par) {
  if (par != nullptr && m_size) {
    del(par->right);
    del(par->left);
    delete par->right;
    delete par->left;
    par->right = par->left = nullptr;
  }
}

template <typename Key, typename M, typename T, typename Comp>
bool BinaryTree<Key, M, T, Comp>::empty() {
  return !(m_size > 0);
}

template <typename Key, typename M, typename T, typename Comp>
size_t BinaryTree<Key, M, T, Comp>::size() {
  return m_size;
}

template <typename Key, typename M, typename T, typename Comp>
size_t BinaryTree<Key, M, T, Comp>::max_size() {
  return (SIZE_MAX / sizeof(Node<Key, M, T, Comp>)) / 2;
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::clear() {
  this->del(root);
  this->m_size = 0;
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::erase_no_del(const Iterator pos) {
  n_ptr tmp = pos.m_ptr;

  if (m_size && this->end() != pos) {
    if (--this->end() == pos) {
      erase_last(pos);
    } else if (tmp->left == nullptr && tmp->right == nullptr) {
      tmp->parent_ptr();
    } else if (tmp->left != nullptr && tmp->right != nullptr) {
      n_ptr t = tmp->right;

      if (t->left != nullptr) {
        t = t->to_right_left_par(LEFT);
        if (t->right == nullptr)
          t->parent_ptr();
        else
          t->right->parent_ptr(t->parent);
        t->parent->parent_ptr(t);
        t->connect_left(tmp->left);
      }
      if (tmp->parent == nullptr)
        root = t->to_root();
      else
        t->parent_ptr(tmp->parent);
      t->connect_left(tmp->left);
    } else {
      if (tmp->parent == nullptr) {
        root = tmp->right->to_root();
      } else {
        if (tmp->left == nullptr)
          tmp->right->parent_ptr(tmp->parent);
        else
          tmp->left->parent_ptr(tmp->parent);
      }
    }
    pos.m_ptr->left = pos.m_ptr->parent = pos.m_ptr->right = nullptr;
    m_size--;
  }
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::erase_last(const Iterator pos) {
  n_ptr tmp = pos.m_ptr, t = tmp;
  if (tmp->left == nullptr) {
    tmp = tmp->right;
    if (t->parent != nullptr) {
      t->parent->connect_right(tmp);
    } else {
      root = tmp->to_root();
    }
  } else if (tmp->left != nullptr) {
    tmp = tmp->left;

    if (t->parent != nullptr) {
      t->parent->connect_right(tmp);
    } else {
      root = tmp->to_root();
    }

    tmp = tmp->to_right_left_par(RIGHT);

    tmp->connect_right(t->right);
  }
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::erase(Iterator pos) {
  erase_no_del(pos);
  delete pos.m_ptr;
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::swap(BinaryTree& other) {
  n_ptr tmp = root;

  root = other.root;
  other.root = tmp;

  size_t s = m_size;
  m_size = other.m_size;
  other.m_size = s;
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::merge(BinaryTree& other) {
  for (auto it = other.begin(), en = other.end(); other.m_size;) {
    while (this->contains(it.m_ptr->val)) {
      if (it == en) break;
      it++;
    }
    if (it == en) break;
    other.erase_no_del(it);
    this->add_node(it.m_ptr);
    it = other.begin();
    en = other.end();
  }
}

template <typename Key, typename M, typename T, typename Comp>
bool BinaryTree<Key, M, T, Comp>::contains(const Key& key) {
  bool ans = false;
  if (m_size) {
    size_t sz = m_size;
    n_ptr p = root;
    for (; sz > 0 && ans == false; sz--) {
      if (p->cmp(p->val, key) == GR) {
        if (p->left == nullptr)
          break;
        else
          p = p->left;
      } else if (p->cmp(p->val, key) == LS) {
        if (p->right == nullptr)
          break;
        else
          p = p->right;
      } else {
        ans = true;
      }
    }
  }
  return ans;
}

template <typename Key, typename M, typename T, typename Comp>
bool BinaryTree<Key, M, T, Comp>::contains(std::pair<Key, M> key) {
  return this->contains(key.first);
}

template <typename Key, typename M, typename T, typename Comp>
typename BinaryTree<Key, M, T, Comp>::Iterator
BinaryTree<Key, M, T, Comp>::find(const Key& key) {
  auto it = this->begin();

  for (; it != this->end(); it++) {
    if (it.m_ptr->cmp(it.m_ptr->val, key) == EQ) break;
  }

  return it;
}

template <typename Key, typename M, typename T, typename Comp>
std::pair<typename BinaryTree<Key, M, T, Comp>::Iterator, bool>
BinaryTree<Key, M, T, Comp>::insert(const T& new_val) {
  n_ptr tmp = new Node<Key, M, T, Comp>{nullptr, nullptr, nullptr, new_val};

  return add_node(tmp);
}

template <typename Key, typename M, typename T, typename Comp>
std::pair<typename BinaryTree<Key, M, T, Comp>::Iterator, bool>
BinaryTree<Key, M, T, Comp>::add_node(Node<Key, M, T, Comp>* n) {
  Node<Key, M, T, Comp>* p = root;
  bool flag = true;

  if (m_size == 0) {
    add_to_emt(n);
  } else {
    if (end().m_ptr->parent->cmp(n) == LS) {
      add_to_end(n);
    } else {
      for (; p != nullptr && flag;) {
        if (n->cmp(p) == LS) {
          if (p->left == nullptr) {
            p->left = n;
            break;
          } else {
            p = p->left;
          }
        } else if (n->cmp(p) == GR) {
          if (p->right == nullptr) {
            p->right = n;
            break;
          } else {
            p = p->right;
          }
        } else {
          flag = false;
          delete n;
        }
      }
      if (flag) {
        n->parent = p;
        m_size++;
      }
    }
  }
  return std::make_pair(BinaryTree<Key, M, T, Comp>::Iterator(flag ? n : p),
                        flag);
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::add_to_end(n_ptr n_e) {
  auto it = end().m_ptr;

  it->parent->connect_right(n_e);
  n_e->connect_right(it);

  m_size++;
}

template <typename Key, typename M, typename T, typename Comp>
void BinaryTree<Key, M, T, Comp>::add_to_emt(n_ptr n_e) {
  n_e->connect_right(root);

  root = n_e;
  m_size++;
}

}  // namespace s21

#endif  // __S21__TREE__H__