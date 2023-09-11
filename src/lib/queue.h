#ifndef SRC_INCLUDE_QUEUE_H_
#define SRC_INCLUDE_QUEUE_H_

#include <iostream>

namespace hhullen {

template <class T>
class queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  queue();
  queue(const std::initializer_list<value_type> &items);
  queue(const queue<value_type> &other);
  queue(queue<value_type> &&other);
  ~queue();
  queue<value_type> &operator=(const queue<value_type> &other);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  class Node {
   public:
    value_type data;
    Node *next;
    Node *prev;
    Node(value_type data = value_type(), Node *next = nullptr,
         Node *prev = nullptr)
        : data(data), next(next), prev(prev) {}
  };

  size_t size_;
  Node *head_ = nullptr;
  Node *tail_ = nullptr;

  void get_null_node();
  void fill_queue_by_other(const queue<value_type> &other);
};

template <class value_type>
queue<value_type>::queue() : size_(0) {
  get_null_node();
}

template <class value_type>
queue<value_type>::queue(const std::initializer_list<value_type> &items)
    : size_(0) {
  get_null_node();
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    push(*iter);
  }
}

template <class value_type>
queue<value_type>::queue(const queue<value_type> &other) : size_(0) {
  get_null_node();
  fill_queue_by_other(other);
}

template <class value_type>
queue<value_type>::queue(queue<value_type> &&other) : size_(0) {
  get_null_node();
  fill_queue_by_other(other);
  other.~queue();
}

template <class value_type>
queue<value_type>::~queue() {
  while (head_) {
    pop();
  }
}

template <class value_type>
queue<value_type> &queue<value_type>::operator=(
    const queue<value_type> &other) {
  if (&other != this) {
    this->~queue();

    size_ = 0;
    get_null_node();
    fill_queue_by_other(other);
  }
  return *this;
}

template <class value_type>
const value_type &queue<value_type>::front() {
  return head_->data;
}

template <class value_type>
const value_type &queue<value_type>::back() {
  return tail_->next->data;
}

template <class value_type>
bool queue<value_type>::empty() {
  return !size_;
}

template <class value_type>
size_t queue<value_type>::size() {
  return size_;
}

template <class value_type>
void queue<value_type>::push(const_reference value) {
  tail_->prev = new Node(value_type(), tail_);
  tail_->data = value;
  tail_ = tail_->prev;
  ++size_;
}

template <class value_type>
void queue<value_type>::pop() {
  Node *buffer = head_->prev;
  delete head_;
  head_ = buffer;
  --size_;
}

template <class value_type>
void queue<value_type>::swap(hhullen::queue<value_type> &other) {
  Node *head_buffer = other.head_;
  Node *tail_buffer = other.tail_;
  size_type temp_size = other.size_;
  other.head_ = head_;
  other.tail_ = tail_;
  other.size_ = size_;
  head_ = head_buffer;
  tail_ = tail_buffer;
  size_ = temp_size;
}

template <class value_type>
void queue<value_type>::get_null_node() {
  Node *buffer = new Node;
  head_ = buffer;
  tail_ = buffer;
}

template <class value_type>
void queue<value_type>::fill_queue_by_other(const queue<value_type> &other) {
  Node *buffer = other.head_;
  while (buffer != other.tail_) {
    push(buffer->data);
    buffer = buffer->prev;
  }
}

template <typename T>
template <typename... Args>
void queue<T>::emplace_back(Args &&...args) {
  const int size_arg{sizeof...(args)};
  T arr[size_arg] = {args...};
  for (int i = 0; i < size_arg; i++) {
    push(arr[i]);
  }
}

}  // namespace hhullen

#endif  // SRC_INCLUDE_QUEUE_H_
