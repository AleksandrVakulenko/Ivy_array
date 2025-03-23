mkdir obj_files
g++ main.cpp -O2 -c -o obj_files\main.o
g++ drawer.cpp -O2 -c -o obj_files\drawer.o
g++ color.cpp -O2 -c -o obj_files\color.o
g++ memory.cpp -O2 -c -o obj_files\memory.o 
g++ ivy.cpp -O2 -c -o obj_files\ivy.o

ar rcs lib\libivyarr.a .\obj_files\main.o .\obj_files\color.o .\obj_files\drawer.o .\obj_files\memory.o .\obj_files\ivy.o

rmdir /s /q .\obj_files