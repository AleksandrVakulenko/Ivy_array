#include "vec3.h"
#include "stdlib.h"

float rand_float(){
    float v = 2*(rand()/static_cast<float>(RAND_MAX)-0.5);
    return v;
}

void foo(){
    vec3 A(rand_float(), rand_float(), 0);
    vec3 B = A.find_orth(vec3(1, 0, 0));
    A.print();
    B.print();
    
    std::cout << A.dot_product(B) << "\n\n";
}



int main(){
    
    vec3 A(1,0,0);
    vec3 B(A.find_orth());
    
    A.print();
    B.print();
    (A+B).print();
    
    vec3 C(A+B);
    vec3 C_orth = C.find_orth();
    C_orth = C_orth*10;
    C_orth.print();
    std::cout << C_orth.dot_product(C) << '\n';
    
    std::cout << "!!!!\n\n";
    for (int i = 0; i < 10; i++)
        foo();
    
    
}