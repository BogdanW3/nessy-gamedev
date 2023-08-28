#include "gpu.h"

/*
 Some info:
 The pixel draw registers are at 0x4001 and 0x4002
 The line draw registers are at 0x4003 and 0x4004
 The rect draw registers are at 0x4005 and 0x4006
 The status register is at 0x4000, read only,
 it contains the ready statuses of all renderers,
 and the NMI status
 Each register is 8 bits wide
 Data is written to registers in the order of:
  Colour, all 3 parts in separate writes
  X1, low then high
  Y1, low then high
  if applicable:
    X2, low then high
    Y2, low then high
*/

char* gpu_status =          (char*)0x4000;
char* gpu_render_pixel1 =   (char*)0x4001;
char* gpu_render_pixel2 =   (char*)0x4002;
char* gpu_render_line1 =    (char*)0x4003;
char* gpu_render_line2 =    (char*)0x4004;
char* gpu_render_rect1 =    (char*)0x4005;
char* gpu_render_rect2 =    (char*)0x4006;

void draw_pixel(char* where, int x, int y, Colour_t* colour)
{
    while (!(*gpu_status & (1 << (where - gpu_status))));
    *where = colour->r;
    *where = colour->g;
    *where = colour->b;
    *where = x & 0xFF;
    *where = (x >> 8) & 0xFF;
    *where = y & 0xFF;
    *where = (y >> 8) & 0xFF;

}

void draw_shape(char* where, int x1, int y1, int x2, int y2, Colour_t* colour)
{
    while (!(*gpu_status & (1 << (where - gpu_status))));
    *where = colour->r;
    *where = colour->g;
    *where = colour->b;
    *where = x1 & 0xFF;
    *where = (x1 >> 8) & 0xFF;
    *where = y1 & 0xFF;
    *where = (y1 >> 8) & 0xFF;
    *where = x2 & 0xFF;
    *where = (x2 >> 8) & 0xFF;
    *where = y2 & 0xFF;
    *where = (y2 >> 8) & 0xFF;
}