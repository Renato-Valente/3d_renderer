#ifndef MESH_HPP
#define MESH_HPP

#include "vector.hpp"
#include "triangle.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

int const n_cube_vertices = 101;
extern vec3_t cube_vertices[101];

int const n_cube_faces = 193;
extern face_t cube_faces[n_cube_faces];

typedef struct {
    std::vector <vec3_t> vertices;
    std::vector <face_t> faces;
    vec3_t rotation;

}mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data();
void load_mesh(char* filename);



#endif