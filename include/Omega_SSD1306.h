/**
 * @file Omega_SSD1306.hpp
 * @brief SSD1306 / SSD1309 OLED display driver for Raspberry Pi.
 *
 * Copyright (c) 2026 Onetimega
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 */

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
void transparent_text_display(const char* text_input, int x, int y);
void sequential_text_display(const char* text_input, int x, int y, int c_delay);


void pixel_display(uint16_t x, uint16_t y);
void line_display(int x1, int y1, int x2, int y2);
void rectangle_display(int x, int y, int width, int height, bool fill = false);
void quadrilateral_display(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void circle_display(int xc, int yc, int r);
void easy_triangle_display(uint16_t x, uint16_t y, uint16_t base, uint16_t height);
void triangle_display(int x1, int y1, int x2, int y2, int x3, int y3);

#endif

