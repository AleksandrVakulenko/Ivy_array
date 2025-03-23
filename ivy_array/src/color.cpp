#include <vector>
#include "color.h"
#include "stdlib.h"


std::vector<float> R_arr = {244, 190, 137, 105, 161,  49,  50, 231, 241, 196,  82,  32, 235,  36};
std::vector<float> G_arr = {170, 192, 243, 206, 248, 234, 222, 147,  70,  50, 198, 237, 204, 246}; 
std::vector<float> B_arr = { 56,  36,  36,  11,  80,  20, 128, 240, 190, 151,  24, 144,  11,  78};

int i = 0;
int i_prev = 0;

void operator<<(color& col, const color_preset& cp){
	switch (cp){
	case color_preset::green_random:
	{
		//int i = rand()%R_arr.size();
		//if (i == i_prev){
		//	i = (i+1)%R_arr.size();
		//}
		col.r = R_arr[i]/255.0;
		col.g = G_arr[i]/255.0;
		col.b = B_arr[i]/255.0;
		i = (i+1)%R_arr.size();
		break;
	}
	case color_preset::random:
		col.r = rand()/static_cast<float>(RAND_MAX)*0.8+0.2;
		col.g = rand()/static_cast<float>(RAND_MAX)*0.8+0.2;
		col.b = rand()/static_cast<float>(RAND_MAX)*0.8+0.2;
		break;
	case color_preset::white:
		col.r = 1;
		col.g = 1;
		col.b = 1;
		break;
	case color_preset::black:
		col.r = 0;
		col.g = 0;
		col.b = 0;
		break;
	case color_preset::red :
		col.r = 1;
		col.g = 0;
		col.b = 0;
		break;
	case color_preset::green :
		col.r = 0;
		col.g = 1;
		col.b = 0;
		break;
	case color_preset::blue :
		col.r = 0;
		col.g = 0;
		col.b = 1;
		break;
	case color_preset::orange :
		col.r = 1;
		col.g = 0.78;
		col.b = 0;
		break;
	case color_preset::yellow :
		col.r = 1;
		col.g = 1;
		col.b = 0;
		break;
	case color_preset::cian :
		col.r = 0;
		col.g = 1;
		col.b = 1;
		break;
	}
}

color::color (color_preset cp){
	*this << cp;
}

color::color(float rr, float gg, float bb){
	r = rr;
	g = gg;
	b = bb;	
}