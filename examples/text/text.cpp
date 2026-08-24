#include "include/Omega_SSD1306.h"

int main(){
    init_i2c_display(0x3c);
    init_ascii();
    
    fb_clear_display();
    text_display("Omega_SSD1306",0,0);
    text_display("Example: text",0,1);
    flush_display();

}


