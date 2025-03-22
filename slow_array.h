#pragma once
#include <initializer_list>
#include <stdexcept>
#include "memory.h"
#include "graphics.h"

class itarator final {
int itptr_;
	
public:
	itarator(int p) : itptr_(p) {}
	itarator(const itarator& it) : itptr_(it.itptr_) {}
	
	int& operator*(){
		return get_line_ptr(itptr_).get_p2y_ref();
	}
	
	itarator& operator++(){
		itptr_++;
		return *this;
	}
	
	itarator operator++(int){
		itarator tmp(itptr_);
		itptr_++;
		return tmp;
	}
	
	itarator operator+(int index){
		return itarator(itptr_+index);
	}
	
	itarator operator-(int index){
		return itarator(itptr_-index);
	}
};

class slow_array final {
	int size_;
	int ptr_;
	
	
	public: //------------------------------------------------------------------
	
	slow_array(int size){
		size_ = size;
		ptr_ = allocate(size_);
		if (ptr_ == -1)
			throw std::runtime_error("Bag allocation in slow_array");
	}
	
	slow_array(int size, int){
		size_ = size;
		ptr_ = allocate(size_);
		if (ptr_ == -1)
			throw std::runtime_error("Bag allocation in slow_array");
		make_rand();
	}
	
	slow_array(std::initializer_list<int> L){
		size_ = L.size();
		ptr_ = allocate(size_);
		if (ptr_ == -1)
			throw std::runtime_error("Bag allocation in slow_array");
		auto p = ptr_;
		for (auto& el:L){
			mem_set_elem(p++, el);
		}
	}
	
	slow_array(const slow_array& arr){
		size_ = arr.size_;
		ptr_ = allocate(size_);
		
		for (int i = 0; i < arr.size_; i++){
			this->operator[](i) = arr[i];
		}
	}
	
	void make_rand(){
		for (int i = ptr_; i < ptr_+size_; i++)
			mem_set_elem(i, rand()%99);
	}
	
	slow_array operator=(const slow_array&) = delete;
	
	int& operator[](int index) {
		return get_line_ptr(ptr_+index).get_p2y_ref();
	}
	
	int operator[](int index) const {
		return get_line_ptr(ptr_+index).get_p2y_ref();
	}
	
	int size() const {
		return size_;
	}
	
	itarator begin() const {
		return itarator(ptr_);
	}
	
	itarator end() const {
		return itarator(ptr_+size_);
	}
	
	~slow_array(){
		deallocate(ptr_);
	}
};



