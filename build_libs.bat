mkdir obj_files
g++ main.cpp -O2 -c -o obj_files\main.o
g++ drawer.cpp -O2 -c -o obj_files\drawer.o
g++ color.cpp -O2 -c -o obj_files\color.o
g++ memory.cpp -O2 -DSLOW -c -o obj_files\memory.o 

ar rcs lib\libslowarr.a .\obj_files\main.o .\obj_files\color.o .\obj_files\drawer.o .\obj_files\memory.o

rmdir /s /q .\obj_files