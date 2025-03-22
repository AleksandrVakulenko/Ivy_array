#pragma once
#include <initializer_list>
#include "graphics.h"

int get_window_w();
int get_window_h();


class slow_array final {
	std::vector<int> data;
	rectXY Rect;
	std::vector<graphic_object*> Lines;
	
	void place_elements();
	
	void clear_elements();
	
	void restore_lines_color();
	
	void place_rect();
	
	void clear_rect();
	
	
	public: //------------------------------------------------------------------
	
	slow_array(std::initializer_list<int> L);
	
	int operator[](int index);
	
	int size();
	
	~slow_array();
};



