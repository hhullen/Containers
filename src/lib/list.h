#ifndef SRC_INCLUDE_LIST_H_
#define SRC_INCLUDE_LIST_H_

#include <iostream>

namespace hhullen {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  list();
  explicit list(size_t n);
  list(const std::initializer_list<value_type> &items);
  list(const list<value_type> &other);
  list(list<value_type> &&other);
  ~list();
  list<value_type> &operator=(const list<value_type> &other);

  value_type &front();
  value_type &back();

  class iterator;
  iterator begin();
  iterator end();

  bool empty();
  size_t size();
  size_t max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator &pos);
  void push_back(value_type value = value_type());
  void pop_back();
  void push_front(value_type value = value_type());
  void pop_front();
  void swap(list<value_type> &other);
  void merge(list<value_type> &other);
  void splice(const iterator pos, list<value_type> &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator emplace(const iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <class... Args>
  void emplace_front(Args &&...args);

 private:
  class Node {
   public:
    value_type data;
    Node *prev;
    Node *next;
    Node(value_type data = value_type(), Node *prev = nullptr,
         Node *next = nullptr)
        : data(data), prev(prev), next(next) {}
  };

  size_t size_;
  Node *null_node_ = nullptr;

  void get_null_node();
  void copy_data_other_to_this(const list<value_type> &other);
};

template <class T>
class list<T>::iterator {
  friend class list;

 public:
  iterator() { current_node_ = nullptr; }
  ~iterator() { current_node_ = nullptr; }
  reference operator*() { return current_node_->data; }
  iterator operator++() {
    current_node_ = current_node_->next;
    return *this;
  }

  iterator operator--() {
    current_node_ = current_node_->prev;
    return *this;
  }

  iterator operator++(int) {
    iterator temp = *this;
    current_node_ = current_node_->next;
    return temp;
  }

  iterator operator--(int) {
    iterator temp = *this;
    current_node_ = current_node_->prev;
    return temp;
  }

  bool operator==(const list<value_type>::iterator &other) {
    bool returnable = false;
    if (current_node_ == other.current_node_) {
      returnable = true;
    }
    return returnable;
  }

  bool operator!=(const list<value_type>::iterator &other) {
    bool returnable = true;
    if (*this == other) {
      returnable = false;
    }
    return returnable;
  }

 private:
  Node *current_node_;
};

template <class value_type>
list<value_type>::list() : size_(0) {
  get_null_node();
}

template <class value_type>
list<value_type>::list(size_t n) : size_(0) {
  get_null_node();
  for (size_t i = 0; i < n; ++i) {
    push_front();
  }
}

template <class value_type>
list<value_type>::list(const std::initializer_list<value_type> &items)
    : size_(0) {
  get_null_node();
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    push_back(*iter);
  }
}

template <class value_type>
list<value_type>::list(const list<value_type> &other) : size_(other.size_) {
  get_null_node();
  copy_data_other_to_this(other);
}

template <class value_type>
list<value_type>::list(list<value_type> &&other) : size_(other.size_) {
  get_null_node();
  copy_data_other_to_this(other);
  other.~list();
}

template <class value_type>
list<value_type>::~list() {
  while (null_node_ && null_node_->next != null_node_) {
    pop_front();
  }
  delete null_node_;
  null_node_ = nullptr;
  size_ = 0;
}

template <class value_type>
list<value_type> &list<value_type>::operator=(const list<value_type> &other) {
  if (&other != this) {
    this->~list();
    get_null_node();
    copy_data_other_to_this(other);
    size_ = other.size_;
  }
  return *this;
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  iterator iter;
  iter.current_node_ = null_node_->next;
  return iter;
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::end() {
  iterator iter;
  iter.current_node_ = null_node_;
  return iter;
}

template <class value_type>
value_type &list<value_type>::front() {
  return null_node_->next->data;
}

template <class value_type>
value_type &list<value_type>::back() {
  return null_node_->prev->data;
}

template <class value_type>
bool list<value_type>::empty() {
  return !size_;
}

template <class value_type>
size_t list<value_type>::size() {
  return size_;
}

template <class value_type>
size_t list<value_type>::max_size() {
  return std::allocator<hhullen::list<value_type>::Node>().max_size();
}

template <class value_type>
void list<value_type>::clear() {
  this->~list();
  get_null_node();
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::insert(
    typename list<value_type>::iterator pos, const_reference value) {
  Node *buffer = new Node(value, pos.current_node_->prev, pos.current_node_);
  buffer->next->prev = buffer;
  buffer->prev->next = buffer;
  ++size_;
  pos.current_node_ = buffer;

  return pos;
}

template <class value_type>
void list<value_type>::erase(typename list<value_type>::iterator &pos) {
  if (pos.current_node_ == null_node_) {
    throw std::invalid_argument("Impossible to erase null node");
  }

  Node *buffer = pos.current_node_->next;
  buffer->prev = buffer->prev->prev;
  buffer->prev->next = buffer;
  delete pos.current_node_;
  pos.current_node_ = buffer;
  --size_;
}

template <class value_type>
void list<value_type>::push_back(value_type value) {
  Node *buffer = new Node(value, null_node_->prev, null_node_);

  buffer->prev->next = buffer;
  null_node_->prev = buffer;
  ++size_;
}

template <class value_type>
void list<value_type>::pop_back() {
  null_node_->prev = null_node_->prev->prev;
  delete null_node_->prev->next;
  null_node_->prev->next = null_node_;
  --size_;
}

template <class value_type>
void list<value_type>::push_front(value_type value) {
  Node *buffer = new Node(value, null_node_, null_node_->next);

  null_node_->next = buffer;
  buffer->next->prev = buffer;
  ++size_;
}

template <class value_type>
void list<value_type>::pop_front() {
  null_node_->next = null_node_->next->next;
  delete null_node_->next->prev;
  null_node_->next->prev = null_node_;
  --size_;
}

template <class value_type>
void list<value_type>::swap(list<value_type> &other) {
  Node *buffer = null_node_;
  size_type temp_size = size_;

  null_node_ = other.null_node_;
  other.null_node_ = buffer;
  size_ = other.size_;
  other.size_ = temp_size;
}

template <class value_type>
void list<value_type>::merge(list<value_type> &other) {
  iterator iter = begin();
  iterator jter = other.begin();

  while (jter != other.end()) {
    insert(iter, *jter);
    ++jter;
  }
  sort();
}

template <class value_type>
void list<value_type>::splice(const typename list<value_type>::iterator pos,
                              list<value_type> &other) {
  iterator iter = other.begin();

  while (iter != other.end()) {
    insert(pos, *iter);
    ++iter;
  }
}

template <class value_type>
void list<value_type>::reverse() {
  Node *buffer = null_node_;

  for (size_t i = 0; i < size_ + 1; ++i) {
    Node *temp = buffer->next;
    buffer->next = buffer->prev;
    buffer->prev = temp;
    buffer = buffer->prev;
  }
}

template <class value_type>
void list<value_type>::unique() {
  iterator iter = begin();
  iterator ender = end();

  ++iter;
  while (iter != ender) {
    if (iter.current_node_->data == iter.current_node_->prev->data) {
      erase(iter);
    }
    ++iter;
  }
}

template <class value_type>
void list<value_type>::sort() {
  Node *buffer = null_node_->next;

  for (size_t i = 1; i < size_; ++i) {
    for (size_t j = 0; j < size_ - i; ++j) {
      if (buffer->data > buffer->next->data) {
        value_type temp_value = buffer->data;
        buffer->data = buffer->next->data;
        buffer->next->data = temp_value;
      }
      buffer = buffer->next;
    }
    buffer = null_node_->next;
  }
}

template <class value_type>
void list<value_type>::get_null_node() {
  null_node_ = new Node();
  null_node_->data = value_type();
  null_node_->next = null_node_;
  null_node_->prev = null_node_;
}

template <class value_type>
void list<value_type>::copy_data_other_to_this(const list<value_type> &other) {
  for (Node *buffer = other.null_node_->next; buffer != other.null_node_;
       buffer = buffer->next) {
    push_back(buffer->data);
  }
}

template <typename T>
template <class... Args>
typename list<T>::iterator list<T>::emplace(
    const typename list<value_type>::iterator pos, Args &&...args) {
  iterator new_pos = pos;
  const int size_arg{sizeof...(args)};
  T arr[size_arg] = {args...};
  for (int i = 0; i < size_arg; i++) {
    new_pos = insert(new_pos, arr[i]);
  }
  return new_pos;
}

template <typename T>
template <typename... Args>
void list<T>::emplace_back(Args &&...args) {
  const int size_arg{sizeof...(args)};
  T arr[size_arg] = {args...};
  for (int i = 0; i < size_arg; i++) {
    push_back(arr[i]);
  }
}

template <typename T>
template <class... Args>
void list<T>::emplace_front(Args &&...args) {
  const int size_arg{sizeof...(args)};
  T arr[size_arg] = {args...};
  for (int i = 0; i < size_arg; i++) {
    push_front(arr[i]);
  }
}

}  // namespace hhullen

#endif  // SRC_INCLUDE_LIST_H_
