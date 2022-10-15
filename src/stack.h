#ifndef SRC_INCLUDE_STACK_H_
#define SRC_INCLUDE_STACK_H_

#include <iostream>

namespace hhullen {

template <class T>
class stack {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  stack();
  stack(const std::initializer_list<value_type> &items);
  stack(const stack<value_type> &other);
  stack(stack<value_type> &&other);
  ~stack();
  stack<value_type> &operator=(const stack<value_type> &other);

  const_reference top();
  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <class... Args>
  void emplace_front(Args &&...args);

 private:
  class Node {
   public:
    value_type data;
    Node *next;
    Node(value_type data = value_type(), Node *next = nullptr)
        : data(data), next(next) {}
  };

  size_t size_;
  Node *top_node_ = nullptr;

  void fill_stak_by_other(const stack<value_type> &other);
};

template <class value_type>
stack<value_type>::stack() : size_(0) {}

template <class value_type>
stack<value_type>::stack(const std::initializer_list<value_type> &items)
    : size_(0) {
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    push(*iter);
  }
}

template <class value_type>
stack<value_type>::stack(const stack<value_type> &other) : size_(0) {
  fill_stak_by_other(other);
}

template <class value_type>
stack<value_type>::stack(stack<value_type> &&other) : size_(0) {
  fill_stak_by_other(other);
  other.~stack();
}

template <class value_type>
stack<value_type>::~stack() {
  while (top_node_) {
    pop();
  }
}

template <class value_type>
stack<value_type> &stack<value_type>::operator=(
    const stack<value_type> &other) {
  if (&other != this) {
    this->~stack();

    size_ = 0;
    fill_stak_by_other(other);
  }
  return *this;
}

template <class value_type>
const value_type &stack<value_type>::top() {
  return top_node_->data;
}

template <class value_type>
bool stack<value_type>::empty() {
  return !size_;
}

template <class value_type>
size_t stack<value_type>::size() {
  return size_;
}

template <class value_type>
void stack<value_type>::push(const_reference value) {
  Node *buffer = new Node();
  buffer->next = top_node_;
  top_node_ = buffer;
  top_node_->data = value;
  ++size_;
}

template <class value_type>
void stack<value_type>::pop() {
  Node *buffer = top_node_->next;
  delete top_node_;
  top_node_ = buffer;
  --size_;
}

template <class value_type>
void stack<value_type>::swap(hhullen::stack<value_type> &other) {
  Node *buffer = other.top_node_;
  size_type temp_size = other.size_;
  other.top_node_ = top_node_;
  top_node_ = buffer;
  other.size_ = size_;
  size_ = temp_size;
}

template <class value_type>
void stack<value_type>::fill_stak_by_other(const stack<value_type> &other) {
  Node *buffer = other.top_node_;
  while (buffer) {
    push(buffer->data);
    buffer = buffer->next;
  }
}

template <typename T>
template <class... Args>
void stack<T>::emplace_front(Args &&...args) {
  const int size_arg{sizeof...(args)};
  T arr[size_arg] = {args...};
  for (int i = 0; i < size_arg; i++) {
    push(arr[i]);
  }
}

}  // namespace hhullen

#endif  // SRC_INCLUDE_STACK_H_
