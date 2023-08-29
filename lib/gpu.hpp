#ifndef GPU_H
#define GPU_H

struct Colour {
    char r;
    char g;
    char b;
};

char *const GPU_STATUS =        (char *)0x4000;
char *const GPU_RENDER_PIXEL1 = (char *)0x4001;
char *const GPU_RENDER_PIXEL2 = (char *)0x4002;
char *const GPU_RENDER_LINE1 =  (char *)0x4003;
char *const GPU_RENDER_LINE2 =  (char *)0x4004;
char *const GPU_RENDER_RECT1 =  (char *)0x4005;
char *const GPU_RENDER_RECT2 =  (char *)0x4006;

void draw_pixel(char* where, int x, int y, Colour* colour);
void draw_shape(char* where, int x1, int y1, int x2, int y2, Colour* colour);

void draw_pixel(int x, int y, Colour* colour);
void draw_line(int x1, int y1, int x2, int y2, Colour* colour);
void draw_rect(int x1, int y1, int x2, int y2, Colour* colour);


enum DRAW_PRIORITY: bool {PRIO_LOW = 0,PRIO_HIGH = 1};

void draw_pixel(DRAW_PRIORITY priority, int x, int y, Colour* colour);
void draw_line(DRAW_PRIORITY priority, int x1, int y1, int x2, int y2, Colour* colour);
void draw_rect(DRAW_PRIORITY priority, int x1, int y1, int x2, int y2, Colour* colour);


#endif