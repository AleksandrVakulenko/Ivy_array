#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include "GLFW/glfw3.h"
#include "vec3.h"
#include "color.h"


/*
Этот код был первый в проекте, и он же был последний,
так что тут все недостатки плохого планирования и последующей
подгонки под остальную часть.
*/

class graphic_object{
	virtual void draw_internal() = 0;
	
protected:
	color col;
	
public:
	graphic_object() : col(0, 0, 0) {}
	
	void draw() {
		col.apply();
		draw_internal();
	};
	
	void draw(color col){
		col.apply();
		draw_internal();
	}
	
	void set_color(float R, float G, float B){
		col = color(R, G, B);
	}
	
	void set_color(color col_in){
		col = col_in;
	}
	
	void set_color(color_preset cp){
		col << cp;
	}

	void print_col(){
		std::cout << col.r << " " << col.g << " " << col.b << '\n';
	}

    ~graphic_object(){}
};


class line final : public graphic_object{
    vec3 p1, p2;
	int value = 0;
    float width = 0.2;
	
	void draw_internal() override {
		//vec3 p2_save = p2;
		//p2.y = p2.y - 2*(p2.y-p1.y);
		p2.y = p1.y - value;
        vec3 line_v(p2-p1);
        vec3 orth = line_v.find_orth(vec3(1, 0, 0), vec3(0, 1, 0));
        orth = orth*width/2;
        vec3 points[4] = {p1+orth, p1-orth, p2+orth, p2-orth};
        glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < 4; i++) {
                glVertex2f(points[i].x, points[i].y);
            }
        glEnd();
		//p2 = p2_save;
    }


    public:
    line(float x1, float y1, float x2, float y2, float w = 2) :
        width(w), p1(x1, y1, 0), p2(x2, y2, 0)
	{
		value = p1.y -p2.y;
	}
	
	line(const vec3& v1, const vec3& v2, float w = 2) : 
		width(w), p1(v1), p2(v2)
	{
		value = p1.y -p2.y;	
	}
	
	void set_h(int v){
		value = v;
		p2.y = p1.y - value;
	}
	
	int get_h(){
		return (p1-p2).y;
	}
	
	int& get_p2y_ref(){
		return value;
	}
	
};










