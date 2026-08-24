#include "include/Omega_SSD1306.h"

int main(){

        init_i2c_display(0x3C);
        fb_clear_display();
        line_display(0,0, 127,63);
        line_display(0,63, 127,0);
        line_display(64, 0, 64,63);
        line_display(0,32, 127,32);
        
        flush_display();

}

