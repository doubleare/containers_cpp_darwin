#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <initializer_list>
#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::List<T>>
class Stack {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 public:
  /* Конструктор */
  Stack() : zalupa(){};

  /* Параметизированный конструктор */
  Stack(std::initializer_list<value_type> const& items) : zalupa(items){};

  /* Конструктор копирования */
  Stack(const Stack& s) : zalupa(s.zalupa){};

  /* Конструктор перемещения */
  Stack(Stack&& s) : zalupa(s.zalupa){};

  /* Оператор перемещения */
  Stack<value_type, Container>& operator=(Stack&& s) {
    this->zalupa = std::move(s.zalupa);
    return *this;
  }

  /* Оператор копирования */
  Stack<value_type, Container>& operator=(const Stack& s) {
    this->zalupa = s.zalupa;
    return *this;
  }

  /* Верхнее значение стэка */
  const_reference top() const { return zalupa.back(); }

  /* Размер контейнера */
  size_type size() const { return zalupa.size(); }

  /* Проверка на пустоту */
  bool empty() const { return zalupa.empty(); }

  void push(const_reference value) { zalupa.push_back(value); }

  /* Удаление одного элемента */
  void pop() { zalupa.pop_back(); }

  /* Меняет местами два стэка */
  void swap(Stack& other) {
    Stack<value_type, Container> Temp1(*this);
    Stack<value_type, Container> Temp2(other);
    *this = Temp2;
    other = Temp1;
  }

 protected:
  Container zalupa;
};

}  // end namespace s21

#endif  //  S21_STACK_H_
