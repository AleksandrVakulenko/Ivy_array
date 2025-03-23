@echo off
set opt_lvl=-O2
set srcf=.\ivy_array\src
set incf=.\ivy_array\inc
set glfwincf=.
set obj_folder=.\ivy_array\obj_files
set lib_folder=.\lib

mkdir .\ivy_array\obj_files

@echo on
g++ %srcf%\main.cpp   -I%incf% -I%glfwincf% %opt_lvl% -c -o %obj_folder%\main.o
g++ %srcf%\drawer.cpp -I%incf% -I%glfwincf% %opt_lvl% -c -o %obj_folder%\drawer.o
g++ %srcf%\color.cpp  -I%incf% -I%glfwincf% %opt_lvl% -c -o %obj_folder%\color.o
g++ %srcf%\memory.cpp -I%incf% -I%glfwincf% %opt_lvl% -c -o %obj_folder%\memory.o -DSLOW
g++ %srcf%\ivy.cpp    -I%incf% -I%glfwincf% %opt_lvl% -c -o %obj_folder%\ivy.o

ar rcs %lib_folder%\libivyarr.a %obj_folder%\main.o %obj_folder%\color.o %obj_folder%\drawer.o %obj_folder%\memory.o %obj_folder%\ivy.o

@echo off
rmdir /s /q %obj_folder%