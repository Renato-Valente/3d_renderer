#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include "display.hpp"
#include "vector.hpp"
#include "mesh.hpp"
#include "triangle.hpp"

trinagle_t trinangles_to_render[n_cube_faces];
vec3_t cube_rotation = {0,0,0};

bool is_running = false;
int const fps = 60;
int const frame_target_time = 1000/fps;
int last_frame_time = 0;


void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
    }
}

void setup(){
      // Allocate the required memory in bytes to hold the color buffer
    //color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    //load_cube_mesh_data();
    load_mesh("cube.obj");
}
void update(){
    int timeToWait = frame_target_time - (SDL_GetTicks() - last_frame_time);

    if(timeToWait > 0 && timeToWait<=frame_target_time){
        SDL_Delay(timeToWait);
    }

    mesh.rotation.x+=0.01;
    mesh.rotation.y+=0.00;
    mesh.rotation.z+=0.00;

    for(int i = 0; i < mesh.faces.size(); i++){
        face_t mesh_face = mesh.faces[i];
        trinagle_t trinagle;
        
        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];


        for(int j = 0; j < 3; j++){
            face_vertices[j] = vec3_rotate_x(face_vertices[j],mesh.rotation.x);
            face_vertices[j] = vec3_rotate_y(face_vertices[j],mesh.rotation.y);
            face_vertices[j] = vec3_rotate_z(face_vertices[j],mesh.rotation.z);

            face_vertices[j].z += (-5);
            vec2_t projected_point = project(face_vertices[j]);
            projected_point.x += (window_width/2);
            projected_point.y += (window_height/2);
            trinagle.points[j] = projected_point;
        }
        trinangles_to_render[i] = trinagle;
    }

    last_frame_time = SDL_GetTicks();
}


void render(){
    render_color_buffer();
    clear_color_buffer(0xFF000000);

    //drawRect(0,0,50,50,0xFFFFFF00);

    //drawLine(0,0,800,600,0xFF00FF00);

    for(int i = 0; i<mesh.faces.size(); i++){
        //drawRect(trinangles_to_render[i].points[0].x,trinangles_to_render[i].points[0].y,3,3,0xFFFFFF00);
        //drawRect(trinangles_to_render[i].points[1].x,trinangles_to_render[i].points[1].y,3,3,0xFFFFFF00);
        //drawRect(trinangles_to_render[i].points[2].x,trinangles_to_render[i].points[2].y,3,3,0xFFFFFF00);

        trinagle_t triangle = trinangles_to_render[i];
        drawLine(triangle.points[0].x,triangle.points[0].y,triangle.points[1].x,triangle.points[1].y,0xFFF542C2);
        drawLine(triangle.points[1].x,triangle.points[1].y,triangle.points[2].x,triangle.points[2].y,0xFFF542C2);
        drawLine(triangle.points[2].x,triangle.points[2].y,triangle.points[0].x,triangle.points[0].y,0xFFF542C2);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    mesh.faces.clear();
    mesh.vertices.clear();

    return 0;
}