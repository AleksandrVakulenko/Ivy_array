mkdir obj_files
g++ main.cpp -c -o obj_files\main.o
g++ drawer.cpp -c -o obj_files\drawer.o
g++ color.cpp -c -o obj_files\color.o
g++ memory.cpp -DSLOW -c -o obj_files\memory.o 

ar rcs lib\libslowarr.a .\obj_files\main.o .\obj_files\color.o .\obj_files\drawer.o .\obj_files\memory.o

rmdir /s /q .\obj_files