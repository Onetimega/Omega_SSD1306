# Omega_SSD1306 Documentation Page

All examples can be found at examples/ folder in the project's root.

####  init_i2c_display(int address);
This function initializes the entire display, without it, you'll have a completely dark screen,
so don't forget to always add it at the very beginning of your code!.

If parameters are empty, defaults to 0x3C address.

Example: 
```cpp
int main(){
    init_i2c_display(0x3C);
    //your imagination here
    }
```

#### flush_display();
Flushes the entire 1024 byte framebuffer data to the display. Use it wisely!, and never forget to 
add it after finishing your designs or anything you've made!.

Example:

```cpp
int main(){
    init_i2c_display(0x3C);
    
    //some code, some drawings, some shenanigans

    flush_display(); // you'll now render anything you wrote to the framebuffer into the display
}
```

#### fb_clear_display();
Clears the entire framebuffer without updating immediately, this is recommended to be used right
after initializing the display to avoid weird behavior after running any other render multiple
times.

Example: 
```cpp
int main(){
    init_i2c_display(0x3c);
    
    fb_clear_display();

    //rest of your code
}
```

#### clear_display();
Does the same as fb_clear_display, clears the whole framebuffer, but immediately updates the screen,
not advised to use on tight loops such as animations, as it can cause flickering or slowdowns.

Example: 
```cpp
int main(){
    init_i2c_display(0x3c);
    
    //rest of your code

    clear_display();

    //rest of your code
}
```


#### init_ascii();
Loads all bitmaps of the currently made ASCII characters, don't forget to use it before using any
text_display() functions, or you will get segfaults. All basic characters from ASCII (32 - 127) 
are supported. If a character it not supported, you'll either get a segfault or have the
unknown character symbol displayed.

Example:
```cpp
int main(){
    init_i2c_display(0x3C);
    init_ascii();
    fb_clear_display();
    //now you can put your text here
    }
```    

#### text_display(const char* text, int x, int y);
Prints basic text on display on a 8x8 grid across the whole screen, uses const char*, so 
you must convert whatever data type you use to the proper data type before printing anything here.

The whole display is divided in a  16x8 grid, where coordinates range from x(0-15) and y(0-7).

Example:
```cpp
int main(){
    init_i2c_display(0x3c);
    init_ascii();
    fb_clear_display();

    text_display("Hello World!", 0, 0); 

    flush_display();
}
```

#### transparent_text_display(const char* text, int x, int y);
It's basically the same as text_display, but it will not draw the black background
behind each character cell, useful if you don't want black squares over your renders, usage is
exactly the same as the previous function.

Example: 

```cpp
int main(){
    init_i2c_display(0x3c);
    init_ascii();
    fb_clear_display();

    transparent_text_display("Hello World!", 0, 0); 

    flush_display();
}
```

#### sequential_text_display(const char* text, int x, int y, int c_delay);
Prints your text character by character, note that the smallest delay is defined by i2c bus speed
itself, so, using a 1ms doesn't mean you'll get exactly 1ms delay between each sequence. This
function also forces dumping the framebuffer to display, so you don't have to use flush_delay(); 

Example: 
```cpp
int main(){
    init_i2c_display(0x3c);
    init_ascii();
    fb_clear_display();

    sequential_text_display("Hello World!", 0, 0, 50); //delay in milliseconds

}
```

#### pixel_display(uint16_t x, uint16_t y);
Turns on a single pixel at given coordinates in a 128x64 canvas, x value range is 0-127,
y value range is 0-63.

Example:
```cpp
int main(){
    init_i2c_display(0x3C);
    fb_clear_display();

    pixel_display(64, 32); //draws a single point at about the screen's center

    flush_display();

}
```

#### line_display(int x1, int y1, int x2, int y2);
Draws a line from point "A" to point "B".

Example: 
```cpp
int main(){
    init_i2c_display(0x3c);
    fb_clear_display();

    line_display(0,32, 127,63); //draws a line across the whole display's width

    flush_display();
    }
```


#### rectangle_display(int x, int y, int width, int height, bool fill);
Draws a rectangle from given coordinates, can be filled if fill parameter is "1", defaults to
no fill if left empty.

Example:
```cpp
int main(){
    init_i2c_display(0x3c);
    fb_clear_display();

    rectangle_display(0,0, 32,16); //draws a hollow rectangle 
    rectangle_display(64,16, 32,16, 1); //draws a rectangle, but with filling

    flush_display();
    }
```


#### circle_display(int xc, int yc, int r);
Draws a circle of given radius at given coordinates.

Example: 
```cpp
int main(){
    init_i2c_display(0x3c);
    fb_clear_display();

    circle_display(64,32, 24); //draws a circle at the center of the screen

    flush_display();
    }
```
####triangle_display(int x1, int y1, int x2, int y2, int x3, int y3);
Draws a triangle connecting the three given coordinates.

Example:
```cpp
int main(){
    init_i2c_display(0x3c);
    fb_clear_display();

    triangle_display(20,45, 40,60, 30,10);
    flush_display();
    }
```


#### easy_triangle_display(uint16_t x, uint16_t y, uint16_t base, uint16_t height);
Draws a standard triangle of given base and height at given coordinates.

Example:
```cpp
int main(){
    init_i2c_display(0x3c);
    fb_clear_display();

    easy_triangle_display(64,16, 64,32); 

    flush_display();
    }
```








































