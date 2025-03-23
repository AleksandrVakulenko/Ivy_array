#pragma once
#include <initializer_list>
#include <stdexcept>
#include <utility>

class iterator final {
	int itptr_;
	
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int*;
    using reference = int&;

	iterator(int p);
	iterator(const iterator& it);
	
	int& operator*() const;
	
	iterator& operator++();
	iterator operator++(int);
	iterator& operator--();
	iterator operator--(int);
	
	iterator operator+(int index) const;
	iterator operator-(int index) const;
	int operator-(const iterator& it) const;
	
	bool operator==(const iterator& it) const;
	bool operator!=(const iterator& it) const;
	bool operator<(const iterator& it) const;
	bool operator>=(const iterator& it) const;
	bool operator>(const iterator& it) const;
	bool operator<=(const iterator& it) const;
	
};


class ivy final {
	int size_;
	int ptr_;

	void realloc(int new_size);
	void make_rand();
	
public:
	
	ivy(int size);
	ivy(int size, int value);
	ivy(iterator b_it, iterator e_it);
	ivy(std::initializer_list<int> L);
	ivy(const ivy& arr);
	ivy(ivy&& arr);
	~ivy();
	
	ivy operator=(const ivy& arr);
	ivy operator=(ivy&& arr);

	void push_back(int v);
	void push_back(const ivy& arr);

	int& operator[](int index);
	int operator[](int index) const;
	
	int size() const;
	iterator begin() const;
	iterator end() const;
	
};

