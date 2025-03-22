#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>


struct point{
	float x,y;
};

struct color{
	float r, g, b;
};

struct triangle{
	color col;
	point a,b,c;
	void draw(){
		glColor3f(col.r, col.g, col.b);
		glBegin(GL_TRIANGLES);
		glVertex2f(a.x, a.y);
		glVertex2f(b.x, b.y);
		glVertex2f(c.x, c.y);
		glEnd();
	}
};

struct circle {
	float x, y, r;
	std::vector<triangle> tris;
	
	float sx = 0.05, sy = 0.05;
	
	circle(float x, float y, float r){
		int N = 20;
		for (int i = 0; i < N; i++){
			float angle1 = 2*M_PI/static_cast<float>(N)*i;
			float angle2 = 2*M_PI/static_cast<float>(N)*(i+1);
			float x1 = r*sin(angle1) + x;
			float y1 = r*cos(angle1) + x;
			float x2 = r*sin(angle2) + x;
			float y2 = r*cos(angle2) + x;
			triangle T = {{0.5, 0.0, 0.0}, {x, y}, {x1,y1}, {x2, y2}};
			tris.push_back(T);
		}
	}
	void draw(){
		for (auto t:tris){
			t.draw();
		}
	}
};

triangle T1 = {{0.5, 0.0, 0.0}, {-0.5,-0.5}, {0.5,-0.5}, {0.0, 0.5}};
triangle T2 = {{0.0, 0.0, 0.5}, {0.25,0.25}, {-0.25,0.25}, {-0.0,-0.25}};
circle C1(0.8,0.8,0.1);

float angle = 0;

void draw(){
	angle += 0.5;
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.5, 0.5, 0.5, 1); // black
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	if (angle > 360)
		angle -= 360;
	if (angle > 90 && angle < 270){
		T1.draw();
		T2.draw();
	} else {
		T2.draw();
		T1.draw();
	}
	
	glPopMatrix();
	
	
	C1.draw();




}











