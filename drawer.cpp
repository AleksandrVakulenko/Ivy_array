#include <mutex>
#include <thread>
#include <iostream>
#include <list>

#include "GLFW/glfw3.h"
#include "graphics.h"
#include "utils.h"

std::mutex mutex_for_drawer;
std::list<graphic_object*> objs;

void drawer_add(graphic_object* obj_ptr){
	mutex_for_drawer.lock();
	objs.push_back(obj_ptr);
	mutex_for_drawer.unlock();
}

void drawer_delete(graphic_object* obj_ptr){
	mutex_for_drawer.lock();
	for (auto it = objs.begin(); it != objs.end(); it++){
		if (*it == obj_ptr)
			objs.erase(it);
	}
	mutex_for_drawer.unlock();
}

void drawer_draw(){
	mutex_for_drawer.lock();
	for (auto ptr:objs)
		ptr->draw();
	mutex_for_drawer.unlock();
}







