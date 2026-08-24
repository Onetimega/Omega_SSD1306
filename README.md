# Omega_SSD1306 Library


## Overview 
Omega_SSD1306 is a C++ library made to control 0.96" 128x64 OLED Displays 
that use SSD1306 driver over i2c protocol in Raspberry Pi boards running 
Raspberry Pi OS or similar Linux based installations.

This project was made mainly to learn basics about graphics and 
communication protocols, but I plan to expand it to a more complete 
library in the future.

- It can render basic 8x8 grid text
- Draw points on a virtual 128x64 canvas
- Draw lines, rectangles, triangles, circles and a few more shapes
- It features a simple framebuffer, where its control byte is embedded at the first position
- Uses /dev/i2c-1 device to communicate to the display

## Project Usage 

### Requirements
For compilation, you only need standard C/C++ libraries found on Linux, these are expected to be
already installed in your Raspberry Pi OS in normal conditions.

Enable i2c interface on your Raspberry Pi
```bash
sudo raspi-config
# Interface Options -> I2C -> Enable
```

### Build
In order to build the project, I provided a simple script called build.sh at the project root,
run:
```bash
./build.sh
```
###### If build.sh shows permission errors, use:

```bash
chmod +x build.sh
```


Output files will be stored at build/ folder.

In order to use it, copy the generated libOmega_SSD1306.a and Omega_SSD1306.h
from build/ and include/ folder to your own project.

In your program, you include the library using: 

```cpp
#include "Omega_SSD1306.h"
```
and compile by linking libOmega_SSD1306.a accordingly to your prefered compiler
(remember to properly format your #include line depending on your project's file tree.


## Basic Functions
###### All available functions are explained in detail at the documentation in 
##### docs/documentation.md
 
 - init_i2c_display(int address);  -> Used to initialize display, default is 0x3C.
 - init_ascii();               -> Loads available ascii characters on the program.
 - text_display(const char* text, int x, int y); -> Writes text in the framebuffer.
 - pixel_display(int x, int y); -> Turns on a single pixel on the 128x64 canvas.
 - flush_display(); -> Flushes all data stored at the framebuffer. 
 

 

