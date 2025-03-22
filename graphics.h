#pragma once
#include "vec3.h"
#include "GLFW/glfw3.h"
#include "color.h"
#include <vector>
#include <iostream>
#include <utility>




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
    float width = 0.2;
	
	void draw_internal() override {
        vec3 line_v(p2-p1);
        vec3 orth = line_v.find_orth(vec3(1, 0, 0), vec3(0, 1, 0));
        orth = orth*width/2;
        vec3 points[4] = {p1+orth, p1-orth, p2+orth, p2-orth};
        glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < 4; i++) {
                glVertex2f(points[i].x, points[i].y);
            }
        glEnd();
    }


    public:
    line(float x1, float y1, float x2, float y2, float w = 2) :
        width(w), p1(x1, y1, 0), p2(x2, y2, 0) {}
	line(const vec3& v1, const vec3& v2, float w = 2) : 
		width(w), p1(v1), p2(v2) {}
	line(const line& L) : width(L.width), p1(L.p1), p2(L.p2) {}
	line operator=(const line& L){
		width = L.width;
		p1 = L.p1;
		p2 = L.p2;
		return *this;
	}
	
	void set_h(int v){
		p2 = p1 + vec3(0, v, 0);
	}
	
	int get_h(){
		return (p1-p2).y;
	}
	
};


class rect final : public graphic_object {
	std::vector<line> lines;

	void draw_internal() override {
		for(auto L:lines)
			L.draw(col);
	}
	
	
	public:
	
	rect(float x1, float y1, float x2, float y2, float width = 2){
		float w = 2;
		lines.push_back(line(x1, y1, x2, y1));
		lines.push_back(line(x2, y1, x2, y2));
		lines.push_back(line(x2, y2, x1, y2));
		lines.push_back(line(x1, y2, x1, y1));
	}
	
	void set_first_corner(float x1, float y1){
		
	}
};



class rectXY final : public graphic_object {
	vec3 v1, v2;
	
	void draw_internal() override {
		line(v1.x, v1.y, v2.x, v1.y).draw(col);
		line(v2.x, v1.y, v2.x, v2.y).draw(col);
		line(v2.x, v2.y, v1.x, v2.y).draw(col);
		line(v1.x, v2.y, v1.x, v1.y).draw(col);
	}
	
	void check_sides(){
		if (v1.y > v2.y)
			std::swap(v1.y, v2.y);
		if (v1.x > v2.x)
			std::swap(v1.x, v2.x);
	}
	
	
	
	public:
	rectXY(){
		v1 = v2 = vec3(0,0,0);
	}
	
	rectXY(vec3 vv1, vec3 vv2, float width = 2){
		v1 = vv1;
		v2 = vv2;

	}
	
	rectXY(float x1, float y1, float x2, float y2, float width = 2) : 
		rectXY(vec3(x1, y1, 0), vec3(x2, y2, 0), width) {}
	
	void move_left(float d){
		v1.x += d;
		check_sides();
	}
	void move_right(float d){
		v2.x += d;
		check_sides();
	}
	void move_up(float d){
		v1.y += d;
		check_sides();
	}
	void move_down(float d){
		v2.y += d;
		check_sides();
	}
	
	float get_w(){
		return v2.x - v1.x;
	}
	
	float get_h(){
		return v2.y - v1.y;
	}
	
	float get_left(){
		return v1.x;
	}
	float get_right(){
		return v2.x;
	}
	float get_up(){
		return v1.y;
	}
	float get_down(){
		return v2.y;
	}
		
};











