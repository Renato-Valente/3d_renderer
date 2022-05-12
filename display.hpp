#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "vector.hpp"
#include <math.h>


extern SDL_Window* window; 
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int const window_width;
extern int const window_height;
extern int const fov_factor;
extern vec3_t camera;

bool initialize_window(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void drawRect(int x, int y, int width, int height, uint32_t color);
void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
vec2_t project(vec3_t point);
void destroy_window(void);

#endif