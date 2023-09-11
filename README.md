# Containers
Some STL template containers implementation. All classes are in hhullen namespace.

## There are the next contsiners methods implementation:  

# list
    * value_type = T;
    * reference = value_type &;
    * const_reference = const value_type &;
    * size_type = size_t;

    * list::iterator;

### constructors  
```
1. list();
2. explicit list(size_t n);
3. list(const std::initializer_list<value_type> &items);
3. list(const list<value_type> &other);
5. list(list<value_type> &&other);
```

### methods
```
1. value_type &front();
2. value_type &back();
3. iterator begin();
4. iterator end();
5. bool empty();
6. size_t size();
7. size_t max_size();
8. void clear();
9. iterator insert(iterator pos, const_reference value);
10. void erase(iterator &pos);
11. void push_back(value_type value = value_type());
12. void pop_back();
13. void push_front(value_type value = value_type());
14. void pop_front();
15. void swap(list<value_type> &other);
16. void merge(list<value_type> &other);
17. void splice(const iterator pos, list<value_type> &other);
18. void reverse();
19. void unique();
20. void sort();
21. iterator emplace(const iterator &pos, Args &&...args);
22. void emplace_back(Args &&...args);
23. void emplace_front(Args &&...args);
24. list<value_type> &operator=(const list<value_type> &other);
```

# vector
    * value_type = T;
    * reference = value_type &;
    * const_reference = const value_type &;
    * size_type = size_t;

    * vector::iterator;

### constructors 
```
1. vector();
2. explicit vector(size_type n);
3. vector(const std::initializer_list<value_type> &items);
4. vector(const vector<value_type> &other);
5. vector(vector<value_type> &&other);
```

### methods
```
1. vector<value_type> &operator=(vector<value_type> &other);
2. reference at(size_type pos);
3. reference operator[](size_type pos);
4. const_reference front();
5. const_reference back();
6. value_type *data();
7. iterator begin();
8. iterator end();
9. bool empty();
10. size_type size();
11. size_type max_size();
12. void reserve(size_type size);
13. size_type capacity();
14. void shrink_to_fit();
15. void clear();
16. iterator insert(iterator pos, const_reference value);
17. void erase(iterator pos);
18. void push_back(const_reference value);
19. void pop_back();
20. void swap(vector &other);
21. iterator emplace(const iterator pos, Args &&...args);
22. void emplace_back(Args &&...args);
23. void emplace_front(Args &&...args);
```

# stack
    * value_type = T;
    * reference = value_type &;
    * const_reference = const value_type &;
    * size_type = size_t;

### constructors 
```
1. stack();
2. stack(const std::initializer_list<value_type> &items);
3. stack(const stack<value_type> &other);
4. stack(stack<value_type> &&other);
```

### methods
```
1. stack<value_type> &operator=(const stack<value_type> &other);
2. const_reference top();
3. bool empty();
4. size_type size();
5. void push(const_reference value);
6. void pop();
7. void swap(stack &other);
8. void emplace_front(Args &&...args);
```

# queue
    * value_type = T;
    * reference = value_type &;
    * const_reference = const value_type &;
    * size_type = size_t;

### constructors 
```
1. queue();
2. queue(const std::initializer_list<value_type> &items);
3. queue(const queue<value_type> &other);
4. queue(queue<value_type> &&other);
```

### methods
```
1. queue<value_type> &operator=(const queue<value_type> &other);
2. const_reference front();
3. const_reference back();
4. bool empty();
5. size_type size();
6. void push(const_reference value);
7. void pop();
8. void swap(queue &other);
9. void emplace_back(Args &&...args);
```
