#pragma once
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include "memory.h"
#include "graphics.h"

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
	
	bool operator<(const iterator& it) const{
		return itptr_ < it.itptr_;
	}
};

class ivy final {
	int size_;
	int ptr_;
	
	void realloc(int new_size);
	
public:
	
	ivy(int size);
	
	ivy(int size, int);
	
	ivy(std::initializer_list<int> L);
	
	ivy(const ivy& arr);
	
	ivy(ivy&& arr) : ivy(arr) {};
	
	ivy operator=(const ivy& arr){
		if(ptr_ == arr.ptr_)
			return *this;
		deallocate(ptr_);
		size_ = arr.size();
		ptr_ = allocate(size_);
		for (int i = 0; i < arr.size_; i++){
			(*this)[i] = arr[i];
		}
		return *this;
	};
	
	ivy operator=(ivy&& arr){
		(*this) = arr;
		return *this;
	};
	
	ivy(iterator b_it, iterator e_it);
	
	~ivy();
	
	
	void make_rand();
	
	void push_back(int v);
	
	void push_back(const ivy& arr);

	int& operator[](int index);
	
	int operator[](int index) const;
	
	int size() const;
	
	iterator begin() const;
	
	iterator end() const;
	

};



