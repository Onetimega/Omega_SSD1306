#include "include/Omega_SSD1306.h"

int main(){
        init_i2c_display(0x3C);

        rectangle_display(0,0, 127,63);
        rectangle_display(32,16, 64, 32);
        

        flush_display();

}
