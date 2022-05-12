#include "display.hpp"
#include <stdio.h>

SDL_Window* window = NULL; 
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int const window_width = 800;
int const window_height = 600;
int const fov_factor = 640;
vec3_t camera = {0,0,5.0};


bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    // Create a SDL Window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }
    
    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
    //for (int y = 0; y < window_height; y++) {
      //  for (int x = 0; x < window_width; x++) {
        //    color_buffer[(window_width * y) + x] = color;
       // }
   // }

   int x = 0;
   while(x<window_width*window_height){
       color_buffer[x] = color;
       x++;
   }
}

void draw_pixel(int x, int y, uint32_t color){
    if(x >= 0 && x < window_width && y >= 0 && y < window_height){
        color_buffer[(window_width * y) + x] = color;
    }
}

void drawRect(int x, int y, int width, int height, uint32_t color){
    //color_buffer[window_width*y + x] = color;
    int rectX = x;
    int rectY = y;
    while(rectY<=y+height){
        rectX = x;
        while(rectX<=x+width){
            //color_buffer[(window_width * rectY) + rectX] = color;
            draw_pixel(rectX,rectY,color);
            rectX++;
        }
        rectY++;
    }
}

void drawLine(int x0, int y0, int x1, int y1, uint32_t color){
    int delta_x = x1 - x0;
    int delta_y = y1 - y0;
    int longest_side;

    if(delta_x > delta_y){
        longest_side = delta_x;
    }
    else{
        longest_side = delta_y;
    }

    float x_increment = delta_x / (float)longest_side;
    float y_increment = delta_y / (float)longest_side;

    float currentX = (float)x0;
    float currentY = (float)y0;

    for(int i = 0; i<longest_side; i++){
        draw_pixel(round(currentX),round(currentY),color);
        currentX += x_increment;
        currentY += y_increment;
    }


}

vec2_t project(vec3_t point){
    vec2_t projected_point = {
       fov_factor * point.x / point.z,
       fov_factor * point.y / point.z
    };

    return projected_point;
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}