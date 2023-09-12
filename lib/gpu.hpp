#ifndef GPU_HPP
#define GPU_HPP

#ifndef NONES
#include "stdint.hpp"
#else
#include <stdint.h>
#endif

struct Colour
{
	constexpr Colour(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

#ifdef NONES
extern char *GPU_STATUS;
extern char *GPU_RENDER_PIXEL1;
extern char *GPU_RENDER_PIXEL2;
extern char *GPU_RENDER_LINE1;
extern char *GPU_RENDER_LINE2;
extern char *GPU_RENDER_RECT1;
extern char *GPU_RENDER_RECT2;
#else
volatile char *const GPU_STATUS =       (char *const)0x2000;
char *const GPU_RENDER_PIXEL1 = 		(char *const)0x2001;
char *const GPU_RENDER_PIXEL2 = 		(char *const)0x2002;
char *const GPU_RENDER_LINE1 =  		(char *const)0x2003;
char *const GPU_RENDER_LINE2 =  		(char *const)0x2004;
char *const GPU_RENDER_RECT1 = 			(char *const)0x2005;
char *const GPU_RENDER_RECT2 = 			(char *const)0x2006;
#endif

#define GPU_CONTROL GPU_STATUS

void draw_pixel(char *const where, const int x, const int y, const Colour &colour);
void draw_shape(char *const where, const int x1, const int y1,
								   const int x2, const int y2, const Colour &colour);

void draw_pixel(const int x, const int y, const Colour &colour);
void draw_line(const int x1, const int y1,
			   const int x2, const int y2, const Colour &colour);
void draw_rect(const int x1, const int y1, const int x2, const int y2, const Colour &colour);

enum DRAW_PRIORITY : bool
{
	PRIO_LOW = 0,
	PRIO_HIGH = 1
};

void draw_pixel(const DRAW_PRIORITY priority, const int x, const int y, const Colour &colour);
void draw_line(const DRAW_PRIORITY priority, const int x1, const int y1,
											 const int x2, const int y2, const Colour &colour);
void draw_rect(const DRAW_PRIORITY priority, const int x1, const int y1,
											 const int x2, const int y2, const Colour &colour);

#endif // !GPU_HPP