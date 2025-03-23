#include <initializer_list>
#include <stdexcept>
#include "ivy.h"
#include "memory.h"
//#include "graphics.h"

iterator::iterator(int p) : itptr_(p) {}
iterator::iterator(const iterator& it) : itptr_(it.itptr_) {}

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

bool iterator::operator<(const iterator& it) const{
	return itptr_ < it.itptr_;
}

bool iterator::operator>=(const iterator& it) const{
	return !(*this < it);
}

bool iterator::operator>(const iterator& it) const{
	return !(*this < it) && !(*this == it);
}

bool iterator::operator<=(const iterator& it) const{
	return !(*this > it);
}

ivy::ivy(int size){
	if (size <= 0)
		throw std::runtime_error("size of ivy must be > 0");
	size_ = size;
	ptr_ = allocate(size_);
	if (ptr_ == -1)
		throw std::runtime_error("Bag allocation in ivy");
}

ivy::ivy(int size, int value) : ivy(size) {
	if (value == -1) {
		make_rand();
	} else {
		if ((value < 0) || (value >99))
			throw std::runtime_error(
				"init value of ivy must be in range [0, 99]");
		for (int i = 0; i < size_; i++)
			(*this)[i] = value;	
	}
}

ivy::ivy(std::initializer_list<int> L){
	size_ = L.size();
	ptr_ = allocate(size_);
	if (ptr_ == -1)
		throw std::runtime_error("Bag allocation in ivy");
	auto p = ptr_;
	for (auto& el:L){
		mem_set_elem(p++, el);
	}
}

ivy::ivy(const ivy& arr){
	size_ = arr.size_;
	ptr_ = allocate(size_);
	
	for (int i = 0; i < arr.size_; i++){
		(*this)[i] = arr[i];
	}
}

ivy::ivy(ivy&& arr) : ivy(arr) {};

ivy ivy::operator=(const ivy& arr){
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

ivy ivy::operator=(ivy&& arr){
	(*this) = arr;
	return *this;
};

ivy::ivy(iterator b_it, iterator e_it){
	int size = e_it - b_it;
	if (size <= 0)
		throw std::runtime_error("second iterator must be greater than first");
	size_ = size;
	ptr_ = allocate(size_);
	if (ptr_ == -1)
		throw std::runtime_error("Bag allocation in ivy");
	
	int i = 0;
	while(b_it != e_it) {
		(*this)[i] = *b_it;
		b_it++;
		i++;
	}
}

void ivy::realloc(int new_size){
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

void ivy::push_back(int v){
	realloc(size_+1);
	(*this)[size_-1] = v;
}

void ivy::push_back(const ivy& arr){
	int arr_size = arr.size();
	int end_pos = size_;
	realloc(size_+arr.size());
	for (int i = 0; i<arr_size; i++){
		(*this)[end_pos+i] = arr[i];
	}
}

void ivy::make_rand(){
	for (int i = ptr_; i < ptr_+size_; i++)
		mem_set_elem(i, rand()%99);
}


int& ivy::operator[](int index) {
	return get_line_ptr(ptr_+index).get_p2y_ref();
}

int ivy::operator[](int index) const {
	return get_line_ptr(ptr_+index).get_p2y_ref();
}

int ivy::size() const {
	return size_;
}

iterator ivy::begin() const {
	return iterator(ptr_);
}

iterator ivy::end() const {
	return iterator(ptr_+size_);
}

ivy::~ivy(){
	deallocate(ptr_);
}




