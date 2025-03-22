#include <initializer_list>
#include <stdexcept>
#include "memory.h"
#include "graphics.h"
#include "slow_array.h"


iterator::iterator(int p) : itptr_(p) {
	
}
iterator::iterator(const iterator& it) : itptr_(it.itptr_) {
	
}

int& iterator::operator*() const {
	return get_line_ptr(itptr_).get_p2y_ref();
}

iterator& iterator::operator++(){
	itptr_++;
	return *this;
}

iterator iterator::operator++(int){
	iterator tmp(itptr_);
	itptr_++;
	return tmp;
}

iterator& iterator::operator--(){
	itptr_--;
	return *this;
}

iterator iterator::operator--(int){
	iterator tmp(itptr_);
	itptr_--;
	return tmp;
}
iterator iterator::operator+(int index) const {
	return iterator(itptr_+index);
}

iterator iterator::operator-(int index) const {
	return iterator(itptr_-index);
}

int iterator::operator-(const iterator& it) const {
	return itptr_ - it.itptr_;
}

bool iterator::operator==(const iterator& it) const {
	return itptr_ == it.itptr_;
}

bool iterator::operator!=(const iterator& it) const {
	return !(*this == it);
}




slow_array::slow_array(int size){
	size_ = size;
	ptr_ = allocate(size_);
	if (ptr_ == -1)
		throw std::runtime_error("Bag allocation in slow_array");
}

slow_array::slow_array(int size, int){
	size_ = size;
	ptr_ = allocate(size_);
	if (ptr_ == -1)
		throw std::runtime_error("Bag allocation in slow_array");
	make_rand();
}

slow_array::slow_array(std::initializer_list<int> L){
	size_ = L.size();
	ptr_ = allocate(size_);
	if (ptr_ == -1)
		throw std::runtime_error("Bag allocation in slow_array");
	auto p = ptr_;
	for (auto& el:L){
		mem_set_elem(p++, el);
	}
}

slow_array::slow_array(const slow_array& arr){
	size_ = arr.size_;
	ptr_ = allocate(size_);
	
	for (int i = 0; i < arr.size_; i++){
		(*this)[i] = arr[i];
	}
}

slow_array::slow_array(iterator b_it, iterator e_it){
	int size = e_it - b_it;
	if (size <= 0)
		throw std::runtime_error("second iterator must be greater than first");
	size_ = size;
	ptr_ = allocate(size_);
	if (ptr_ == -1)
		throw std::runtime_error("Bag allocation in slow_array");
	
	int i = 0;
	while(b_it != e_it) {
		(*this)[i] = *b_it;
		b_it++;
		i++;
	}
}

void slow_array::realloc(int new_size){
	int need_size = new_size - size_;
	bool flag = extend(ptr_, need_size);
	if (flag){
		size_ = new_size;
		return;
	}
	int new_ptr = allocate(new_size);
	for (int i = 0; i<size_; i++){
		int el = mem_get_elem(ptr_+i);
		mem_set_elem(new_ptr+i, el);
	}
	deallocate(ptr_);
	ptr_ = new_ptr;
	size_ = new_size;
}

void slow_array::push_back(int v){
	realloc(size_+1);
	(*this)[size_-1] = v;
}

void slow_array::push_back(const slow_array& arr){
	int old_size = size_;
	realloc(size_+arr.size());
	for (int i = 0; i<arr.size(); i++){
		(*this)[old_size+i] = arr[i];
	}
}

void slow_array::make_rand(){
	for (int i = ptr_; i < ptr_+size_; i++)
		mem_set_elem(i, rand()%99);
}


int& slow_array::operator[](int index) {
	return get_line_ptr(ptr_+index).get_p2y_ref();
}

int slow_array::operator[](int index) const {
	return get_line_ptr(ptr_+index).get_p2y_ref();
}

int slow_array::size() const {
	return size_;
}

iterator slow_array::begin() const {
	return iterator(ptr_);
}

iterator slow_array::end() const {
	return iterator(ptr_+size_);
}

slow_array::~slow_array(){
	deallocate(ptr_);
}




