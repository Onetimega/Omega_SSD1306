#include "include/Omega_SSD1306.h"

int main(){
    init_i2c_display(0x3C); //you must change this address in case your display has a different one.
    init_ascii();


    rectangle_display(0,0, 127,63);
    line_display(64,0, 64,63);

    circle_display(32, 32, 24);
    triangle_easy_display(72, 16, 48,32);

    text_display("OLED 0.96", 5,0);
    flush_display();
    

}
