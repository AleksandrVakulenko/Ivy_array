#include "GLFW/glfw3.h"
#include <iostream>
#include <vector>
#include "graphics.h"
#include "utils.h"
#include "drawer.h"
#include "slow_array.h"
#include <thread>


void user_func();

bool user_func_active = true;

void user_func_wrapper(){
	user_func();
	user_func_active = false;
}

int main() {
		int width = get_window_w();
		int height = get_window_h();
		
		glfwInit();
		GLFWwindow* window = glfwCreateWindow(width, height,
			"Slow array DEMO", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glLoadIdentity();
		glScalef(1/(width/2.0), -1/(height/2.0), 1);
		glTranslatef(-width/2.0, -height/2.0, 0);

		std::cout << "RUN USER THREAD\n";
		std::thread draw_thread(user_func_wrapper);
		draw_thread.detach();
		

		/*
        std::vector<line> l_arr;
        for (int i = 0; i < 10; i++){
            float x = 500 + 6*i;
            l_arr.push_back(line(x, 0, x, i/9.0*100, 4));
        }
		*/       
		

        while(!glfwWindowShouldClose(window) && user_func_active)
        {
				glfwPollEvents();
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor(0.5, 0.5, 0.5, 1);

			
				/*
				line Lx(0, height/2, width, height/2);
				line Ly(width/2, 0, width/2, height);
				glColor3f(1, 0, 0);
                Lx.draw();
                glColor3f(0, 0, 1);
                Ly.draw();
				*/
                
                pause(0.05);

				drawer_draw();

                glfwSwapBuffers(window);
        }

        return 0;
}



