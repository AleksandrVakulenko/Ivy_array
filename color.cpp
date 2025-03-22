#include "color.h"
#include "stdlib.h"

void operator<<(color& col, const color_preset& cp){
	switch (cp){
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
		col.r = 0.8;
		col.g = 0;
		col.b = 0;
		break;
	case color_preset::green :
		col.r = 0;
		col.g = 0.8;
		col.b = 0;
		break;
	case color_preset::blue :
		col.r = 0;
		col.g = 0;
		col.b = 0.8;
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