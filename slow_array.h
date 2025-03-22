#pragma once
#include <initializer_list>
#include <stdexcept>
#include "memory.h"
#include "graphics.h"



class slow_array final {
	int size_;
	int ptr_;
	
	
	public: //------------------------------------------------------------------
	
	slow_array(int size){
		size_ = size;
		ptr_ = allocate(size_);
		if (ptr_ == -1)
			throw std::runtime_error("Bag allocation in slow_array");
		for (int i = ptr_; i < ptr_+size; i++)
			mem_set_elem(i, rand()%99);
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
	
	float& operator[](int index){
		return get_line_ptr(ptr_+index).get_p2y_ref();
	}
	
	int size(){
		return size_;
	}
	
	~slow_array(){
		deallocate(ptr_);
	}
};



