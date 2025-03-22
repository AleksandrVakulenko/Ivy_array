#include <initializer_list>
#include <stdexcept>
#include "slow_array.h"
#include "graphics.h"
#include "color.h"
#include "drawer.h"
#include "utils.h"

// ADD DEFAULT COLORS
// add elements check

const int max_size = 100;

#ifdef SLOW
	const float mem_delay = 0.005;
	const float elem_delay = 0.05;
#else
	const float mem_delay = 0.002;
	const float elem_delay = 0.02;
#endif

const int min_elem_value = 1;
const int max_elem_value = 99;
const int marg_top = 2;
const int marg_bot = 2;
const int marg_bot_outer = 2;
const int marg_left = 3;
const int marg_right = 1;
const int marg_right_outer = 2;
const int per_elem = 3; // 2 to 6
const int elem_line_width = 4;

const int rows_num = 9;

const int rect_h_size = marg_bot + max_elem_value + marg_top;

const int width = 1000;
const int height = (rect_h_size + marg_bot_outer) * rows_num;



int get_rect_w_size(int size){
	return marg_left + (size)*per_elem + marg_right;
}

rectXY request_memory_for_array(int size){
	// FIXME: allocator func
	int top = 1;
	int bot = top + rect_h_size;
	return rectXY(100,top, 100,bot);
}



	//const float mem_delay = 0.005;
	//const float elem_delay = 0.05;
	//const int max_size = 100;
	//std::vector<int> data;
	//rectXY Rect;
	//std::vector<graphic_object*> Lines;
	
	void slow_array::place_elements(){
		for (int i = 0; i < data.size(); i++){
			int y_bot = Rect.get_down() - marg_bot;
			int y_top = y_bot - data[i] + 2; //FIXME: bot interval
			int x = Rect.get_left() + per_elem*i + marg_left;
			//std::cout << per_elem*i << " " << x  << " " << Rect.get_right()<< "\n";
			auto L = new line(x, y_bot, x, y_top, elem_line_width);
			L->set_color(color_preset::green);
			Lines.push_back(L);
			drawer_add(L);
			pause(elem_delay);
		}
	}
	
	void slow_array::clear_elements(){
		for(int i = data.size()-1; i >= 0; i--){
			auto line_ptr = Lines[i];
			drawer_delete(line_ptr);
			delete line_ptr;
			pause(elem_delay);
		}
	}
	
	void slow_array::restore_lines_color(){
		for(int i = 0; i < data.size(); i++){
			Lines[i]->set_color(color_preset::green);
		}
	}
	
	void slow_array::place_rect(){
		int final_size = get_rect_w_size(data.size());
		int current_size = Rect.get_w();
		while (current_size < final_size){
			Rect.move_right(1);
			current_size = Rect.get_w();
			pause(mem_delay);
		}
		Rect.set_color(color_preset::blue);
	}
	
	void slow_array::clear_rect(){
		Rect.set_color(color_preset::red);
		int final_size = 0;
		int current_size = Rect.get_w();
		while (current_size > final_size){
			Rect.move_right(-1);
			current_size = Rect.get_w();
			pause(mem_delay);
		}
		drawer_delete(&Rect);
	}
	
	
	
	
	//------------------------------------------------------------------
	slow_array::slow_array(std::initializer_list<int> L) {
		if (L.size() > max_size)
			throw std::runtime_error(
				"Max number of elements exceeded in slow_array");
		data.insert(data.end(), L.begin(), L.end());
		Rect = request_memory_for_array(data.size());
		Rect.set_color(color_preset::red);
		drawer_add(&Rect);
		
		place_rect();
		place_elements();
	}
	
	int slow_array::operator[](int index){
		restore_lines_color();
		Lines[index]->set_color(color_preset::red);
		pause(elem_delay);
		return data[index];
	}
	
	int slow_array::size(){
		return data.size();
	}
	
	
	
	slow_array::~slow_array(){
		restore_lines_color();
		clear_elements();
		clear_rect();
	}






