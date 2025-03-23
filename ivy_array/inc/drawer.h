#pragma once

#include "graphics.h"

void drawer_draw();

void drawer_add(graphic_object* obj_ptr);

void drawer_delete(graphic_object* obj_ptr);

void drawer_lock();

void drawer_unlock();

