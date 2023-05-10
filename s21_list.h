#ifndef __S21__LIST__H__
#define __S21__LIST__H__

#include <initializer_list>
#include <iostream>

namespace s21 {

template <typename T>
struct node {
  node *next;
  node *prev;
  T val;

  void connect_nodes(node *o) {
    this->next = o;
    o->prev = this;
  }

  void swap(node *o) {
    node tmp = *o;

    this->prev->connect_nodes(o);
    o->connect_nodes(this->next);

    tmp.prev->connect_nodes(this);
    this->connect_nodes(tmp.next);
  }

  void swap_near() {
    node t = *this, tmp = *this->next;

    this->prev->connect_nodes(this->next);
    t.next->connect_nodes(this);
    this->connect_nodes(tmp.next);
  }
};

template <class T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  using nl_ptr = node<T> *;

  class ListConstIterator {
   public:
    nl_ptr m_ptr;

    ListConstIterator(nl_ptr ptr) : m_ptr(ptr) {}
    ~ListConstIterator() { m_ptr = nullptr; }

    const_reference operator*() { return m_ptr->val; }
    ListConstIterator &operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }
    ListConstIterator operator++(int) {
      ListConstIterator tmp = *this;
      m_ptr = m_ptr->next;
      return tmp;
    }
    ListConstIterator &operator--() {
      m_ptr = m_ptr->prev;
      return *this;
    }
    ListConstIterator operator--(int) {
      ListConstIterator tmp = *this;
      m_ptr = m_ptr->prev;
      return tmp;
    }
    bool operator==(const ListConstIterator &b) { return m_ptr == b.m_ptr; }
    bool operator!=(const ListConstIterator &b) { return m_ptr != b.m_ptr; }
  };

  class ListIterator : public ListConstIterator {
   public:
    ListIterator(nl_ptr ptr) : ListConstIterator(ptr) {}

    reference operator*() { return this->m_ptr->val; }
    ListIterator &operator++() {
      this->m_ptr = this->m_ptr->next;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator tmp = *this;
      this->m_ptr = this->m_ptr->next;
      return tmp;
    }
    ListIterator &operator--() {
      this->m_ptr = this->m_ptr->prev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator tmp = *this;
      this->m_ptr = this->m_ptr->prev;
      return tmp;
    }
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &v);
  List(List &&v);
  ~List() {
    del();
    delete arr;
  };

  List &operator=(const List &v);
  List &operator=(List &&v);

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void reverse() noexcept;
  void unique();
  void sort();

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(const_iterator pos, List &other);
  void swap(List &other);
  void merge(List &other);

 private:
  nl_ptr arr;
  size_t m_size;

  void push_to_ept(const_reference value);
  void sw(nl_ptr t, nl_ptr o);
  void cpy(const List &v);
  void mv(List &v);
  void fake_node();
  void del();
  void oth_empty(List &other, nl_ptr t);
};
template <typename T>
List<T>::List() : m_size(0) {
  fake_node();
};

template <typename T>
List<T>::List(size_type n) : m_size(0) {
  fake_node();
  if (n > 0) {
    for (size_t i = 0; i < n; i++) {
      push_back(0);
    }
  }
};

template <typename T>
List<T>::List(std::initializer_list<T> const &items) : m_size(0) {
  fake_node();
  for (auto it = items.begin(); it != items.end(); it++) {
    push_back(*it);
  }
};

template <typename T>
List<T>::List(const List<T> &v) : m_size(0) {
  fake_node();
  cpy(v);
};

template <typename T>
List<T> &List<T>::operator=(const List<T> &v) {
  del();
  cpy(v);

  return *this;
};

template <typename T>
List<T>::List(List &&v) {
  mv(v);
};

template <typename T>
List<T> &List<T>::operator=(List &&v) {
  del();
  delete arr;
  mv(v);

  return *this;
};

template <typename T>
size_t List<T>::size() const noexcept {
  return m_size;
}

template <typename T>
void List<T>::fake_node() {
  arr = new node<T>{};
  arr->next = arr->prev = arr;
}

template <typename T>
void List<T>::del() {
  if (m_size > 0) {
    for (size_t i = 1; i < m_size; arr = arr->next, i++)
      ;
    for (size_t i = 1; i < m_size; arr = arr->prev, i++) {
      delete arr->next;
    }
    delete arr->next;
    arr->next = arr->prev = arr;
    arr->val = T{};
    m_size = 0;
  }
}

template <typename T>
void List<T>::push_to_ept(const_reference value) {
  arr->next = new node<T>{};
  arr->prev = arr->next;
  arr->next->next = arr->next->prev = arr;
  arr->val = value;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  if (m_size > 0) {
    auto it = --end();
    it.m_ptr->next = new node<T>{};
    it.m_ptr->next->prev = it.m_ptr;
    it.m_ptr->next->val = value;
    it.m_ptr->next->connect_nodes(arr->prev);
  } else {
    push_to_ept(value);
  }
  m_size++;
}

template <typename T>
void List<T>::pop_back() {
  if (m_size > 0) {
    if (m_size == 1) {
      del();
    } else {
      auto it = --end();
      it.m_ptr->prev->connect_nodes(it.m_ptr->next);
      delete it.m_ptr;
      m_size--;
    }
  }
}

template <typename T>
void List<T>::push_front(const_reference value) {
  if (m_size > 0) {
    nl_ptr tmp = new node<T>{};
    tmp->val = value;
    arr->prev->val = 0;
    arr->prev->connect_nodes(tmp);
    tmp->connect_nodes(arr);
    arr = tmp;
  } else {
    push_to_ept(value);
  }
  m_size++;
}

template <typename T>
void List<T>::pop_front() {
  if (m_size > 0) {
    auto it = begin();
    it.m_ptr->prev->connect_nodes(it.m_ptr->next);
    arr = it.m_ptr->next;
    delete it.m_ptr;
    m_size--;
  }
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  return iterator(arr);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(m_size ? arr->prev : arr);
}

template <typename T>
const T &List<T>::front() const {
  return arr->val;
}

template <typename T>
const T &List<T>::back() const {
  return arr->prev->prev->val;
}

template <typename T>
bool List<T>::empty() const noexcept {
  return !(m_size > 0);
}

template <typename T>
size_t List<T>::max_size() const noexcept {
  return (SIZE_MAX / sizeof(node<value_type>)) / 2;
}

template <typename T>
void List<T>::clear() noexcept {
  del();
}

template <typename T>
void List<T>::reverse() noexcept {
  int c = 0, l = size() % 2 == 0 ? size() / 2 : (size() - 1) / 2;

  for (auto s = begin(), e = --end(); c < l; c++) {
    sw(s.m_ptr, e.m_ptr);
    s = begin();
    e = --end();
    for (int i = 0; i <= c; s++, i++)
      ;
    for (int i = 0; i <= c; e--, i++)
      ;
  }
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (m_size) {
    nl_ptr tmp = arr;
    auto s = begin();

    for (; s != end(); s++, tmp = tmp->next)
      if (pos == s) break;

    if (s != end()) {
      tmp->prev->connect_nodes(tmp->next);

      arr = pos == begin() ? tmp->next : arr;

      delete tmp;

      m_size--;
    }
  }
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  auto s = begin();

  if (pos == end()) {
    push_back(value);
    s = --this->end();
  } else if (pos == begin()) {
    push_front(value);
    s = this->begin();
  } else {
    nl_ptr tmp = arr;

    for (; s != end(); s++, tmp = tmp->next)
      if (pos == s) break;

    if (s != end()) {
      nl_ptr n = new node<T>{};

      m_size++;
      tmp->prev->connect_nodes(n);
      n->connect_nodes(tmp);
      n->val = value;

      s = iterator(n);
    }
  }

  return s;
}

template <typename T>
void List<T>::oth_empty(List &o, nl_ptr t) {
  t->next = t->prev = t;
  o.arr = t;

  m_size += o.m_size;
  o.m_size = 0;
}

template <typename T>
void List<T>::splice(const_iterator pos, List &o) {
  nl_ptr tmp = arr, t = o.arr;
  auto s = begin();

  for (; s != (begin() == pos ? end() : pos); s++) tmp = tmp->next;

  for (size_t i = 0; i < o.m_size; i++) t = t->next;

  if (begin() == pos) {
    tmp->connect_nodes(o.arr);
    t->prev->connect_nodes(arr);

    arr = o.arr;
  } else {
    tmp->prev->connect_nodes(o.arr);
    t->prev->connect_nodes(tmp);
  }
  oth_empty(o, t);
}

template <typename T>
void List<T>::swap(List &o) {
  nl_ptr tmp = o.arr;

  o.arr = arr;
  arr = tmp;

  auto s = m_size;

  m_size = o.m_size;
  o.m_size = s;
}

template <typename T>
void List<T>::unique() {
  if (m_size > 1) {
    for (auto s = begin(), s1 = ++begin(); s1 != end();) {
      if (s.m_ptr->val == s1.m_ptr->val) {
        erase(s1++);
      } else {
        s++;
        s1++;
      }
    }
  }
}

template <typename T>
void List<T>::sw(nl_ptr t, nl_ptr o) {
  if (begin().m_ptr == t) {
    arr = o;
  }
  if (t->next == o)
    t->swap_near();
  else
    t->swap(o);
}

template <typename T>
void List<T>::sort() {
  if (m_size > 1) {
    auto s = begin();

    for (; s != --end(); s++) {
      auto s1 = s, sw = s;
      for (; s1 != end(); s1++) {
        if (s1.m_ptr->val < sw.m_ptr->val) {
          sw = s1;
        }
      }
      if (sw != s) {
        this->sw(s.m_ptr, sw.m_ptr);
        s = this->begin();
      }
    }
  }
}

template <typename T>
void List<T>::cpy(const List<T> &v) {
  size_t i = 0;
  for (nl_ptr tmp = v.arr; i < v.m_size; tmp = tmp->next, i++) {
    push_back(tmp->val);
  }
};

template <typename T>
void List<T>::mv(List<T> &v) {
  arr = v.arr;
  m_size = v.m_size;

  v.arr = nullptr;
  v.m_size = 0;
};

template <typename T>
void List<T>::merge(List &o) {
  if (arr != o.arr) {
    if (back() < o.front()) {
      splice(end(), o);
    } else if (o.back() < front()) {
      o.splice(o.end(), *this);
      splice(begin(), o);
    } else {
      if (o.front() < front()) swap(o);

      auto ed = o.end(), lt = --o.end();

      for (auto it = begin(), st = it, io = o.begin(), so = io; st != end();) {
        if (*so < *st) {
          it.m_ptr->connect_nodes(so.m_ptr);

          for (io = so, so++; *so < *st && so != ed; so++, io++)
            ;

          io.m_ptr->connect_nodes(st.m_ptr);
          if (so == ed) break;
        } else {
          it = st;
          if (++st == end()) {
            it.m_ptr->connect_nodes(so.m_ptr);
            lt.m_ptr->connect_nodes(st.m_ptr);
          }
        }
      }
      oth_empty(o, ed.m_ptr);
    }
  }
}

}  // namespace s21

#endif  // __S21__LIST__H__