#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vector.hpp"

typedef struct{
    int a;
    int b;
    int c;
}face_t;  

typedef struct{
    vec2_t points[3];
}trinagle_t;


#endif