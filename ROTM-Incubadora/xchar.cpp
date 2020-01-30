#include <Arduino.h>

#include "LiquidCrystal_I2C.h" 
#include "xchar.h"

  byte bedTemp[8] = {
    B00000,
    B11111,
    B10101,
    B10001,
    B10101,
    B11111,
    B00000,
    B00000
  }; //thanks Sonny Mounicou
  byte degree[8] = {
    B01100,
    B10010,
    B10010,
    B01100,
    B00000,
    B00000,
    B00000,
    B00000
  };
  byte thermometer[8] = {
    B00100,
    B01010,
    B01010,
    B01010,
    B01010,
    B10001,
    B10001,
    B01110
  };

byte uplevel[8] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B11100,
    B00000,
    B00000,
    B00000
  }; //thanks joris
  byte refresh[8] = {
    B00000,
    B00110,
    B11001,
    B11000,
    B00011,
    B10011,
    B01100,
    B00000,
  }; //thanks joris
  byte folder[8] = {
    B00000,
    B11100,
    B11111,
    B10001,
    B10001,
    B11111,
    B00000,
    B00000
  }; //thanks joris
  byte feedrate[8] = {
    B11100,
    B10000,
    B11000,
    B10111,
    B00101,
    B00110,
    B00101,
    B00000
  }; //thanks Sonny Mounicou

byte xclock[8] = {
    B00000,
    B01110,
    B10011,
    B10101,
    B10001,
    B01110,
    B00000,
    B00000
  }; //thanks Sonny Mounicou


    byte progress[3][8] = { {
      B00000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B00000
    }, {
      B00000,
      B10100,
      B10100,
      B10100,
      B10100,
      B10100,
      B10100,
      B00000
    }, {
      B00000,
      B10101,
      B10101,
      B10101,
      B10101,
      B10101,
      B10101,
      B00000
    }};

byte smiley[8] = {
B00000, B01010,
B00000,
B00000,
B10001,
B01110,
B00000,
B00000
};

byte heart_h[8] = {
B00000,
B00000,
B01010,
B10101,
B10001,
B01010,
B00100, B00000
}; 
byte heart_f[8] = {
B00000,
B00000,
B01010,
B11111,
B11111,
B01110,
B00100, B00000
}; 
byte ohm[8] = {
B00000,
B01110,
B10001,
B10001,
B10001,
B01010,
B01010, B11011
}; 
byte rect[8] = {
B11111,
B10001,
B10001,
B10001,
B10001,
B10001,
B10001,
B11111
};
byte arrow_u[8] = {
B00100,
B01110,
B11111,
B00100,
B00100,
B00100,
B00100, B00100
}; 
byte arrow_d[8] = { 
  B00100,
B00100,
B00100,
B00100, B00100, B11111,
B01110,
B00100
}; 
byte diamond[8] = {
B00000,
B00100,
B01010,
B10001, B01010,
B00100,
B00000,
B00000 
};     

uint8_t bell[8] = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8] = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t yclock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8] = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = { 0x1,0x1,0x5,0x9,0x1f,0x8,0x4};


void charsetThree(LiquidCrystal_I2C lcd)
{
  lcd.createChar(DEGREE, bell);
  lcd.createChar(BEDTEMP, note);
  lcd.createChar(THERMOMETER, yclock);
  lcd.createChar(UPLEVEL, heart);
  lcd.createChar(REFRESH, duck);
  lcd.createChar(FOLDER, check);
  lcd.createChar(FEEDRATE, cross);
  lcd.createChar(CLOCK, retarrow);
}

void charsetOne(LiquidCrystal_I2C lcd)
{
  lcd.createChar(DEGREE, degree);
  lcd.createChar(BEDTEMP,bedTemp);
  lcd.createChar(THERMOMETER, thermometer);
  lcd.createChar(UPLEVEL, uplevel);
  lcd.createChar(REFRESH, refresh);
  lcd.createChar(FOLDER, folder);
  lcd.createChar(FEEDRATE, feedrate);
  lcd.createChar(CLOCK, xclock);
}

void charsetFour(LiquidCrystal_I2C lcd)
{
  lcd.createChar(DEGREE, degree);
  lcd.createChar(BEDTEMP,bedTemp);
  lcd.createChar(THERMOMETER, thermometer);
  lcd.createChar(UPLEVEL, uplevel);
  lcd.createChar(REFRESH, refresh);
  lcd.createChar(FOLDER, check);
  lcd.createChar(FEEDRATE, feedrate);
  lcd.createChar(CLOCK, xclock);
}

void charsetTwo(LiquidCrystal_I2C lcd)
{
    lcd.createChar(SMILEY, smiley);
  lcd.createChar(HEART_H,heart_h);
  lcd.createChar(HEART_F,heart_f);
  lcd.createChar(OHM,ohm);
  lcd.createChar(RECT,rect);
  lcd.createChar(ARROW_U,arrow_u);
  lcd.createChar(ARROW_D, arrow_d);
  lcd.createChar(DIAMOND,diamond);
}



void showCharset(LiquidCrystal_I2C lcd)
{
    lcd.print(DEGREE);
  lcd.print(BEDTEMP);
  lcd.print(THERMOMETER);
  lcd.print(UPLEVEL);
  lcd.print(REFRESH);
  lcd.print(FOLDER);
  lcd.print(FEEDRATE);
  lcd.print(CLOCK);
}
