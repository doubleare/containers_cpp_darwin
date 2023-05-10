#ifndef __S21__VECTOR__H__
#define __S21__VECTOR__H__

#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector() {
    del();
    m_size = m_capacity = 0;
  };

  Vector &operator=(Vector &&v);
  Vector &operator=(const Vector &v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T *data();

  iterator begin();
  iterator end();

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  size_type capacity() const noexcept;
  void reserve(size_type size);
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;

  void cpy(const Vector &v);
  void mv(Vector &v);
  void del();
  void cpy_to_arr(size_type new_cap);
};
// default constructor, creates empty Vector
template <typename T>
Vector<T>::Vector() : m_size(0), m_capacity(0), arr(nullptr){};

// // parameterized constructor, creates the Vector of size n
template <typename T>
Vector<T>::Vector(size_type n)
    : m_size(n), m_capacity(n), arr(n ? new T[n]{} : nullptr){};

// initializer list constructor, creates Vector initizialized using
// std::initializer_list
template <typename T>
Vector<T>::Vector(std::initializer_list<T> const &items) {
  arr = new value_type[items.size()];

  for (auto it = items.begin(), i = 0; it != items.end(); it++) {
    arr[i++] = *it;
  }

  m_size = items.size();
  m_capacity = items.size();
};

// copy constructor
template <typename T>
Vector<T>::Vector(const Vector<T> &v) : m_size(0), m_capacity(0) {
  this->cpy(v);
};

/* assignment operator overload for coping object */
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
  this->del();

  this->cpy(v);

  return *this;
};

// move constructor
template <typename T>
Vector<T>::Vector(Vector &&v) {
  this->mv(v);
};

// assignment operator overload for moving object
template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  this->del();

  this->mv(v);

  return *this;
};

// 	access specified element with bounds checking
template <typename T>
T &Vector<T>::at(size_type pos) {
  if (pos >= this->size()) {
    throw std::out_of_range("pos >= this->size");
  }
  return arr[pos];
}

// 	access specified element
template <typename T>
T &Vector<T>::operator[](size_type pos) {
  return arr[pos];
}

// access the first element
template <typename T>
const T &Vector<T>::front() const {
  return arr[0];
}

// access the last element
template <typename T>
const T &Vector<T>::back() const {
  return arr[this->size() - 1];
}

// direct access to the underlying array
template <typename T>
T *Vector<T>::data() {
  return arr;
}

// returns an iterator to the beginning
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return iterator(&arr[0]);
}

// returns an iterator to the end
template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return iterator(&arr[m_size]);
}

// checks whether the container is empty
template <typename T>
bool Vector<T>::empty() const noexcept {
  return !(m_size > 0);
}

// returns the number of elements
template <typename T>
size_t Vector<T>::size() const noexcept {
  return m_size;
}

// returns the maximum possible number of elements
template <typename T>
size_t Vector<T>::max_size() const noexcept {
  return (SIZE_MAX / sizeof(value_type)) / 2;
}

/* allocate storage of size elements and
copies current array elements to a newely allocated array */
template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::out_of_range("new size > max_size");
  } else {
    if (size > m_capacity) {
      cpy_to_arr(size);
    }
  }
}

// returns the number of elements that can be held in currently allocated
// storage
template <typename T>
size_t Vector<T>::capacity() const noexcept {
  return m_capacity;
}

// reduces memory usage by freeing unused memory
template <typename T>
void Vector<T>::shrink_to_fit() {
  if (m_size < m_capacity) {
    cpy_to_arr(m_size);
  }
}

// clears the contents
template <typename T>
void Vector<T>::clear() noexcept {
  if (m_capacity > 0) {
    delete[] arr;
    m_size = 0;
    arr = new value_type[m_capacity];
  }
}

// inserts elements into concrete pos and returns the iterator that points to
// the new element
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  s21::Vector<T> tmp(*this);
  size_t c = 0;
  auto s = this->begin();

  for (; s != pos; s++, c++)
    ;

  if (s == this->end()) {
    this->push_back(value);
  } else {
    if (m_size == m_capacity)
      this->push_back(*(tmp.end()));
    else
      m_size++;
    s = this->begin() + c;
    *s = value;
  }

  s++;

  for (auto s2 = tmp.begin() + c; s2 != tmp.end(); s2++) {
    *s = *s2;
    s++;
  }

  return this->begin() + c;
}

/* erases element at pos */
template <typename T>
void Vector<T>::erase(iterator pos) {
  s21::Vector<T> tmp(*this);
  size_t c = 0;
  auto s = begin();

  for (; s != end(); s++, c++)
    if (pos == s) break;

  for (auto s2 = tmp.begin() + (c + 1); s2 != tmp.end();) {
    *s = *s2;
    s++;
    s2++;
  }

  m_size--;
}

/* adds an element to the end */
template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (m_size == m_capacity) {
    cpy_to_arr(m_size * 2);
  }
  arr[m_size++] = value;
}

// removes the last element
template <typename T>
void Vector<T>::pop_back() {
  if (m_size > 0) {
    arr[m_size] = 0;
    m_size--;
  }
}

// swaps the contents
template <typename T>
void Vector<T>::swap(Vector &other) {
  T *tmp = other.arr;

  other.arr = arr;
  arr = tmp;

  size_t s = m_size, c = m_capacity;

  m_size = other.m_size;
  m_capacity = other.m_capacity;

  other.m_size = s;
  other.m_capacity = c;
}

template <typename T>
void Vector<T>::cpy(const Vector<T> &v) {
  m_size = v.m_size;
  m_capacity = v.m_capacity > m_capacity ? v.m_capacity : m_capacity;
  arr = new value_type[m_capacity]{};

  for (size_type i = 0; i < m_size; i++) arr[i] = v.arr[i];
};

template <typename T>
void Vector<T>::mv(Vector<T> &v) {
  arr = v.arr;
  m_capacity = v.m_capacity;
  m_size = v.m_size;

  v.arr = nullptr;
  v.m_capacity = v.m_size = 0;
};

template <typename T>
void Vector<T>::cpy_to_arr(size_type new_cap) {
  T *new_arr = new T[new_cap]{};

  for (size_t i = 0; i < m_size; i++) new_arr[i] = arr[i];

  del();

  arr = new_arr;
  m_capacity = new_cap;
};

// clean memory
template <typename T>
void Vector<T>::del() {
  if (arr) {
    delete[] arr;
  }
}

}  // namespace s21

#endif  // __S21__VECTOR__H__