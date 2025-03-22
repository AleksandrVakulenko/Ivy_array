#include <iostream>
#include "utils.h"
#include "graphics.h"
#include "drawer.h"
#include "slow_array.h"
#include "memory.h"
#include <vector>
#include "stdlib.h"

std::vector<int> ptrs;

void alloc(){
	int size = rand()%200+20;
	std::cout << "Size needed " << size << '\n';
	int ptr = allocate(size);
	ptrs.push_back(ptr);
	
	for (int j = ptr; j < ptr+size; j++){
		set_elem(j, rand()%99);
	}
}

void dealloc(){
	int i = rand()%ptrs.size();
	deallocate(ptrs[i]);
	ptrs.erase(ptrs.begin() + i);
}

void user_func(){
	
	#if 0
	slow_array arr = {99, 1, 2, 3, 5, 6, 22, 33, 44, 55, 66, 77, 4, 5, 6, 7, 8, 9, 10, 33, 44, 99,
					33, 12,43,46,75,86,34,45,75,35,68,35,57,67,90};
	
	for (int i = 0; i < arr.size(); i+=1)
		arr[i];
	
	
	#endif
	
	
	init_memory();
	pause(1.5);
	
	//mod_lines();
	//repaint_lines();
	//pause(1.5);
	
	
	alloc();
	alloc();
	alloc();
	alloc();
	alloc();
	alloc();
	dealloc();
	alloc();
	alloc();
	dealloc();
	alloc();
	dealloc();
	dealloc();
	dealloc();
	alloc();
	alloc();
	dealloc();
	dealloc();
	alloc();
	dealloc();
	dealloc();
	dealloc();
	alloc();
	dealloc();
	alloc();
	dealloc();
	dealloc();
	dealloc();
		
	
	pause(2);
}







