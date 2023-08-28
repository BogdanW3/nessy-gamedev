#include "../lib/gpu.h"
#include <stdlib.h>

int main()
{
    
    Colour_t* colour = (Colour_t*)malloc(sizeof(Colour_t));
    colour->r = 0xFF;
    colour->g = 0xFF;
    colour->b = 0x00;
    draw_pixel(gpu_render_pixel1, 0, 20, colour);
    draw_shape(gpu_render_line2, 10, 20, 200, 100, colour);
    return 0;
}