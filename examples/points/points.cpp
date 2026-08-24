#include "include/Omega_SSD1306.h"

int main(){
        init_i2c_display(0x3c);
        fb_clear_display();

        int r = 0;
        for(int i = 0; i < 128; ++i){
        r = i%4;
        if (r == 0){
                pixel_display(i, 0);

                pixel_display(i,16);

                pixel_display(i, 32);

                pixel_display(i, 48);

                pixel_display(i, 63);
        }
            
        }

        flush_display();

}


