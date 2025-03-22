#pragma once
#include "graphics.h"

int get_window_w();
int get_window_h();
int get_mem_size();

void init_memory();
int allocate(int size);
void deallocate(int ptr);

void mem_set_elem(int adr, int v);
int mem_get_elem(int adr);

line& get_line_ptr(int index);
