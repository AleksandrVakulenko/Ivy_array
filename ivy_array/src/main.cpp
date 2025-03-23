#include "GLFW/glfw3.h"
#include <iostream>
#include <vector>
#include <thread>

#include "drawer.h"
#include "memory.h"

void user_thread();

bool user_thread_active = true;

void user_thread_wrapper(){
	user_thread();
	user_thread_active = false;
	std::cout << "STOP USER THREAD\n";
	print_allocs_num();
}

int main() {
		int width = get_window_w();
		int height = get_window_h();
		
		glfwInit();
		GLFWwindow* window = glfwCreateWindow(width, height,
			"Ivy memory map V1.1.0", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glLoadIdentity();
		glScalef(1/(width/2.0), -1/(height/2.0), 1);
		glTranslatef(-width/2.0, -height/2.0, 0);

		init_memory();
		std::cout << "Window size: " << width << "x" << height << '\n';
		std::cout << "Memory size: " << get_mem_size() << '\n';

		std::cout << "RUN USER THREAD\n";
		std::thread draw_thread(user_thread_wrapper);
		draw_thread.detach();


        while(!glfwWindowShouldClose(window) && user_thread_active)
        {
				glfwPollEvents();
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor(77/255.0, 134/255.0, 163/255.0, 1);

				drawer_draw();

                glfwSwapBuffers(window);
        }

        return 0;
}



