#pragma once
#include <cmath>
#include <iostream>

struct vec3 {
    float x, y, z;

    vec3() : x(0), y(0), z(0) {};
    vec3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
    vec3(const vec3& A) : x(A.x), y(A.y), z(A.z) {}
    vec3 operator=(const vec3& A){
        x = A.x;
        y = A.y;
        z = A.z;
        return *this;
    }
    
    vec3 operator-() const {
        return vec3(-x, -y, -z);
    }
    
    vec3 operator+(const vec3& B) const {
        return vec3(x+B.x, y+B.y, z+B.z);
    }
    
    vec3 operator-(const vec3& B) const {
        return *this+(-B);
    }
    
    vec3 operator/(float b) const {
        return vec3(x/b, y/b, z/b);
    }
    
    vec3 operator*(float b) const {
        return vec3(x*b, y*b, z*b);
    }
    
    float dot_product(const vec3& A) const {
        return x*A.x + y*A.y + z*A.z;
    }
    
    vec3 cross_product(const vec3& B) const {
        vec3 tmp;
        tmp.x = y*B.z - z*B.y;
        tmp.y = z*B.x - x*B.z;
        tmp.z = x*B.y - y*B.x;
        return tmp;
    }
    
    void print(){
        std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    }
    
    float norm(){
        return sqrt(x*x + y*y + z*z);
    }
        
    vec3 find_orth(){
        float vect[3] = {x, y, z};
        float max = 0;
        int index = 0;
        for (int i = 0; i < 3; i++){
            //std::cout << fabs(vect[i]) << '\n';
            if (fabs(vect[i])>max){
                max = fabs(vect[i]);
                index = i;
            }
        }

        int coord1 = (index+1)%3;
        int coord2 = (index+2)%3;

        float orth1[3];
        orth1[coord1] = 1;
        orth1[coord2] = 0;
        orth1[index] = -vect[coord1]/vect[index];

        vec3 out(orth1[0], orth1[1], orth1[2]);
        out = out/out.norm();

        return out;
    }
    
    vec3 find_orth(const vec3& B, const vec3& C) const {
        vec3 orth1 = B.cross_product(C);
        vec3 orth2 = this->cross_product(orth1);
        orth2 = orth2/orth2.norm();
        return orth2;
    }
    
    
};