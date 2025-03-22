#include "color.h"

void operator<<(color& col, const color_preset& cp){
	switch (cp){
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