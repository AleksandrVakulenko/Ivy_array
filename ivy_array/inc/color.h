#pragma once
#include "GLFW/glfw3.h"

enum class color_preset{
	white, black, red, green, blue, orange, yellow, cian,
	random, green_random
};


struct color {
	color(color_preset cp);
	
	color(float rr, float gg, float bb);
	
	color(const color& col){
		r = col.r;
		g = col.g;
		b = col.b;
	}
	
	float r, g, b;
	
	void apply(){
		glColor3f(r, g, b);
	}
	
};

void operator<<(color& col, const color_preset& cp);







