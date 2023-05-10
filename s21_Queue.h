#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "s21_Stack.h"

namespace s21 {

template <typename T, typename Container = s21::List<T>>
class Queue : public Stack<T, Container> {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using Stack<value_type>::zalupa;
  using Stack<value_type>::top;

 public:
  /* Конструктор */
  Queue() : Stack<value_type>(){};

  /* Параметизированный конструктор */
  Queue(std::initializer_list<value_type> const& items)
      : Stack<value_type>(items){};

  /* Конструктор копирования */
  Queue(const Queue& s) : Stack<value_type>(s){};

  /* Конструктор перемещения */
  Queue(Queue&& s) : Stack<value_type>(s){};

  /* Оператор перемещения */
  Queue& operator=(Queue&& s) {
    this->zalupa = std::move(s.zalupa);
    return *this;
  };

  /* Оператор копирования */
  Queue& operator=(const Queue& s) {
    this->zalupa = s.zalupa;
    return *this;
  };

  /* Первый элемент в очереди */
  const_reference front() const { return zalupa.front(); }

  /* Последний элемент в очереди */
  const_reference back() const { return zalupa.back(); }

  /* Удаление одного элемента */
  void pop() { zalupa.pop_front(); }
};

}  // end namespace s21

#endif  // S21_QUEUE_H_