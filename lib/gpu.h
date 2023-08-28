#ifndef GPU_H
#define GPU_H

struct Colour {
    char r;
    char g;
    char b;
};
#define Colour_t struct Colour

extern char* gpu_status;
extern char* gpu_render_pixel1;
extern char* gpu_render_pixel2;
extern char* gpu_render_line1;
extern char* gpu_render_line2;
extern char* gpu_render_rect1;
extern char* gpu_render_rect2;

void draw_pixel(char* where, int x, int y, Colour_t* colour);
void draw_shape(char* where, int x1, int y1, int x2, int y2, Colour_t* colour);

#endif