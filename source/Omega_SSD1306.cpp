/**
 * @file Omega_SSD1306.cpp
 * @brief SSD1306 OLED display driver for Raspberry Pi.
 *
 * Copyright (c) 2026 Onetimega
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 */


#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
//#include <stdexcept>

#include <chrono>
#include <thread>
//#include <time.h>
#include <utility>


static int fd = open("/dev/i2c-1", O_RDWR);


uint8_t framebuffer[1025] = {0};


static unsigned char initBytes[26] = {
        0x00, 0xAE, 0xA8, 0x3F, 0xD3,
        0x00, 0x40, 0xA1, 0xC8, 0xDA,
        0x12, 0x81, 0x7F, 0xA4, 0xA6,
        0xD5, 0x80, 0x8D, 0x14, 0xD9,
        0x22, 0xD8, 0x30, 0x20, 0x00,
        0xAF
};

static const uint8_t Unknown_char[8] = {0x00, 0x66, 0x5a, 0x24, 0x24, 0x5a, 0x66, 0x00};         //0
static const uint8_t space [8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};               //32
static const uint8_t exclamation_mark [8] = {0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x00};    //33
static const uint8_t double_quotes[8] = {0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00};        //34
static const uint8_t number_sign[8] = {0x00, 0x24, 0x7e, 0x24, 0x7e, 0x24, 0x00, 0x00};          //35
static const uint8_t dollar[8] = {0x00, 0x58, 0x54, 0xfe, 0x54, 0x34, 0x00, 0x00};               //36
static const uint8_t percent_sign[8] = {0x00, 0x46, 0x26, 0x10, 0x08, 0x64, 0x62, 0x00};//37
static const uint8_t ampersand[8] = {0x00, 0x00, 0x34, 0x4a, 0x52, 0x24, 0x40, 0x00};//38
static const uint8_t single_quote[8] = {0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00};         //39
static const uint8_t open_parenthesis [8] = {0x00, 0x00, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00};    //40
static const uint8_t close_parenthesis [8] = {0x00, 0x00, 0x00, 0x42, 0x24, 0x18, 0x00, 0x00};   //41
static const uint8_t asterisk [8] {0x00, 0x04, 0x18, 0x0e, 0x18, 0x04, 0x00, 0x00};//42
static const uint8_t plus [8] = {0x00, 0x7c, 0x05, 0x09, 0x31, 0x41, 0x7c, 0x00};                //43
static const uint8_t comma [8] = {0x00, 0x00, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00};               //44
static const uint8_t hyphen_minus [8] = {0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};        //45
static const uint8_t dot [8] = {0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};                 //46
static const uint8_t diagonal [8] = {0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00};            //47

static const uint8_t zero [8] = {0x00, 0x3c, 0x42, 0x5a, 0x42, 0x42, 0x3c, 0x00};                //48
static const uint8_t one [8] = {0x00, 0x00, 0x42, 0x7e, 0x40, 0x00, 0x00, 0x00};                 //49
static const uint8_t two [8] = {0x00, 0x00, 0x72, 0x4a, 0x4a, 0x44, 0x00, 0x00};                 //50
static const uint8_t three [8] = {0x00, 0x00, 0x42, 0x4a, 0x4a, 0x34, 0x00, 0x00};               //51
static const uint8_t four [8] = {0x00, 0x00, 0x1e, 0x10, 0x10, 0x7e, 0x00, 0x00};                //52
static const uint8_t five [8] = {0x00, 0x00, 0x4e, 0x4a, 0x4a, 0x32, 0x00, 0x00};                //53
static const uint8_t six [8] = {0x00, 0x00, 0x7e, 0x4a, 0x4a, 0x7a, 0x00, 0x00};                 //54
static const uint8_t seven [8] = {0x00, 0x00, 0x02, 0x02, 0x02, 0x7e, 0x00, 0x00};               //55
static const uint8_t eight [8] = {0x00, 0x00, 0x34, 0x4a, 0x4a, 0x34, 0x00, 0x00};               //56
static const uint8_t nine [8] = {0x00, 0x00, 0x4e, 0x4a, 0x4a, 0x7e, 0x00, 0x00};                //57

static const uint8_t colon [8] = {0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00};               //58
static const uint8_t semicolon [8] = {0x00, 0x00, 0x40, 0x22, 0x00, 0x00, 0x00, 0x00};           //59
static const uint8_t less_than [8] = {0x00, 0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x00};           //60
static const uint8_t equal [8] = {0x00, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00};               //61
static const uint8_t greater_than [8] = {0x00, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x00};        //62
static const uint8_t question [8] = {0x00, 0x00, 0x02, 0x5a, 0x0a, 0x0e, 0x00, 0x00};            //63
static const uint8_t AT_sign [8] = {0x00, 0x7e, 0x42, 0x5a, 0x52, 0x52, 0x5e, 0x00};             //64

static const uint8_t A [8] = {0x00, 0x7c, 0x12, 0x12, 0x12, 0x12, 0x7c, 0x00};                   //65
static const uint8_t B [8] = {0x00, 0x7e, 0x4a, 0x4a, 0x4a, 0x4a, 0x34, 0x00};                   //66
static const uint8_t C [8] = {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00};                   //67
static const uint8_t D [8] = {0x00, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00};                   //68
static const uint8_t E [8] = {0x00, 0x7e, 0x52, 0x52, 0x52, 0x42, 0x42, 0x00};                   //69
static const uint8_t F [8] = {0x00, 0x7e, 0x12, 0x12, 0x12, 0x02, 0x02, 0x00};                   //70
static const uint8_t G [8] = {0x00, 0x3c, 0x42, 0x4a, 0x4a, 0x4a, 0x3a, 0x00};                   //71
static const uint8_t H [8] = {0x00, 0x7e, 0x08, 0x08, 0x08, 0x08, 0x7e, 0x00};                   //72
static const uint8_t I [8] = {0x00, 0x00, 0x42, 0x7e, 0x42, 0x00, 0x00, 0x00};                   //73
static const uint8_t J [8] = {0x00, 0x72, 0x42, 0x42, 0x7e, 0x02, 0x02, 0x00};                   //74
static const uint8_t K [8] = {0x00, 0x7e, 0x08, 0x14, 0x24, 0x42, 0x00, 0x00};                   //75
static const uint8_t L [8] = {0x00, 0x7e, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00};                   //76
static const uint8_t M [8] = {0x00, 0x7e, 0x04, 0x08, 0x08, 0x04, 0x7e, 0x00};                   //77
static const uint8_t N [8] = {0x00, 0x7e, 0x02, 0x0c, 0x30, 0x40, 0x7e, 0x00};                   //78
static const uint8_t O [8] = {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00};                   //79
static const uint8_t P [8] = {0x00, 0x7e, 0x12, 0x12, 0x12, 0x12, 0x0c, 0x00};                   //80
static const uint8_t Q [8] = {0x00, 0x3c, 0x42, 0x42, 0x52, 0x62, 0x3c, 0x00};                   //81
static const uint8_t R [8] = {0x00, 0x7e, 0x12, 0x12, 0x32, 0x52, 0x0c, 0x00};                   //82
static const uint8_t S [8] = {0x00, 0x4c, 0x4a, 0x4a, 0x4a, 0x4a, 0x32, 0x00};                   //83
static const uint8_t T [8] = {0x00, 0x02, 0x02, 0x02, 0x7e, 0x02, 0x02, 0x00};                   //84
static const uint8_t U [8] = {0x00, 0x3e, 0x40, 0x40, 0x40, 0x40, 0x3e, 0x00};                   //85
static const uint8_t V [8] = {0x00, 0x0e, 0x30, 0x40, 0x40, 0x30, 0x0e, 0x00};                   //86
static const uint8_t W [8] = {0x00, 0x7e, 0x20, 0x10, 0x10, 0x20, 0x7e, 0x00};                   //87
static const uint8_t X [8] = {0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00};                   //88
static const uint8_t Y [8] = {0x00, 0x02, 0x04, 0x08, 0x78, 0x04, 0x02, 0x00};                   //89
static const uint8_t Z [8] = {0x00, 0x62, 0x52, 0x52, 0x4a, 0x4a, 0x46, 0x00};                   //90

static const uint8_t open_bracket [8] = {0x00, 0x00, 0x00, 0x7e, 0x42, 0x00, 0x00, 0x00};        //91
static const uint8_t backslash [8] = {0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00};//92
static const uint8_t close_bracket [8] = {0x00, 0x00, 0x00, 0x42, 0x7e, 0x00, 0x00, 0x00};       //93
static const uint8_t caret_circumflex [8] = {0x00, 0x08, 0x04, 0x02, 0x04, 0x08, 0x00, 0x00};//94
static const uint8_t underscore [8] = {0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00};          //95
static const uint8_t grave_accent [8] = {0x00, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00};//96

static const uint8_t a [8] = {0x00, 0x7c, 0x12, 0x12, 0x12, 0x12, 0x7c, 0x00};                   //97
static const uint8_t b [8] = {0x00, 0x7e, 0x4a, 0x4a, 0x4a, 0x4a, 0x34, 0x00};                   //98
static const uint8_t c [8] = {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00};                   //99
static const uint8_t d [8] = {0x00, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00};                   //100
static const uint8_t e [8] = {0x00, 0x7e, 0x52, 0x52, 0x52, 0x42, 0x42, 0x00};                   //101
static const uint8_t f [8] = {0x00, 0x7e, 0x12, 0x12, 0x12, 0x02, 0x02, 0x00};                   //102
static const uint8_t g [8] = {0x00, 0x3c, 0x42, 0x4a, 0x4a, 0x4a, 0x3a, 0x00};                   //103
static const uint8_t h [8] = {0x00, 0x7e, 0x08, 0x08, 0x08, 0x08, 0x7e, 0x00};                   //104
static const uint8_t i [8] = {0x00, 0x00, 0x42, 0x7e, 0x42, 0x00, 0x00, 0x00};                   //105
static const uint8_t j [8] = {0x00, 0x72, 0x42, 0x42, 0x7e, 0x02, 0x02, 0x00};                   //106
static const uint8_t k [8] = {0x00, 0x7e, 0x08, 0x14, 0x24, 0x42, 0x00, 0x00};                   //107
static const uint8_t l [8] = {0x00, 0x7e, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00};                   //108
static const uint8_t m [8] = {0x00, 0x7e, 0x04, 0x08, 0x08, 0x04, 0x7e, 0x00};                   //109
static const uint8_t n [8] = {0x00, 0x7e, 0x02, 0x0c, 0x30, 0x40, 0x7e, 0x00};                   //110
static const uint8_t o [8] = {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00};                   //111
static const uint8_t p [8] = {0x00, 0x7e, 0x12, 0x12, 0x12, 0x12, 0x0c, 0x00};                   //112
static const uint8_t q [8] = {0x00, 0x3c, 0x42, 0x42, 0x52, 0x62, 0x3c, 0x00};                   //113
static const uint8_t r [8] = {0x00, 0x7e, 0x12, 0x12, 0x32, 0x52, 0x0c, 0x00};                   //114
static const uint8_t s [8] = {0x00, 0x4c, 0x4a, 0x4a, 0x4a, 0x4a, 0x32, 0x00};                   //115
static const uint8_t t [8] = {0x00, 0x02, 0x02, 0x02, 0x7e, 0x02, 0x02, 0x00};                   //116
static const uint8_t u [8] = {0x00, 0x3e, 0x40, 0x40, 0x40, 0x40, 0x3e, 0x00};                   //117
static const uint8_t v [8] = {0x00, 0x0e, 0x30, 0x40, 0x40, 0x30, 0x0e, 0x00};                   //118
static const uint8_t w [8] = {0x00, 0x7e, 0x20, 0x10, 0x10, 0x20, 0x7e, 0x00};                   //119
static const uint8_t x [8] = {0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00};                   //120
static const uint8_t y [8] = {0x00, 0x02, 0x04, 0x08, 0x78, 0x04, 0x02, 0x00};                   //121
static const uint8_t z [8] = {0x00, 0x62, 0x52, 0x52, 0x4a, 0x4a, 0x46, 0x00};                   //122


struct ascii_chars {
       const uint8_t* characters[128];
};


ascii_chars indexes = {};


void init_ascii() {
        indexes.characters[0] = Unknown_char;
        indexes.characters[32] = space;
        indexes.characters[33] = exclamation_mark;
        indexes.characters[34] = double_quotes;
        indexes.characters[35] = number_sign;
        indexes.characters[36] = dollar;
        indexes.characters[37] = percent_sign;
        indexes.characters[38] = ampersand;
        indexes.characters[39] = single_quote; 
        indexes.characters[40] = open_parenthesis;
        indexes.characters[41] = close_parenthesis;
        indexes.characters[42] = asterisk;
        indexes.characters[43] = plus;
        indexes.characters[44] = comma;
        indexes.characters[45] = hyphen_minus;
        indexes.characters[46] = dot;
        indexes.characters[47] = diagonal;
         
        indexes.characters[48] = zero;
        indexes.characters[49] = one;
        indexes.characters[50] = two;
        indexes.characters[51] = three;
        indexes.characters[52] = four;
        indexes.characters[53] = five;
        indexes.characters[54] = six;
        indexes.characters[55] = seven;
        indexes.characters[56] = eight;
        indexes.characters[57] = nine;
        
        indexes.characters[58] = colon;
        indexes.characters[59] = semicolon;
        indexes.characters[60] = less_than;
        indexes.characters[61] = equal;
        indexes.characters[62] = greater_than;
        indexes.characters[63] = question;
        indexes.characters[64] = AT_sign;   //@
        
        indexes.characters[65] = A;
        indexes.characters[66] = B;
        indexes.characters[67] = C;
        indexes.characters[68] = D;
        indexes.characters[69] = E;
        indexes.characters[70] = F;
        indexes.characters[71] = G;
        indexes.characters[72] = H;
        indexes.characters[73] = I;
        indexes.characters[74] = J;
        indexes.characters[75] = K;
        indexes.characters[76] = L;
        indexes.characters[77] = M;
        indexes.characters[78] = N;
        indexes.characters[79] = O;
        indexes.characters[80] = P;
        indexes.characters[81] = Q;
        indexes.characters[82] = R;
        indexes.characters[83] = S;
        indexes.characters[84] = T;
        indexes.characters[85] = U;
        indexes.characters[86] = V;
        indexes.characters[87] = W;
        indexes.characters[88] = X;
        indexes.characters[89] = Y;
        indexes.characters[90] = Z;

        indexes.characters[91] = open_bracket;
        indexes.characters[92] = backslash;
        indexes.characters[93] = close_bracket;
        indexes.characters[94] = caret_circumflex;
        indexes.characters[95] = underscore;
        indexes.characters[96] = grave_accent;

        indexes.characters[97] = a;
        indexes.characters[98] = b;
        indexes.characters[99] = c;
        indexes.characters[100] = d;
        indexes.characters[101] = e;
        indexes.characters[102] = f;
        indexes.characters[103] = g;
        indexes.characters[104] = h;
        indexes.characters[105] = i;
        indexes.characters[106] = j;
        indexes.characters[107] = k;
        indexes.characters[108] = l;
        indexes.characters[109] = m;
        indexes.characters[110] = n;
        indexes.characters[111] = o;
        indexes.characters[112] = p;
        indexes.characters[113] = q;
        indexes.characters[114] = r;
        indexes.characters[115] = s;
        indexes.characters[116] = t;
        indexes.characters[117] = u;
        indexes.characters[118] = v;
        indexes.characters[119] = w;
        indexes.characters[120] = x;
        indexes.characters[121] = y;
        indexes.characters[122] = z;        

}













void contrast_set(uint8_t value){
        if(value>=0){
                if(value>255){
                        value = 255;
                }

                uint8_t payload[3]{0x00, 0x81, value};
                write(fd, payload, 3);
        }
}



void clear_display(){
        uint8_t empty_bytes[1025] = {0};

        memcpy(framebuffer, empty_bytes, 1025);
        framebuffer[0] = 0x40;
        write(fd, framebuffer, 1025);
}

void fb_clear_display(){
    uint8_t empty_bytes[1024] = {0};
    memcpy(&framebuffer[1], empty_bytes, 1024);
    
}




void flush_display(){

        framebuffer[0] = 0x40;
        write(fd, framebuffer, 1025);

}


void flush_command(){
        uint8_t payload{};
}




static void delay(int time_delay){
        std::this_thread::sleep_for(std::chrono::milliseconds(time_delay));
}


int init_i2c_display(int address){
    if(fd < 0){
        perror("i2c device not found");
        return 1;
    }

    if(ioctl(fd, I2C_SLAVE, address) < 0){
        perror("i2c address not found");
        return 2;
    }

    write(fd, initBytes, 26);
    return 0;
}




void text_display(const char* text_input, int x, int y){

        if(y > 7) { y = 7; }
        if(x > 15) { x = 15; }

         if(y < 0) { y = 0; }
        if(x < 0) { x = 0; }
 

        int string_length = 16;
        char text_chars[string_length] = {};

        strncpy(text_chars, text_input, 15);
        text_chars[15] = '\0';


        int cell_x = x * 8;
        int cell_y = y * 128;



        for (int i = 0; text_chars[i] != '\0'; ++i){
                if(cell_x > 127) break;
                char c = text_chars[i];
                const uint8_t* byte_data = nullptr;


                if(c < 32 || c > 127) {
                        byte_data = indexes.characters[0];

                        while (text_chars[i + 1] != '\0' && text_chars[i + 1] < 32) {
                                i++;
                        }
                }
                else{

                        byte_data = indexes.characters[(const uint8_t)c];
                }


                memcpy(&framebuffer[1 + cell_x + cell_y], byte_data, 8);
                cell_x+=8;
        }



}


void transparent_text_display(const char* text_input, int x, int y){

        if(y > 7) { y = 7; }
        if(x > 15) { x = 15; }

         if(y < 0) { y = 0; }
        if(x < 0) { x = 0; }
 

        int string_length = 16;
        char text_chars[string_length] = {};

        strncpy(text_chars, text_input, 15);
        text_chars[15] = '\0';


        int cell_x = x * 8;
        int cell_y = y * 128;



        for (int i = 0; text_chars[i] != '\0'; ++i){
                if(cell_x > 127) break;
                char c = text_chars[i];
                const uint8_t* byte_data = nullptr;


                if(c < 32 || c > 127) {
                        byte_data = indexes.characters[0];

                        while (text_chars[i + 1] != '\0' && text_chars[i + 1] < 32) {
                                i++;
                        }
                }
                else{

                        byte_data = indexes.characters[(const uint8_t)c];
                }


                
                for(int col = 0; col<8; col++){

                        int fb_index = 1 + cell_x + cell_y + col;
                        framebuffer[fb_index] |= byte_data[col];

                }


                cell_x+=8;
        }



}



void sequential_text_display(const char* text_input, int x, int y, int c_delay){

        if(y > 7) { y = 7; }
        if(x > 15) { x = 15; }

        int string_length = 16;
        char text_chars[string_length] = {};

        strncpy(text_chars, text_input, 15);
        text_chars[15] = '\0';


        int cell_x = x * 8;
        int cell_y = y * 128;



        for (int i = 0; text_chars[i] != '\0'; ++i){
                if(cell_x > 127) break;
                char c = text_chars[i];
                const uint8_t* byte_data = nullptr;


                if(c < 32 || c > 127) {
                        byte_data = indexes.characters[0];

                        while (text_chars[i + 1] != '\0' && text_chars[i + 1] < 32) {
                                i++;
                        }
                }
                else{

                        byte_data = indexes.characters[(const uint8_t)c];
                }


                memcpy(&framebuffer[1 + cell_x + cell_y], byte_data, 8);
                flush_display();
                cell_x+=8;
                delay(c_delay);
        }



}






void pixel_display(uint16_t x, uint16_t y){

        if (x < 0 || x >= 128 || y < 0 || y >= 64) return;

        uint16_t page = y >> 3;              // y / 8
        uint16_t bit  = y & 0x07;            // y % 8
        uint16_t index = page * 128 + x + 1;

        framebuffer[index] |= (1 << bit);

}

void line_display(int x1, int y1, int x2, int y2){


        if (x1 > x2){
                std::swap(x1, x2);
                std::swap(y1, y2);
        }

        int dx = x2 - x1;
        int dy = y2 - y1;

        int p = 0;
        int y = 0;

        int dir_y;

        if(dy < 0) {dir_y = -1;} else {dir_y = 1;}

        dy *= dir_y;

        if(dx>=dy){
                y = y1;

                p = 2 * dy - dx;

                for(int i = 0; i <= dx; i++){
                        pixel_display(x1 + i, y);

                        if (p >= 0){
                                y += dir_y;
                                p = p - 2*dx;
                        }

                        p = p + 2*dy;

                }

        }
        else { 



                if (y1 > y2){
                        std::swap(x1, x2);
                        std::swap(y1, y2);
                }

                int dx = x2 - x1;
                int dy = y2 - y1;

                int p = 0;
                int x = 0;

                int dir_x;

                if(dx < 0) {dir_x = -1;} else {dir_x = 1;}

                dx *= dir_x;

                if(dy!=0){
                        x = x1;

                        p = 2 * dx - dy;

                        for(int i = 0; i <= dy; i++){
                                pixel_display(x, y1 + i);

                                if (p >= 0){
                                        x += dir_x;
                                        p = p - 2*dy;
                                }

                                p = p + 2*dx;

                        }

                }

        }



}


void rectangle_display(int x, int y, int width, int height, bool fill){

        line_display(x, y, x + width, y);
        line_display(x, y, x, y + height);

        line_display(x, y + height, x + width, y + height);
        line_display(x + width, y, x + width, y + height);

        if(fill == true){
                for (int i = 0; i < height; i++){
                        line_display(x, y + 1 + i, x + width, y + 1 + i);
                }
        }


}

void quadrilateral_display(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    line_display(x1, y1, x2, y2);
}

void circle_display(int xc, int yc, int r){

    int x = 0;
    int y = r;
    int p = 1 - r;

    pixel_display(xc + x, yc + y);
    pixel_display(xc - x, yc + y);
    pixel_display(xc + x, yc - y);
    pixel_display(xc - x, yc - y);
    pixel_display(xc + y, yc + x);
    pixel_display(xc - y, yc + x);
    pixel_display(xc + y, yc - x);
    pixel_display(xc - y, yc - x);

    while (x < y) {
        x++;

        if (p < 0) {

            p += (x << 1) + 1;
        } else {
            y--;

            p += ((x - y) << 1) + 1;
        }


        pixel_display(xc + x, yc + y);
        pixel_display(xc - x, yc + y);
        pixel_display(xc + x, yc - y);
        pixel_display(xc - x, yc - y);
        pixel_display(xc + y, yc + x);
        pixel_display(xc - y, yc + x);
        pixel_display(xc + y, yc - x);
        pixel_display(xc - y, yc - x);
    }
}

void easy_triangle_display(uint16_t x, uint16_t y, uint16_t base, uint16_t height){
    
        line_display(x, y, x + base, y);
        line_display(x, y, x + (base>>1), y + height);
        line_display(x + base, y, x + (base>>1), y + height);


}


void triangle_display(int x1, int y1, int x2, int y2, int x3, int y3){
        line_display(x1,y1, x2,y2);
        line_display(x2,y2, x3,y3);
        line_display(x3,y3, x1,y1);
}


