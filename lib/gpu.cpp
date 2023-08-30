#include "gpu.hpp"

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

void draw_pixel(char *where, int x, int y, Colour *colour)
{
	while (!(*GPU_STATUS & (1 << (where - GPU_STATUS))));
	*where = colour->r;
	*where = colour->g;
	*where = colour->b;
	*where = x & 0xFF;
	*where = (x >> 8) & 0xFF;
	*where = y & 0xFF;
	*where = (y >> 8) & 0xFF;
}

void draw_shape(char *where, int x1, int y1, int x2, int y2, Colour *colour)
{
	while (!(*GPU_STATUS & (1 << (where - GPU_STATUS))))
		;
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

void draw_pixel(int x, int y, Colour *colour)
{
	while (!(*GPU_STATUS & (1 << (GPU_RENDER_PIXEL1 - GPU_STATUS))) &&
		   !(*GPU_STATUS & (1 << (GPU_RENDER_PIXEL2 - GPU_STATUS))))
		;

	if (*GPU_STATUS & (1 << (GPU_RENDER_PIXEL2 - GPU_STATUS)))
		draw_pixel(GPU_RENDER_PIXEL2, x, y, colour);
	else
		draw_pixel(GPU_RENDER_PIXEL1, x, y, colour);
}

void draw_line(int x1, int y1, int x2, int y2, Colour *colour)
{
	while (!(*GPU_STATUS & (1 << (GPU_RENDER_LINE1 - GPU_STATUS))) &&
		   !(*GPU_STATUS & (1 << (GPU_RENDER_LINE2 - GPU_STATUS))))
		;

	if (*GPU_STATUS & (1 << (GPU_RENDER_LINE2 - GPU_STATUS)))
		draw_shape(GPU_RENDER_LINE2, x1, y1, x2, y2, colour);
	else
		draw_shape(GPU_RENDER_LINE1, x1, y1, x2, y2, colour);
}

void draw_rect(int x1, int y1, int x2, int y2, Colour *colour)
{
	while (!(*GPU_STATUS & (1 << (GPU_RENDER_RECT1 - GPU_STATUS))) &&
		   !(*GPU_STATUS & (1 << (GPU_RENDER_RECT2 - GPU_STATUS))))
		;

	if (*GPU_STATUS & (1 << (GPU_RENDER_RECT2 - GPU_STATUS)))
		draw_shape(GPU_RENDER_RECT2, x1, y1, x2, y2, colour);
	else
		draw_shape(GPU_RENDER_RECT1, x1, y1, x2, y2, colour);
}

void draw_pixel(DRAW_PRIORITY priority, int x, int y, Colour *colour)
{
	if (priority)
		draw_pixel(GPU_RENDER_PIXEL2, x, y, colour);
	else
		draw_pixel(GPU_RENDER_PIXEL1, x, y, colour);
}

void draw_line(DRAW_PRIORITY priority, int x1, int y1, int x2, int y2, Colour *colour)
{
	if (priority)
		draw_shape(GPU_RENDER_LINE2, x1, y1, x2, y2, colour);
	else
		draw_shape(GPU_RENDER_LINE1, x1, y1, x2, y2, colour);
}

void draw_rect(DRAW_PRIORITY priority, int x1, int y1, int x2, int y2, Colour *colour)
{
	if (priority)
		draw_shape(GPU_RENDER_RECT2, x1, y1, x2, y2, colour);
	else
		draw_shape(GPU_RENDER_RECT1, x1, y1, x2, y2, colour);
}