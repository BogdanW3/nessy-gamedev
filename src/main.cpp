#include "../lib/gpu.hpp"
#include <stdlib.h>

int main()
{
    
    Colour* colour = (Colour*)malloc(sizeof(Colour));
    colour->r = 0xFF;
    colour->g = 0xFF;
    colour->b = 0x00;
    draw_pixel(GPU_RENDER_PIXEL1, 400, 20, colour);
    draw_shape(GPU_RENDER_LINE2, 10, 20, 200, 100, colour);
    return 0;
}