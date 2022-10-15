#ifndef SRC_INCLUDE_VECTOR_H_
#define SRC_INCLUDE_VECTOR_H_

#include <iostream>

namespace hhullen {

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(const std::initializer_list<value_type> &items);
  vector(const vector<value_type> &other);
  vector(vector<value_type> &&other);
  ~vector();
  vector<value_type> &operator=(vector<value_type> &other);
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data();

  class iterator;
  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <class... Args>
  iterator emplace(const iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <class... Args>
  void emplace_front(Args &&...args);

 private:
  value_type *data_ = nullptr;
  size_type size_ = 0;
  size_type reserved_ = 1;

  void get_empty_vector();
  void get_vector_data_by_other(const vector<value_type> &other);
  void shift_values_right_from_pos(value_type *current, value_type *end);
  void shift_values_left_to_pos(value_type *current, value_type *end);
};

template <class T>
class vector<T>::iterator {
  friend class vector;

 public:
  reference operator*() {
    value_type *returnable;
    if (current_element_ != end_element_) {
      returnable = current_element_;
    } else {
      returnable = new value_type();
    }
    return *returnable;
  }
  iterator operator++() {
    if (current_element_ != end_element_) {
      ++current_element_;
    }
    return *this;
  }
  iterator operator--() {
    if (current_element_ != first_element_) {
      --current_element_;
    }
    return *this;
  }
  iterator operator++(int) {
    iterator temp(*this);
    ++this;
    return temp;
  }
  iterator operator--(int) {
    iterator temp(*this);
    --this;
    return temp;
  }
  bool operator==(const vector<value_type>::iterator &other) {
    bool returnable = false;
    if (current_element_ == other.current_element_) {
      returnable = true;
    }
    return returnable;
  }
  bool operator!=(const vector<value_type>::iterator &other) {
    bool returnable = false;
    if (current_element_ != other.current_element_) {
      returnable = true;
    }
    return returnable;
  }

 private:
  value_type *first_element_;
  value_type *current_element_;
  value_type *end_element_;
};

template <class value_type>
vector<value_type>::vector() {
  size_ = 0;
  get_empty_vector();
}

template <class value_type>
vector<value_type>::vector(size_type n) : size_(n) {
  get_empty_vector();
  for (size_type i = 0; i < size_ + reserved_ + 1; ++i) {
    data_[i] = value_type();
  }
}

template <class value_type>
vector<value_type>::vector(const std::initializer_list<value_type> &items) {
  auto iter = items.begin();

  while (iter != items.end()) {
    ++size_;
    ++iter;
  }

  get_empty_vector();
  iter = items.begin();

  for (size_type i = 0; i < size_; ++i) {
    data_[i] = *iter;
    ++iter;
  }
}

template <class value_type>
vector<value_type>::vector(const vector<value_type> &other)
    : size_(other.size_), reserved_(other.reserved_) {
  get_empty_vector();
  get_vector_data_by_other(other);
}

template <class value_type>
vector<value_type>::vector(vector<value_type> &&other)
    : size_(other.size_), reserved_(other.reserved_) {
  get_empty_vector();
  get_vector_data_by_other(other);
  other.~vector();
}

template <class value_type>
vector<value_type>::~vector() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  reserved_ = 1;
}

template <class value_type>
vector<value_type> &vector<value_type>::operator=(vector<value_type> &other) {
  if (&other != this) {
    this->~vector();

    size_ = other.size_;
    reserved_ = other.reserved_;
    data_ = new value_type[size_ + reserved_];

    for (size_type i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }
  return *this;
}

template <class value_type>
value_type &vector<value_type>::at(size_type pos) {
  if (pos >= size_) {
    throw std::invalid_argument("Access attempt to out of range");
  }
  return data_[pos];
}

template <class value_type>
value_type &vector<value_type>::operator[](size_type pos) {
  return data_[pos];
}

template <class value_type>
const value_type &vector<value_type>::front() {
  if (size_ == 0) {
    throw std::invalid_argument("Container is empty");
  }

  return data_[0];
}

template <class value_type>
const value_type &vector<value_type>::back() {
  if (size_ == 0) {
    throw std::invalid_argument("Container is empty");
  }
  return data_[size_ - 1];
}

template <class value_type>
value_type *vector<value_type>::data() {
  return data_;
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  iterator iter;
  iter.first_element_ = &data_[0];
  iter.current_element_ = &data_[0];
  iter.end_element_ = &data_[size_];
  return iter;
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  iterator iter;
  iter.first_element_ = &data_[0];
  iter.current_element_ = &data_[size_];
  iter.end_element_ = &data_[size_];
  return iter;
}

template <class value_type>
bool vector<value_type>::empty() {
  return !size_;
}

template <class value_type>
size_t vector<value_type>::size() {
  return size_;
}

template <class value_type>
size_t vector<value_type>::max_size() {
  return std::allocator<hhullen::vector<value_type>::value_type>().max_size();
}

template <class value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > reserved_) {
    reserved_ = size - size_;
    vector<value_type> temp(*this);
    *this = temp;
  }
}

template <class value_type>
size_t vector<value_type>::capacity() {
  return size_ + reserved_;
}

template <class value_type>
void vector<value_type>::shrink_to_fit() {
  reserved_ = 0;
  vector<value_type> temp(*this);
  *this = temp;
}

template <class value_type>
void vector<value_type>::clear() {
  this->~vector();
  if (reserved_ > 0) {
    data_ = new value_type[reserved_];
  }
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    typename vector<value_type>::iterator pos, const_reference value) {
  if (reserved_ > 0) {
    shift_values_right_from_pos(pos.current_element_, pos.end_element_);
    *pos.current_element_ = value;
    ++size_;
  } else {
    ++size_;
    vector<value_type> temp(*this);
    temp.shift_values_right_from_pos(pos.current_element_, pos.end_element_);
    *pos.current_element_ = value;
    *this = temp;
  }
  return pos;
}

template <class value_type>
void vector<value_type>::erase(iterator pos) {
  --size_;
  shift_values_left_to_pos(pos.current_element_, pos.end_element_);
  data_[size_] = 0;
}

template <class value_type>
void vector<value_type>::push_back(const_reference value) {
  iterator pos = end();
  insert(pos, value);
}

template <class value_type>
void vector<value_type>::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("There is no element to pop");
  }

  iterator pos = end();
  --pos;
  erase(pos);
}

template <class value_type>
void vector<value_type>::swap(vector &other) {
  vector<value_type> temp(*this);
  *this = other;
  other = temp;
}

template <class value_type>
void vector<value_type>::get_empty_vector() {
  data_ = new value_type[size_ + reserved_ + 1];
}

template <class value_type>
void vector<value_type>::get_vector_data_by_other(
    const vector<value_type> &other) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <class value_type>
void vector<value_type>::shift_values_right_from_pos(value_type *current,
                                                     value_type *end) {
  value_type *p_temp_last = end, *p_temp_prev = --end;

  while (p_temp_last != current) {
    *p_temp_last = *p_temp_prev;
    --p_temp_last;
    --p_temp_prev;
  }
}

template <class value_type>
void vector<value_type>::shift_values_left_to_pos(value_type *current,
                                                  value_type *end) {
  value_type *p_temp_current = current, *p_temp_next = ++current;

  while (p_temp_next != end) {
    *p_temp_current = *p_temp_next;
    ++p_temp_current;
    ++p_temp_next;
  }
}

template <typename T>
template <class... Args>
typename vector<T>::iterator vector<T>::emplace(
    const typename vector<value_type>::iterator pos, Args &&...args) {
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
void vector<T>::emplace_back(Args &&...args) {
  const int size_arg{sizeof...(args)};
  T arr[size_arg] = {args...};
  for (int i = 0; i < size_arg; i++) {
    push_back(arr[i]);
  }
}

template <typename T>
template <class... Args>
void vector<T>::emplace_front(Args &&...args) {
  iterator new_pos = begin();
  const int size_arg{sizeof...(args)};
  T arr[size_arg] = {args...};
  for (int i = 0; i < size_arg; i++) {
    new_pos = insert(new_pos, arr[i]);
  }
}

}  // namespace hhullen

#endif  // SRC_INCLUDE_VECTOR_H_
