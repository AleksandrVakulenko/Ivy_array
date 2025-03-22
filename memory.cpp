#include <initializer_list>
#include <stdexcept>
#include "slow_array.h"
#include "graphics.h"
#include "color.h"
#include "drawer.h"
#include "utils.h"
#include <vector>
#include "memory.h"
#include <stdlib.h>


#ifdef SLOW
	const float allocate_mem_delay = 0.005;
	const float elem_delay = 0.05;
#else
	const float allocate_mem_delay = 0.002;
	const float elem_delay = 0.005;
#endif


const int min_elem_value = 0;
const int max_elem_value = 99;

const int row_margin_top = 3;
const int row_margin_bot = 2;

const int elements_per_row_number = 500;
const int total_rows_num = 11;
const int elements_row_inc = row_margin_top + max_elem_value + row_margin_bot;
const int elements_incol_inc = 4;
const int elem_line_width = 3;
const int row_left_shift = elements_incol_inc/2;

const int width = elements_incol_inc*elements_per_row_number + row_left_shift;
const int height = elements_row_inc * total_rows_num;



const int memory_size = total_rows_num * elements_per_row_number;

std::vector<int> allocation_sizes;
std::vector<bool> memory_flag;
std::vector<line*> Lines;

color_preset color_for_free_mem = color_preset::black;
color_preset color_for_used_mem = color_preset::green;
color_preset color_for_used_elem = color_preset::blue;
color_preset color_for_special = color_preset::red;

int get_window_w(){
	return width;
}

int get_window_h(){
	return height;
}

void repaint_lines(){
	for (int i = 0; i < Lines.size(); i++){
		if (memory_flag[i])
			Lines[i]->set_color(color_for_used_mem);
		else
			Lines[i]->set_color(color_for_free_mem);
	}
}

void init_memory(){
	for (int i = 0; i < memory_size; i++){
		int elem_row = (i / elements_per_row_number + 1) * elements_row_inc;
		int elem_col = (i % elements_per_row_number) * elements_incol_inc + row_left_shift;
		int x = elem_col;
		int y_bot = elem_row;
		int y_top = y_bot - (0) - 1;
		memory_flag.push_back(false);
		allocation_sizes.push_back(0);
		auto L = new line(x, y_bot, x, y_top, elem_line_width);
		Lines.push_back(L);
		L->set_color(color_for_free_mem);
		drawer_add(L);
	}
	
}

void mod_lines(){
	for (int i = 0; i < memory_size; i++){
		int el_v = rand()%99;
		Lines[i]->set_h(-el_v-1);
		memory_flag[i] = true;
		//std::cout << el_v << " " << Lines[i]->get_h()-1 << '\n';
		pause(elem_delay);
	}
	
}

void set_elem(int adr, int v){
	if (adr < 0 || adr >= memory_size)
		throw std::runtime_error("segmentation fault");
	if (v < min_elem_value)
		v = min_elem_value;
	if (v > max_elem_value)
		v = max_elem_value;
	repaint_lines();
	Lines[adr]->set_color(color_for_used_elem);
	Lines[adr]->set_h(-v);
	pause(elem_delay);
}

int get_elem(int adr){
	if (adr < 0 || adr >= memory_size)
		throw std::runtime_error("segmentation fault");
	return Lines[adr]->get_h();
	pause(elem_delay);
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
		throw std::runtime_error("Not enought memory (1)");
	
	//print_mem_map();
	
	int adr = find_free_block(size);
	std::cout << adr << '\n';
	if (adr == -1)
		throw std::runtime_error("Not enought memory (2)");
	
	allocation_sizes[adr] = size;
	for (int i = adr; i < adr+size; i++){
		memory_flag[i] = true;
		Lines[i]->set_color(color_for_used_mem);
		pause(allocate_mem_delay);
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
		Lines[i]->set_color(color_for_free_mem);
		pause(allocate_mem_delay);
	}
}



















