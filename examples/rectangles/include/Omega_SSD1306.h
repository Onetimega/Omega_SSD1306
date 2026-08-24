//Omega_SSD1306.h

#ifndef OMEGA_SSD1306_H
#define OMEGA_SSD1306_H

#include<cstdint>
#include<cstring>

extern uint8_t framebuffer[1025];

void init_ascii();
void contrast_set(uint8_t value);
void clear_display();
void fb_clear_display();
void flush_display();
int init_i2c_display(int address = 0x3C);

void text_display(const char* text_input, int x, int y);
void text_display_transparent(const char* text_input, int x, int y);
void sequential_text_display(const char* text_input, int x, int y, int c_delay);


void pixel_display(uint16_t x, uint16_t y);
void line_display(int x1, int y1, int x2, int y2);
void rectangle_display(int x, int y, int width, int height, bool fill = false);
void quadrilateral_display(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void circle_display(int xc, int yc, int r);
void triangle_easy_display(uint16_t x, uint16_t y, uint16_t base, uint16_t height);
void triangle_display(int x1, int y1, int x2, int y2, int x3, int y3);

#endif

