#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <stdlib.h>

#include "memory.h"
#include "graphics.h"
#include "color.h"
#include "drawer.h"
#include "utils.h"




#ifdef SLOW
	const float allocate_mem_delay = 0.006;
	const float elem_delay = 0.015;
#else
	const float allocate_mem_delay = 0.002;
	const float elem_delay = 0.005;
#endif


const int min_elem_value = 0;
const int max_elem_value = 99;

const int row_margin_top = 3;
const int row_margin_bot = 2;

const int elements_per_row_number = 256+128;
const int total_rows_num = 9;
const int elements_row_inc = row_margin_top + max_elem_value + row_margin_bot;
const int elements_incol_inc = 4;
const int elem_line_width = 3;
const int row_left_shift = elements_incol_inc/2;

const int width = elements_incol_inc*elements_per_row_number + row_left_shift;
const int height = elements_row_inc * total_rows_num;



const int memory_size = total_rows_num * elements_per_row_number;

bool is_init_memory = false;
std::vector<color> allocation_color;
std::vector<int> allocation_sizes;
std::vector<bool> memory_flag;
std::vector<line*> Lines;

color color_for_free_mem = color(color_preset::black);
color color_for_used_mem = color(color_preset::green);
color color_for_used_elem = color(color_preset::blue);
color color_for_special = color(color_preset::red);

int get_window_w(){
	return width;
}

int get_window_h(){
	return height;
}

int get_mem_size(){
	return memory_size;
}

void repaint_lines(){
	/*
	for (int i = 0; i < Lines.size(); i++){
		if (memory_flag[i])
			Lines[i]->set_color(color_for_used_mem);
		else
			Lines[i]->set_color(color_for_free_mem);
	}
	*/
	for (int i = 0; i < Lines.size(); i++){
		Lines[i]->set_color(allocation_color[i]);
	}
}

void init_memory(){
	if (is_init_memory)
		return;
	is_init_memory = true;
	for (int i = 0; i < memory_size; i++){
		int elem_row = (i / elements_per_row_number + 1) * elements_row_inc;
		int elem_col = (i % elements_per_row_number) * elements_incol_inc + row_left_shift;
		int x = elem_col;
		int y_bot = elem_row;
		int y_top = y_bot - (0) - 1;
		memory_flag.push_back(false);
		allocation_sizes.push_back(0);
		allocation_color.push_back(color_for_free_mem);
		auto L = new line(x, y_bot, x, y_top, elem_line_width);
		Lines.push_back(L);
		repaint_lines();
		drawer_add(L);
	}
	
}

void mem_set_elem(int adr, int v){
	if (adr < 0 || adr >= memory_size)
		throw std::runtime_error("segmentation fault");
	if (v < min_elem_value)
		v = min_elem_value;
	if (v > max_elem_value)
		v = max_elem_value;
	repaint_lines();
	Lines[adr]->set_color(color_for_used_elem);
	Lines[adr]->set_h(v);
	pause(elem_delay);
}

int mem_get_elem(int adr){
	if (adr < 0 || adr >= memory_size)
		throw std::runtime_error("segmentation fault");
	repaint_lines();
	Lines[adr]->set_color(color_for_used_elem);
	pause(elem_delay);	
	return Lines[adr]->get_h();
}

line& get_line_ptr(int index){
	if (index < 0 || index >= memory_size)
		throw std::runtime_error("segmentation fault");
	repaint_lines();
	Lines[index]->set_color(color_for_used_elem);
	pause(elem_delay);
	return *Lines[index];
}

int find_free_block(int size){
	for (int i = 0; i <= memory_size-size; i++){
		bool used = false;
		for (int j = i; j < i+size; j++){
			auto flag = memory_flag[j];
			if (flag == true){
				used = true;
			}
		}
		if (!used)
			return i;
	}
	return -1;
}

void print_mem_map(){
	for (int i = 0; i < memory_flag.size(); i++){
		std::cout << (memory_flag[i]? "+":"-");
	}
	std::cout << '\n';
}



int allocate(int size){
	if (size > memory_size)
		throw std::runtime_error("Not enought memory");
	//print_mem_map();
	int adr = find_free_block(size);
	//std::cout << adr << '\n';
	if (adr != -1) {
		allocation_sizes[adr] = size;
		auto col = color(color_preset::green_random);
		for (int i = adr; i < adr+size; i++){
			memory_flag[i] = true;
			//Lines[i]->set_color(color_for_used_mem);
			allocation_color[i] = col;
			Lines[i]->set_color(allocation_color[i]);
			pause(allocate_mem_delay);
		}
	}
	return adr;
}


void deallocate(int ptr){
	if (allocation_sizes[ptr] == 0)
		throw std::runtime_error("bad deallocation");
	int size = allocation_sizes[ptr];
	allocation_sizes[ptr] = 0;
	for (int i = ptr; i < ptr+size; i++){
		memory_flag[i] = false;
		allocation_color[i] = color_for_free_mem;
		Lines[i]->set_color(color_for_free_mem);
		pause(allocate_mem_delay);
	}
}



















