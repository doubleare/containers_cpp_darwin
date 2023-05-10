#ifndef __TREE__ITERATOR__H__
#define __TREE__ITERATOR__H__

class ConstIterator {
 public:
  n_ptr m_ptr;

  ConstIterator(n_ptr ptr) : m_ptr(ptr) {}
  ~ConstIterator() { m_ptr = nullptr; }

  const T& operator*() { return m_ptr->val; }
  ConstIterator& operator++() {
    if (m_ptr->right != nullptr) {
      m_ptr = m_ptr->right->to_right_left_par(LEFT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == LS)
        m_ptr = m_ptr->parent;
      else if (m_ptr->parent->parent != nullptr) {
        m_ptr = m_ptr->plus_minus(true);
      }
    }
    return *this;
  }
  ConstIterator operator++(int) {
    ConstIterator tmp = *this;
    if (m_ptr->right != nullptr) {
      m_ptr = m_ptr->right->to_right_left_par(LEFT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == LS)
        m_ptr = m_ptr->parent;
      else if (m_ptr->parent->parent != nullptr) {
        m_ptr = m_ptr->plus_minus(true);
      }
    }
    return tmp;
  }
  ConstIterator& operator--() {
    if (m_ptr->left != nullptr) {
      m_ptr = m_ptr->left->to_right_left_par(RIGHT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == GR ||
          m_ptr->cmp(m_ptr->val, Key{}) == EQ)
        m_ptr = m_ptr->parent;
      else
        m_ptr = m_ptr->plus_minus(false);
    }
    return *this;
  }
  ConstIterator operator--(int) {
    ConstIterator tmp = *this;
    if (m_ptr->left != nullptr) {
      m_ptr = m_ptr->left->to_right_left_par(RIGHT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == GR ||
          m_ptr->cmp(m_ptr->val, Key{}) == EQ)
        m_ptr = m_ptr->parent;
      else
        m_ptr = m_ptr->plus_minus(false);
    }
    return tmp;
  }
  bool operator==(const ConstIterator& b) { return m_ptr == b.m_ptr; }
  bool operator!=(const ConstIterator& b) { return m_ptr != b.m_ptr; }

  const T* operator->() { return &m_ptr->val; }
};

class Iterator {
 public:
  n_ptr m_ptr;

  Iterator(n_ptr ptr) : m_ptr(ptr) {}
  ~Iterator() { m_ptr = nullptr; }

  const T& operator*() { return m_ptr->val; }
  Iterator& operator++() {
    if (m_ptr->right != nullptr) {
      m_ptr = m_ptr->right->to_right_left_par(LEFT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == LS)
        m_ptr = m_ptr->parent;
      else if (m_ptr->parent->parent != nullptr) {
        m_ptr = m_ptr->plus_minus(true);
      }
    }
    return *this;
  }
  Iterator operator++(int) {
    Iterator tmp = *this;
    if (m_ptr->right != nullptr) {
      m_ptr = m_ptr->right->to_right_left_par(LEFT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == LS)
        m_ptr = m_ptr->parent;
      else if (m_ptr->parent->parent != nullptr) {
        m_ptr = m_ptr->plus_minus(true);
      }
    }
    return tmp;
  }
  Iterator& operator--() {
    if (m_ptr->left != nullptr) {
      m_ptr = m_ptr->left->to_right_left_par(RIGHT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == GR ||
          m_ptr->cmp(m_ptr->val, Key{}) == EQ)
        m_ptr = m_ptr->parent;
      else
        m_ptr = m_ptr->plus_minus(false);
    }
    return *this;
  }
  Iterator operator--(int) {
    Iterator tmp = *this;
    if (m_ptr->left != nullptr) {
      m_ptr = m_ptr->left->to_right_left_par(RIGHT);
    } else if (m_ptr->parent != nullptr) {
      if (m_ptr->cmp(m_ptr->parent) == GR ||
          m_ptr->cmp(m_ptr->val, Key{}) == EQ)
        m_ptr = m_ptr->parent;
      else
        m_ptr = m_ptr->plus_minus(false);
    }
    return tmp;
  }
  bool operator==(const Iterator& b) { return m_ptr == b.m_ptr; }
  bool operator!=(const Iterator& b) { return m_ptr != b.m_ptr; }

  T* operator->() { return &m_ptr->val; }
};

#endif  // __TREE__ITERATOR__H__