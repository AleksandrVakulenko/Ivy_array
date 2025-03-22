#pragma once

#include "GLFW/glfw3.h"

static void pause(double time){
    double init_t = glfwGetTime();
    double now_t = init_t;
    while((now_t - init_t) < time)
        now_t = glfwGetTime();
}