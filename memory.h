#pragma once

int get_window_w();
int get_window_h();

void init_memory();
void mod_lines();
void repaint_lines();

int allocate(int size);
void deallocate(int ptr);

void set_elem(int adr, int v);
int get_elem(int adr);

